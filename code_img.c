/*------------------------------------------------------------*/
/* Authors: Daniel Popov & Maor Maayan                        */
/* File   : code_img.c                                        */
/*                                                            */
/* Description: This file contains the code image structure   */
/* implemented as a linked list and functions to manipulate   */
/* the structure.                                             */
/*------------------------------------------------------------*/
/* Includes: */
#include "code_img.h"

/*Encode to binary R field to node code image*/
void R_zero_op_fill(code_img *new_node, int *operands, opcode op, funct fun)
{
    new_node->bits.R.rs     = operands[0];
    new_node->bits.R.rt     = operands[1];
    new_node->bits.R.rd     = operands[2];
    new_node->bits.R.opcode = op;
    new_node->bits.R.funct  = fun;
    new_node->bits.R.no_use = 0;
}
/*------------------------------------------------------------*/
/*Encode to binary R field to node code image*/
void R_one_op_fill(code_img *new_node, int *operands, opcode op, funct fun)
{
    new_node->bits.R.rs     = operands[0];
    new_node->bits.R.rd     = operands[1];
    new_node->bits.R.rt     = 0;
    new_node->bits.R.opcode = op;
    new_node->bits.R.funct  = fun;
    new_node->bits.R.no_use = 0;
}
/*------------------------------------------------------------*/
/*Encode to binary I field to node code image*/
void I_two_regs_one_num_fill(code_img *new_node, int *operands, opcode op)
{
    new_node->bits.I.rs     = operands[0];
    new_node->bits.I.rt     = operands[2];
    new_node->bits.I.immed  = operands[1];
    new_node->bits.I.opcode = op;
} 
/*------------------------------------------------------------*/
/*Encode to binary I field to node code image*/
void I_two_regs_one_label_fill(code_img *new_node, line *line_node, label **head_label, int *operands, opcode op)
{
    new_node->bits.I.rs     = operands[0];
    new_node->bits.I.rt     = operands[1];
    new_node->bits.I.opcode = op;
}
/*------------------------------------------------------------*/
/*Encode to binary J field to node code image*/
void J_one_reg_fill(code_img *new_node, int *operands, opcode op)
{
    new_node->bits.J.opcode  = op;
    new_node->bits.J.reg     = 1;
    new_node->bits.J.address = operands[0];
}
/*------------------------------------------------------------*/
/*Encode to binary J field to node code image*/
void J_one_label_fill(code_img *new_node, line *line_node, label **head_label, opcode op) 
{
    new_node->bits.J.opcode  = op;
    new_node->bits.J.reg     = 0;
}
/*------------------------------------------------------------*/
/*Encode to binary J field to node code image*/
void J_stop_fill(code_img *new_node, opcode op)
{
    new_node->bits.J.opcode  = op;
    new_node->bits.J.reg     = 0;
    new_node->bits.J.address = 0;
}
/*------------------------------------------------------------*/
/*Returns a pointer to node in code image if address in paramter match address in node*/
code_img *get_code_node(code_img **root, unsigned long address)
{
    code_img *curr = *root;
    while(curr)
    {
        if(curr->address == address)
            return curr;
        curr = curr->next;
    }    
    return NULL;
}
/*------------------------------------------------------------*/
/*Prints all binary field of each node in code_img */
void print_code_img(code_img *head_code, FILE *outputfile)
{
	unsigned long address = 100;
    int mask = 0xff;
    
    while(head_code)
    {
        unsigned char byte[4] = {0,0,0,0};
        unsigned int  bin     = head_code->bits.bin;
        int i = 0;
        address = head_code->address;

        fprintf(outputfile, "\n");
        if (address < 1000) fprintf(outputfile, "0");    /* Leading zero  */
        fprintf(outputfile, "%ld ", address);

        while(i < 4)
        {
            byte[i]  = bin & mask;
            bin    >>= 8;
            if(byte[i] <= 0xf) fprintf(outputfile,"0"); /* Leading zero */
            fprintf(outputfile, "%X ", byte[i++]);
        }
        head_code = head_code->next;
    }
}
/*------------------------------------------------------------*/
/*Initialize node type code_img */
void init_code_node(code_img *node_code)
{
    node_code->next        = NULL;
}
/*------------------------------------------------------------*/
/*Add new node to code image and return a pointer to new node in code image*/
code_img *add_node_code(code_img **root, line *line_node, label **head_label, int *operands, opcode op, funct fun , char *labelop, command_syntax status)
{
    code_img *curr     = *root;
    code_img *new_node = (code_img *)validatedmalloc(sizeof(code_img));
    init_code_node(new_node);
    new_node->address  = IC;
    /*Base on the command in line encode the right field*/
    switch(status)
    {       
        /* Commands with three regs syntax */   
        case THREE_REGS:
            R_zero_op_fill(new_node, operands, op, fun);
            break;
        /* Commands with two regs syntax */               
        case TWO_REGS:
            R_one_op_fill(new_node, operands, op, fun);
            break;
        /*Commands with two regs and regular num in the mid syntax*/                           
        case TWO_REGS_NUM_IN_MID:
            I_two_regs_one_num_fill(new_node, operands, op);
            break;
        /*Commands with two regs and regular num in the mid syntax*/                                       
        case TWO_REGS_AND_LABEL:
            I_two_regs_one_label_fill(new_node, line_node, head_label, operands, op);
            break;
        /*Commands with one label syntax*/                                           
        case ONE_LABEL:
            J_one_label_fill(new_node, line_node, head_label, op);
            break;
        /*Commands with one label syntax*/                                                
        case ONE_REG_OR_LABEL:
            if(strlen(labelop))
                J_one_label_fill(new_node, line_node, head_label, op);  
            else
                J_one_reg_fill(new_node, operands, op);
            break;
        /*Command with none parmeters syntax*/                                                    
        case NONE:
            J_stop_fill(new_node, op);
            break;
        default:
            break;
    }
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
/*Free each node in link list type code_img */
void free_code_list(code_img **root)
{
    code_img* curr = *root;
    code_img* aux;
    while(curr != NULL)
    {
        aux  = curr;
        curr = curr->next;
        free(aux);
    }
    *root=NULL;
}