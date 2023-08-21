/*------------------------------------------------------------*/
/* Authors: Daniel Popov & Maor Maayan                        */
/* File   : line_structure.h                                  */
/*                                                            */
/* Description: A linked list for holding the lines and their */
/* attributes and flags mainly used for the second pass.      */
/*------------------------------------------------------------*/
#ifndef LINE_STRUCTURE_H
#define LINE_STRUCTURE_H

#include "globals.h"
#include "parse.h"
/*------------------------------------------------------------*/
typedef struct Line_Node
{
    long line_number; /* line number */
    
    unsigned long address;/*for IC */
    
    /* Arrays */
    char line_str[MAX_LINE_LENGTH + EXTRANEOUS_LINE_BUFFER]; /* str representation of the line  */
    
    /* Pointer */
    struct Line_Node* next;

    /* Flags: */
    bool is_label;/*if first word in line is label*/ 
    bool is_entry;
    bool is_extern;
    bool is_error;/* if an error is found */
    bool second_pass;/*if second pass is needed*/
    
} line;
/*------------------------------------------------------------*/
/* Initializing line node */
void init_line_node(line *line_list);

/* Add line node to the linekd list */
line *add_line_node(line **root,char *str_line,int line_num);

/* Add the line to the node */
void append_line(line *line_node,char *str_line);
/* Add line num of the file to the node */
void append_line_num(line *line_node,int line_num);
/* Add IC to the node line */
void append_address(line *line_node);

/* free linekd list line */
void free_line_list(line **root);
/*------------------------------------------------------------*/
/* Turn on functions flags in the node: */

void turn_on_extern(line *line_node);

void turn_on_entry(line *line_node);

void turn_on_error_flag(line *line_node);

void turn_on_second_pass(line *root);

void turn_on_label(line *root);

#endif