/*------------------------------------------------------------*/
/* Authors: Daniel Popov & Maor Maayan                        */
/* File   : second_pass.c                                     */
/*                                                            */
/* Description: Handles label operands and label attributes   */
/*------------------------------------------------------------*/
#include "second_pass.h"
bool second_pass(code_img **head_code, line **head_line, label **head_label, extra **head_extra)
{
    /*Initialization :       */
    char word[MAX_LINE_LENGTH];
    char labelop[MAX_LABEL_LENGTH];
    
    command_syntax status;
   
    code_img *cur_code;
    label    *cur_label;
    line     *cur_line;
    
    bool is_error;

    int index  = 0;
    
    cur_code   = NULL;
    cur_label  = NULL;
    cur_line   = *head_line;

    is_error   = false;
    
    while(cur_line != NULL)
    {
        /* Reset */
	    index = 0;
	    memset(labelop, '\0', MAX_LABEL_LENGTH);
        memset(word,    '\0', MAX_LINE_LENGTH);
        status = ERROR;
        /*All lines with second pass flag ON */
        if(cur_line->second_pass)
        {
            index += getword  (cur_line->line_str, word);
            get_label_from_end(cur_line->line_str, labelop); 

            if(!(cur_label = is_in_label_list(head_label, labelop)))
            {
                printf("Error: Label operand isn't defined at line %ld.\n", cur_line->line_number);
                is_error = true;
                cur_line = cur_line->next;
                continue;
            }

            if(islabel(word))
                index += getword(cur_line->line_str, word);
            /* Handels the labels that will be in .ent file*/
            if(cur_line->is_entry)
            {
                if(cur_label->is_extern)
                    printf("Error: Label cannot be external and internal at line %ld.\n", cur_line->line_number);
                else 
                    turn_on_entry_flag(cur_label);
                
                cur_line = cur_line->next;
                continue;
            }
            /* Returns a code node that matches current line address */
            cur_code = get_code_node(head_code, cur_line->address);
            status   = get_cmd_syntax(word);
	   
            switch(status)
            {
                case TWO_REGS_AND_LABEL:
                    if(!is_extern_flag(head_label, labelop))
                        cur_code->bits.I.immed = get_value(head_label, labelop) - (cur_line->address);
                    else
                    {
                        is_error = true;
                        printf("Error: Label operand is external in branch instruction at line %ld.\n", cur_line->line_number);
                    }
                    break;
                    
                case ONE_LABEL:
                case ONE_REG_OR_LABEL:
                    if(cur_label->is_entry || cur_label->is_extern)
                        add_extra_node(head_extra, cur_line, cur_label);
                    cur_code->bits.J.address = get_value(head_label, labelop);
                    break;
                    
                default:
                   break;
            }   
        } /* end of if second_pass */ 
        else if(!cur_line->next)
            return !is_error;

        if(cur_line->next == NULL)
	        return !is_error;
        
        cur_line = cur_line->next;
    } /* end while */
    return !is_error;
}
