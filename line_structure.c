/*------------------------------------------------------------*/
/* Authors: Daniel Popov & Maor Maayan                        */
/* File   : line_structure.c                                  */
/*                                                            */
/* Description: A linked list for holding the lines and their */
/* attributes and flags mainly used for the second pass.      */
/*------------------------------------------------------------*/
#include "line_structure.h"
/*------------------------------------------------------------*/
/* Initializing line struct */
void init_line_node(line *line_list)
{ 
    line_list->line_number = 1;
    
    line_list->address     = 0;

    /* Set up string */
    memset(line_list->line_str, 0, sizeof(line_list->line_str));
    
    /* Set all boolean flags to FALSE: */    
    line_list->is_entry    = false;

    line_list->is_extern   = false;	

    line_list->is_error    = false;
		
    line_list->second_pass = false;

    line_list->is_label    = false;

    line_list->next        = NULL;
}
/*------------------------------------------------------------*/
/* Adding a line node to the link list with the line string ,char extra_label */
line *add_line_node(line **root,char *str_line,int line_num)
{
    line* new_node = (line *)validatedmalloc(sizeof(line));
    line *curr     = *root;
    /* Initializing node line */
    init_line_node(new_node);
    /* Add line form file and line num in the file to the node */
    append_line(new_node,str_line);
    append_line_num(new_node,line_num);
    /*Add IC to the node of the line */
    append_address(new_node);
    
    if(*root == NULL)
    {
        *root = new_node;
        return new_node;
    }
    while(curr->next != NULL)
        curr = curr->next;
	

    curr->next = new_node;

    return new_node;
}

/*------------------------------------------------------------*/
/* Append IC to node */
void append_address(line *line_node)
{   
    line_node->address = IC;
}
/*------------------------------------------------------------*/
/* Append line number in file to node */
void append_line_num(line *line_node,int line_num)
{
    line_node->line_number = line_num;
}
/*------------------------------------------------------------*/
/* Append the node with string of the line from the file      */
void append_line(line *line_node,char *str_line)
{
    strcpy(line_node->line_str,str_line);
}
/*------------------------------------------------------------*/
/* Functions to turn on the flags in the node:                */
 
/* Turn on the flag to know line has extern attribute         */
void turn_on_extern(line *root)
{
    root->is_extern = true;
}
/*------------------------------------------------------------*/
/* Turn on the flag to know line has entry attribute          */
void turn_on_entry(line *root)
{
    root->is_entry = true;
}
/*----------------------------------------------------------*/
/* Turn on the flag to know line has error attribute        */
void turn_on_error_flag(line *root)
{
    root->is_error = true;
}
/*----------------------------------------------------------*/
/* Turn on the flag to know line needs to do a second pass  */
void turn_on_second_pass(line *root)
{
    root->second_pass = true;
}
/*------------------------------------------------------------*/
/* Turn on the flag to know line has label as first word      */
void turn_on_label(line *root)
{
    root->is_label = true;
}
/*------------------------------------------------------------*/
/* Free linked list line */
void free_line_list(line** root)
{
    line* curr = *root;
    line* aux;
    while(curr != NULL)
    {
        aux  = curr;
        curr = curr->next;
        free(aux);
    }
    *root=NULL;
}