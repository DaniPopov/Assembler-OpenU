/*------------------------------------------------------------*/
/* Authors: Daniel Popov & Maor Maayan                        */
/* File   : globals.c                                         */
/*                                                            */
/* Description: Defines the lookup table and functions        */
/* getting data from it.                                      */
/* Defines macros and external variables used throughout the  */
/* Two-Pass Assembler project.                                */
/*------------------------------------------------------------*/
#include "globals.h"

unsigned long IC = INITIAL_IC_VALUE, DC = 0;
/*------------------------------------------------------------*/
/* A lookup table for opcode, funct, commands syntax and declarations:  */

struct cmd_lookup_element lookup_table[] = 
{
    {"add"    ,ADD_OP  ,ADD_FUNCT  ,THREE_REGS          ,CODE_DEC  },
    {"sub"    ,SUB_OP  ,SUB_FUNCT  ,THREE_REGS          ,CODE_DEC  },
    {"and"    ,AND_OP  ,AND_FUNCT  ,THREE_REGS          ,CODE_DEC  },
    {"or"     ,OR_OP   ,OR_FUNCT   ,THREE_REGS          ,CODE_DEC  },
    {"nor"    ,NOR_OP  ,NOR_FUNCT  ,THREE_REGS          ,CODE_DEC  },
    {"move"   ,MOVE_OP ,MOVE_FUNCT ,TWO_REGS            ,CODE_DEC  },
    {"mvhi"   ,MVHI_OP ,MVHI_FUNCT ,TWO_REGS            ,CODE_DEC  },
    {"mvlo"   ,MVLO_OP ,MVLO_FUNCT ,TWO_REGS            ,CODE_DEC  },
    {"addi"   ,ADDI_OP ,NONE_FUNCT ,TWO_REGS_NUM_IN_MID ,CODE_DEC  },
    {"subi"   ,SUBI_OP ,NONE_FUNCT ,TWO_REGS_NUM_IN_MID ,CODE_DEC  },
    {"andi"   ,ANDI_OP ,NONE_FUNCT ,TWO_REGS_NUM_IN_MID ,CODE_DEC  },
    {"ori"    ,ORI_OP  ,NONE_FUNCT ,TWO_REGS_NUM_IN_MID ,CODE_DEC  },
    {"nori"   ,NORI_OP ,NONE_FUNCT ,TWO_REGS_NUM_IN_MID ,CODE_DEC  },
    {"bne"    ,BNE_OP  ,NONE_FUNCT ,TWO_REGS_AND_LABEL  ,CODE_DEC  },
    {"beq"    ,BEQ_OP  ,NONE_FUNCT ,TWO_REGS_AND_LABEL  ,CODE_DEC  },
    {"blt"    ,BLT_OP  ,NONE_FUNCT ,TWO_REGS_AND_LABEL  ,CODE_DEC  },
    {"bgt"    ,BGT_OP  ,NONE_FUNCT ,TWO_REGS_AND_LABEL  ,CODE_DEC  },
    {"lb"     ,LB_OP   ,NONE_FUNCT ,TWO_REGS_NUM_IN_MID ,CODE_DEC  },
    {"sb"     ,SB_OP   ,NONE_FUNCT ,TWO_REGS_NUM_IN_MID ,CODE_DEC  },
    {"lw"     ,LW_OP   ,NONE_FUNCT ,TWO_REGS_NUM_IN_MID ,CODE_DEC  },
    {"sw"     ,SW_OP   ,NONE_FUNCT ,TWO_REGS_NUM_IN_MID ,CODE_DEC  },
    {"lh"     ,LH_OP   ,NONE_FUNCT ,TWO_REGS_NUM_IN_MID ,CODE_DEC  },
    {"sh"     ,SH_OP   ,NONE_FUNCT ,TWO_REGS_NUM_IN_MID ,CODE_DEC  },
    {"jmp"    ,JMP_OP  ,NONE_FUNCT ,ONE_REG_OR_LABEL    ,CODE_DEC  },
    {"la"     ,LA_OP   ,NONE_FUNCT ,ONE_LABEL           ,CODE_DEC  },
    {"call"   ,CALL_OP ,NONE_FUNCT ,ONE_LABEL           ,CODE_DEC  },
    {"stop"   ,STOP_OP ,NONE_FUNCT ,NONE                ,CODE_DEC  },
    {".dh"    ,NONE_OP ,NONE_FUNCT ,DH                  ,DATA_DEC  },
    {".dw"    ,NONE_OP ,NONE_FUNCT ,DW                  ,DATA_DEC  },
    {".db"    ,NONE_OP ,NONE_FUNCT ,DB                  ,DATA_DEC  },
    {".asciz" ,NONE_OP ,NONE_FUNCT ,STRING              ,DATA_DEC  },
    {".entry" ,NONE_OP ,NONE_FUNCT ,ONE_LABEL           ,ENTRY_DEC },
    {".extern",NONE_OP ,NONE_FUNCT ,ONE_LABEL           ,EXTERN_DEC}
};

/*------------------------------------------------------------*/
/* Gets a word without white space.                           */
/* Returns true if it's a reserved word.                      */
bool is_reserved_word(char *cmd)
{
    struct cmd_lookup_element *p;
    for(p = lookup_table; p->cmd; p++)
        if(strcmp((p->cmd),cmd) == 0)
            return true;
    
    return false;
}
/*------------------------------------------------------------*/
/* Gets a command and return the enum command_syntax that matches the command */
/* inside the lookup_table */
command_syntax get_cmd_syntax(char *cmd)
{
    struct cmd_lookup_element *p;
    command_syntax status = ERROR;

    for(p = lookup_table; p->cmd; p++)
        if(strcmp(p->cmd,cmd) == 0)
            status = p->syntax;
    
    return status;
}
/*------------------------------------------------------------*/
/* Gets a command and return the opcode that matchs the command */
/* inside the lookup_table */
opcode get_op(char *cmd)
{
    struct cmd_lookup_element *p;
    for (p = lookup_table; p->cmd; p++)
        if (strcmp(p->cmd,cmd) == 0)
            return p->op; 

    return NONE_OP;
}
/*------------------------------------------------------------*/
/* Gets a command and return the funct that matchs the command */
/* inside the lookup_table */
funct get_fun(char *cmd)
{
    struct cmd_lookup_element *p;
    for (p = lookup_table; p->cmd; p++)
        if (strcmp(p->cmd,cmd) == 0)
            return p->fun; 

    return NONE_FUNCT;
}
/*------------------------------------------------------------*/
/* Gets a command and return the enum attr that match the command */
/* inside the lookup_table */
/* DATA_DEC,EXTERN_DEC,ENTRY_DEC,CODE_DEC */
int get_cmd_type(char *cmd)
{
    struct cmd_lookup_element *p;
    for (p = lookup_table; p->cmd; p++)
        if (strcmp(p->cmd,cmd) == 0)
            return p->label_dec; 

    return -1;
}
/*------------------------------------------------------------*/