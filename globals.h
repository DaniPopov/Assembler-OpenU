/*------------------------------------------------------------*/
/* Authors: Daniel Popov & Maor Maayan                        */
/* File   : globals.h                                         */
/*                                                            */
/* Description: Defines the lookup table and functions        */
/* getting data from it.                                      */
/* Defines macros and external variables used throughout the  */
/* Two-Pass Assembler project.                                */
/*------------------------------------------------------------*/

#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*------------------------------------------------------------*/
typedef enum {false, true} bool; 
/*------------------------------------------------------------*/

#define MAX_ADDRESS_VALUE      33554431 /* [0,2^25 -1]                   */
#define MAX_ATTRIBUTE_LENGTH   10       /* code-data-entry-external      */
#define MAX_LABEL_LENGTH       32       /* label + ':'                   */
#define MAX_LINE_LENGTH        81       /* 80 chars + 1 line ending char */
#define EXTRANEOUS_LINE_BUFFER 100
#define INITIAL_IC_VALUE       100

/*------------------------------------------------------------*/
#define SKIP_SPACE(str,i) \
    while (str[(i)] && ( str[(i)] == ' ' || str[(i)] == '\t') )\
        (++(i));
/*------------------------------------------------------------*/
/* Commands opcode */
typedef enum opcodes 
{
    /* First Group */
    ADD_OP  = 0,
    SUB_OP  = 0,
    AND_OP  = 0,
    OR_OP   = 0,
    NOR_OP  = 0,
    MOVE_OP = 1,
    MVHI_OP = 1,
    MVLO_OP = 1,
    /* END First Group */

    /* Second Group    */  
    ADDI_OP = 10,
    SUBI_OP = 11,
    ANDI_OP = 12,
    ORI_OP  = 13,
    NORI_OP = 14,
    BNE_OP  = 15,
    BEQ_OP  = 16,
    BLT_OP  = 17,
    BGT_OP  = 18,
    LB_OP   = 19,
    SB_OP   = 20,
    LW_OP   = 21,
    SW_OP   = 22,
    LH_OP   = 23,
    SH_OP   = 24,
    /* END Second Group */

    /* Third Group */
    JMP_OP  = 30,
    LA_OP   = 31,
    CALL_OP = 32,
    STOP_OP = 63,
    /* END Third Group */
    /* Default */
    NONE_OP = -1
} opcode;
/*------------------------------------------------------------*/

/** Commands funct */
 typedef enum funct 
{
    /* OPCODE 0 */
    ADD_FUNCT  = 1,
    SUB_FUNCT  = 2,
    AND_FUNCT  = 3,
    OR_FUNCT   = 4,
    NOR_FUNCT  = 5,
    /* OPCODE 1 */
    MOVE_FUNCT = 1,
    MVHI_FUNCT = 2,
    MVLO_FUNCT = 3,
    /* Default  */
    NONE_FUNCT = -1
} funct;

/*------------------------------------------------------------*/
/* Command & declartions syntax type:                         */
typedef enum command_syntax 
{
    ERROR = 0,
    DB    = 1,
    DH    = 2,
    DW    = 4,
    THREE_REGS,
    TWO_REGS,
    TWO_REGS_NUM_IN_MID,
    TWO_REGS_AND_LABEL,
    ONE_LABEL,
    ONE_REG_OR_LABEL,
    STRING,
    NONE
} command_syntax;
/*------------------------------------------------------------*/
typedef enum attributes_types
{
    /* .dh .dw .asciz .db declaration */
    DATA_DEC,
    /* .extern declaration */
    EXTERN_DEC,
    /* .entry declaration  */
    ENTRY_DEC,
    /* CODE instruction    */
    CODE_DEC
} attr;


/*------------------------------------------------------------*/
/* Pointer to the lookup tabel in globals.c */
struct cmd_lookup_element 
{
	char *cmd;
	opcode op;
	funct fun; 
	command_syntax syntax;  
    attr label_dec;
};
/*------------------------------------------------------------*/
/* Gets a word and checks if word is already defined as commands */
/* True -> if word is defined */
bool is_reserved_word(char * word);

/* Gets a command and return enum command_syntax that match the command */
command_syntax get_cmd_syntax(char *cmd);

/* Gets a command and return opcode of the command */
opcode get_op(char *cmd);

/* Gets a command and return funct of the command */
funct  get_fun(char *cmd);

/* Gets a command and return enum attr */
/* DATA_DEC,EXTERN_DEC,ENTRY_DEC,CODE_DEC */
int    get_cmd_type(char *cmd);
/*------------------------------------------------------------*/
extern struct cmd_lookup_element lookup_table[33]; /* 33 = Amount of reserved words */
extern unsigned long IC, DC;
#endif