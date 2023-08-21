/*------------------------------------------------------------*/
/* Authors: Daniel Popov & Maor Maayan                        */
/* File   : code_img.h                                        */
/*                                                            */
/* Description: This file contains the code image structure   */
/* implemented as a linked list and functions to manipulate   */
/* the structure.                                             */
/*------------------------------------------------------------*/
#ifndef CODE_IMG_H
#define CODE_IMG_H
/* Includes: */
#include "parse.h"
#include "line_structure.h"
#include "label_structure.h"
#include "operands.h"
/*------------------------------------------------------------*/
/*R field*/
typedef struct R 
{
    unsigned int no_use: 6;
    unsigned int funct:  5;
    unsigned int rd:     5;
    unsigned int rt:     5;
    unsigned int rs:     5;
    unsigned int opcode: 6;
} Rfield;

/*I field*/
typedef struct I
{
    signed   int immed: 16;
    unsigned int rt:     5;
    unsigned int rs:     5;
    unsigned int opcode: 6;
} Ifield;

/*J field*/
typedef struct J
{
    unsigned int address: 25;
    unsigned int reg:      1;
    unsigned int opcode:   6;
} Jfield;

/*Node struct of code image*/
typedef struct code_img_node
{
    unsigned long address;
    struct code_img_node *next; 

    union
    {
        unsigned long bin; 
        Rfield R;
        Ifield I;
        Jfield J; 
    } bits;
} code_img;
/*------------------------------------------------------------*/

/* Fill R bitfield */
void R_zero_op_fill(code_img *new_node, int *operands, opcode op, funct fun);

/* Fill R bitfield */
void R_one_op_fill (code_img *new_node, int *operands, opcode op, funct fun);

/* Fill I bitfield */
void I_two_regs_one_num_fill(code_img *new_node, int *operands, opcode op);

/* Fill I bitfield */
void I_two_regs_one_label_fill(code_img *new_node, line *line_node, label **head_label, int *operands, opcode op);

/* Fill J bitfield */
void J_one_reg_fill(code_img *new_node, int *operands, opcode op);

/* Fill J bitfield */
void J_one_label_fill(code_img *new_node, line *line_node, label **head_label, opcode op);

/* Fill J bitfield */
void J_stop_fill(code_img *new_node, opcode op);

/* Add node type code_img to code image */
code_img *add_node_code(code_img **root, line *line_node, label **head_label, int *operands, opcode op, funct fun , char *labelop, command_syntax status);

/* Get pointer to Node in code image base on address */
code_img *get_code_node(code_img **root, unsigned long address);

/* Prints the nodes of link list code_img  to output file */
void print_code_img(code_img *head_code, FILE *outputfile);

/* Free all nodes of code list in code_img */
void free_code_list(code_img **root);

/* Initialize code_img node */ 
void init_code_node(code_img *node_code);

#endif