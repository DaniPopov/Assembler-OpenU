/*------------------------------------------------------------*/
/* Authors: Daniel Popov & Maor Maayan                        */
/* File   : label_structure.h                                 */
/*                                                            */
/* Description:                                               */
/*------------------------------------------------------------*/
#ifndef LABEL_STRUCTURE_H
#define LABEL_STRUCTURE_H

#include "globals.h"
#include "parse.h"

/* Symbol Node structer in the link list of labels: */
typedef struct Symbol_Node
{
    unsigned long address;

    char label_name[MAX_LABEL_LENGTH];

    struct Symbol_Node* next;

    bool  is_code;
    bool  is_data;
    bool  is_entry;
    bool  is_extern;


} label;


/* Initializing symbol struct node */
void init_label_node(label *label_node);

/* Append label in node*/
void append_label(label *label_node,char *str_label);

/* Append value of the symbol in node */
void append_value(label *label_node,unsigned long address);

/* Insert a node in linked list with the label */
void add_label_node(label **root,char *str_cmd,char *str_label);

/* Free linked list symbol */
void free_symbol_list(label** root);

/* Remove node from the link list symbol */
void remove_label(label **root,char *str_label);

/* Get true if label is inside the link list symbol */
label *is_in_label_list(label **root,char *label_str);

/* Return true if code flag is ON */
bool is_code_flag(label **root,char *label_str);

/* Return true if extren flag is ON */
bool is_extern_flag(label **root,char *label_str);

/* Turn on the code attribute flag */
void turn_on_code_flag(label *label_node);

/* Turn on the data attribute flag */
void turn_on_data_flag(label *label_node);

/* Turn on the entry attribute flag */
void turn_on_entry_flag(label *label_node);

/* Turn on the flag to know label has extern attribute */
void turn_on_extern_flag(label *label_node);

/* Turn on the attributes flags (is_code,is_data,...) */
void turn_on_attr_flag(label *label_node,char *buffer);

/* Get the address in of the node label */
unsigned long get_value(label **root,char *label_end);


#endif