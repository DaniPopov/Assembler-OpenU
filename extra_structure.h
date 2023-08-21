/*------------------------------------------------------------*/
/* Authors: Maor Maayan & Daniel Popov                        */
/* File   : assembler.c                                       */
/*                                                            */
/* Description: Stores and prints the entries and externals   */
/* varible usage into .ext and .ent files.                    */
/*------------------------------------------------------------*/
#ifndef EXTRA_STRUCTURE_H
#define EXTRA_STRUCTURE_H

#include "globals.h"
#include "line_structure.h"
#include "label_structure.h"
/*------------------------------------------------------------*/


typedef struct extra_node
{
    unsigned long address;

    char label[MAX_LABEL_LENGTH];

    bool is_extern;

    struct extra_node *next;
} extra;
/*------------------------------------------------------------*/

/*Initialize node type extra */
void init_extra_node(extra *extra_node);
/*Add node to the link list type extra */
void add_extra_node(extra **root,line *cur_line ,label *cur_label);
/*Prints all nodes of link list to .ent and .ext files */
void print_extra(extra **head_extra, char *filename);
/*Free all nodes in link list type extra */
void free_extra_list(extra **root);

#endif