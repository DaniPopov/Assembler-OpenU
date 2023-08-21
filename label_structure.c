/*------------------------------------------------------------*/
/* Authors: Daniel Popov & Maor Maayan                        */
/* File   : label_structure.c                                 */
/*                                                            */
/* Description:                                               */
/*------------------------------------------------------------*/
#include "label_structure.h"

/*------------------------------------------------------------*/
/* Initializing symbol struct */
void init_label_node(label *label_node)
{ 
    /* Set up to the value */
    label_node->address = 0;

    /* Set lable string: */
    memset(label_node->label_name , 0, sizeof(label_node->label_name));
   
    /* Set all boolean flags to FALSE: */
    label_node->is_code   = false;
    label_node->is_data   = false;
    label_node->is_entry  = false;
    label_node->is_extern = false;
    
    label_node->next      = NULL;
}
/*------------------------------------------------------------*/
/*Append label in node*/
void append_label(label *label_node,char *str_label)
{
    strcpy(label_node->label_name,str_label);
}
/*------------------------------------------------------------*/
/*Append value of the label in node*/
void append_value(label *label_node, unsigned long address)
{
    label_node->address = address;
}
/*------------------------------------------------------------*/
/*Insert a node to linked list of labels*/
void add_label_node(label **root,char *str_cmd,char *str_label)
{
    label* new_node = (label *)validatedmalloc(sizeof(label));
    label *curr = *root;
  
    /* Initializing node label */
    init_label_node(new_node);
    /* Add string label to the node */
    append_label(new_node,str_label);
    /* Decideing what attributes the labels has */
    turn_on_attr_flag(new_node,str_cmd);

    /* Add value to the node base on the attribute */
    if(new_node->is_code)
        append_value(new_node,IC);  	 
    else if(new_node->is_data)
	    append_value(new_node,DC);
    else if(new_node->is_extern)
        append_value(new_node,0);


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
/* Returns the address of the node label base on the label_end*/
unsigned long get_value(label **root, char *label_end)
{
  label* curr;
  for(curr = *root; curr != NULL; curr = curr->next)
        if (strcmp(label_end, curr->label_name) == 0)
 	  	    return curr->address;

    return -1;
}
/*------------------------------------------------------------*/
/*Free linked list label*/
void free_symbol_list(label **root)
{
    label* curr = *root;
    label* aux;
    while(curr != NULL)
    {
        aux  = curr;
        curr = curr->next;
        free(aux);
    }
    *root = NULL;
}
/*------------------------------------------------------------*/
/* Gets label structure root and a label name as string.      */
/* Returns a pointer to the label if true, NULL otherwise.    */
label *is_in_label_list(label **root,char *label_str)
{
    label* curr;
    for(curr = *root; curr != NULL; curr = curr->next)
        if (strcmp(label_str, curr->label_name) == 0)
 	  	    return curr;

    return NULL;
}
/*------------------------------------------------------------*/
/* Returns true if code flag in node in ON                    */
bool is_code_flag(label **root,char *label_str)
{
    label* curr;
    for(curr = *root; curr != NULL; curr = curr->next)
        if (strcmp(label_str, curr->label_name) == 0)
 			if(curr->is_code)
			       return true;

    return false;
}
/*------------------------------------------------------------*/
/* Returns true if extern flag in node in ON                  */
bool is_extern_flag(label **root,char *label_str)
{
    label* curr;
    for(curr = *root; curr != NULL; curr = curr->next)
        if (strcmp(label_str, curr->label_name) == 0)
 			if(curr->is_extern)
			       return true;
    
    return false;
}
/*------------------------------------------------------------*/
/* Turn on the flag to know label has code attribute */
void turn_on_code_flag(label *label_node)
{
    label_node->is_code = true;
}
/*------------------------------------------------------------*/
/* Turn on the flag to know label has data attribute */
void turn_on_data_flag(label *label_node)
{
    label_node->is_data = true;
}
/*------------------------------------------------------------*/
/* Turn on the flag to know label has entry attribute */
void turn_on_entry_flag(label *label_node)
{
    label_node->is_entry = true;
}
/*------------------------------------------------------------*/
/* Turn on the flag to know label has extern attribute */
void turn_on_extern_flag(label *label_node)
{
    label_node->is_extern = true;
}
/*------------------------------------------------------------*/
/*Turn on the attribute flag in node base on string buffer that includes declartion (.db,.dw,...) 
or commedns (add,move,jmp..)*/
void turn_on_attr_flag(label *label_node,char *buffer)
{
    struct cmd_lookup_element *p;
    int i = 0;
    for(p =  lookup_table; p->cmd != NULL; p++)
    if(strcmp(p->cmd,buffer) == 0)
    {
        i = p->label_dec;
        switch(i)
        {
            case CODE_DEC:
                turn_on_code_flag(label_node);
                break;
            case  DATA_DEC:
                turn_on_data_flag(label_node);
                break;
            case  ENTRY_DEC:
                turn_on_data_flag(label_node);
                break;
            case  EXTERN_DEC:
                turn_on_extern_flag(label_node);
                break;
            default:
                printf("Error Label is not declaer as needed!");
        }
    }
}