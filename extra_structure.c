/*------------------------------------------------------------*/
/* Authors: Maor Maayan & Daniel Popov                        */
/* File   : extra_structure.c                                 */
/*                                                            */
/* Description: Stores and prints the entries and externals   */
/* varible usage into .ext and .ent files.                    */
/*------------------------------------------------------------*/
#include "extra_structure.h"
/*Initialize node type extra */
void init_extra_node(extra *extra_node)
{
    extra_node->address   = 0;
    extra_node->is_extern = false;
    extra_node->next      = NULL;

    memset(extra_node->label, 0, sizeof(extra_node->label));
}
/*------------------------------------------------------------*/
/*Adds node to the link list type extra */
void add_extra_node(extra **root,line *cur_line ,label *cur_label)
{
    extra* new_node = (extra *)validatedmalloc(sizeof(extra));
    extra *curr     = *root;
    
    init_extra_node(new_node);
    
    new_node->is_extern   = cur_label->is_extern;

    if(cur_label->is_extern)
        new_node->address = cur_line->address;
    else 
        new_node->address = cur_label->address;
    
    strcpy(new_node->label, cur_label->label_name);

    if(*root == NULL)
    {
        *root = new_node;
        return;
    }
    while(curr->next != NULL)
        curr = curr->next;

    curr->next = new_node;
}
/*------------------------------------------------------------*/
/* Gets head_extra and prints all node inside the link list   */
/* prints nodes to .ext and .ent files                        */
void print_extra(extra **head_extra, char *filename)
{
    FILE  *entries, *externals;
    char  *ext_filename, *ent_filename; 
    extra *curr_extra =  *head_extra;
    
    ext_filename = (char *)validatedcalloc(strlen(filename) + 4, sizeof(char));
    ent_filename = (char *)validatedcalloc(strlen(filename) + 4, sizeof(char));
    
    strcat(ext_filename, filename);
    strcat(ent_filename, filename);
    strcat(ext_filename, ".ext");
    strcat(ent_filename, ".ent");
    
    externals = fopen(ext_filename, "w");
    entries   = fopen(ent_filename, "w");
    
    assert(externals != NULL);
    assert(entries   != NULL);
    
    while(curr_extra)
    {
        if(curr_extra->is_extern)
        {
            if(curr_extra->address < 1000)
                fprintf(externals, "%s 0%ld\n", curr_extra->label, curr_extra->address);
            else
                fprintf(externals, "%s %ld\n",  curr_extra->label, curr_extra->address);
        }
        else
        {
            if(curr_extra->address < 1000) 
                fprintf(entries,  "%s 0%ld\n", curr_extra->label, curr_extra->address);
            else
                fprintf(entries,  "%s %ld\n",  curr_extra->label, curr_extra->address);
        }
        curr_extra = curr_extra->next;
    }
    free(ext_filename);
    free(ent_filename);
    fclose(externals);
    fclose(entries);
}
/*------------------------------------------------------------*/
/*Free nodes in linked list type extra */
void free_extra_list(extra **root)
{
    extra* curr = *root;
    extra* aux;
    while(curr != NULL)
    {
        aux  = curr;
        curr = curr->next;
        free(aux);
    }
    *root=NULL;
}