/*------------------------------------------------------------*/
/* Authors: Daniel Popov & Maor Maayan                        */
/* File   : first_pass.c                                      */
/*                                                            */
/* Description: Validates lines and encodes data and code     */
/* into appropriate structures.                               */
/*------------------------------------------------------------*/
#include "first_pass.h"

/*------------------------------------------------------------*/
bool first_pass(code_img **head_code, line **head_line, label **head_label, FILE *inputfile)
{
    /* Declarations: */
    int j, index, arrlen;
    command_syntax status;
    attr attr_status; /* Label attributes */
    bool is_valid;    /* Gets false if there's an error in first pass */
    
    label    *cur_label;
    line     *cur_line;

    char buffer[MAX_LINE_LENGTH + EXTRANEOUS_LINE_BUFFER];
    char word[MAX_LINE_LENGTH];
    char label[MAX_LABEL_LENGTH];
    char extra_label[MAX_LABEL_LENGTH]; /* String for operand label           */
    char cmd[MAX_LABEL_LENGTH];         /* String for the command in the line */
    int  operands[3];                   /* Max reg amount                     */
    /* Initializations: */
    size_t size  = sizeof(operands) / sizeof(operands[0]); 
    int line_num = 1;
    cur_line     = NULL;
    cur_label    = NULL;
    
    is_valid     = true;

    /* Loop for each line in input file */
    while (fgets(buffer, sizeof buffer, inputfile))
    {
	    index = 0;
        buffer[strcspn(buffer, "\n")] = '\0';
     
        /* Guard Caluses: */
        if(is_comment(buffer) || is_empty_line(buffer, strcspn(buffer, "\n")))
        { 
            line_num++;
            continue; 
        }
        /* Checks length of line is valid */
        if(!is_line_length_valid(buffer, line_num))
            CONTINUE
        
        cur_line = add_line_node(head_line,buffer,line_num);
        index   += getword(buffer,word);
        /* Treats case of label definition:    */
        if(islabel(word)) /* Word end with ':' */
        {
            if(is_valid_label(word, line_num))
            {
                if(!is_in_label_list(head_label, word))
                {
                    strcpy(label, word);
                    index += getword(buffer + index, word);
                    turn_on_label(cur_line);
                }
                else 
                {
                    printf("Error: Label already defined at line %d.\n", line_num);
                    CONTINUE
                }
            }
            else 
                CONTINUE
        }
        
        if( (status = validate_line(buffer + index, word, line_num)) )
        {
            strcpy(cmd, word);
            attr_status = get_cmd_type(cmd);
            
            /* Encoding of data declarations */
            if(attr_status == DATA_DEC)
            {
                if(strlen(label)) 
                    add_label_node(head_label, cmd, label);
                
                if(status == STRING)
                {
                    char *string_op = get_string(buffer + index);
                    strcpy(word,string_op);
                    encode_string(word);
                    free(string_op);
                }
                else
                {
                    long *operands_dec;      
                    arrlen  = is_valid_nums(buffer + index, line_num);
                    operands_dec = get_nums(buffer + index, &operands_dec);
                    encode_num_operands(operands_dec, cmd, arrlen);
                    free(operands_dec);
                }
            } 
            /* Defining internal and external labels */
            else if(attr_status == ENTRY_DEC || attr_status == EXTERN_DEC)
            {
                index += getword(buffer  + index, extra_label);
                cur_label   = is_in_label_list(head_label, extra_label);
                
                if(attr_status  == ENTRY_DEC) 
                {
                    if(cur_label)
			        {
                        if(cur_label->is_extern)
                        {
                            printf("Error: Label cannot be external and internal at line %d.\n", line_num);
                            CONTINUE
                        }
                       		turn_on_entry_flag(cur_label);
			        }
                    else
                    {
                        turn_on_second_pass(cur_line);
                        turn_on_entry(cur_line);
                    }
                }
                else if(attr_status == EXTERN_DEC)
                {
                    if(!cur_label)
                        add_label_node(head_label, cmd, extra_label);
                    else if(!(cur_label->is_extern))
                    {
                        printf("Error: Label already defined at line %d.\n", line_num);
                        CONTINUE
                    }
                    else
                    {
                        line_num++;
                        continue;
                    }
                }
            }
            /* Encoding instructions: */
            else if(attr_status == CODE_DEC)
            {
                opcode op  = get_op(cmd);
                funct  fun = get_fun(cmd);

                if(strlen(label))
                    add_label_node(head_label, cmd, label);
                /* Command syntax status gets the type of operands to expect. */
                switch(status)
                {
                    case TWO_REGS:
                        get_two_regs(buffer + index,operands);
                        break;
                        
                    case THREE_REGS:
                    case TWO_REGS_NUM_IN_MID:
                        get_three_regs(buffer + index,operands); 
                        break;
                        
                    case TWO_REGS_AND_LABEL:
                         get_two_regs(buffer + index,operands);
                            
                    case ONE_LABEL:
                        get_label_from_end(buffer,extra_label);
                        turn_on_second_pass(cur_line);
                        break;

                    case ONE_REG_OR_LABEL:
                        /* Check if oprand in the line is label */
                        j = 0; 
			            SKIP_SPACE(buffer,j)
                        while(isalpha(buffer[j++]))
                            ;
                        SKIP_SPACE(buffer,j)
                        if(buffer[j++] != '$')
                        {  
                            get_label_from_end(buffer,extra_label);
                            turn_on_second_pass(cur_line);
                        }
                        else
                            get_one_regs(buffer + index,operands);
                                
                        break;
                        
                    case NONE:
                        get_one_regs(buffer + index,operands);           
                        break;
                    default:
                        break;
                }
                add_node_code(head_code, cur_line, head_label, operands, op, fun, extra_label, status);
                IC += 4;
                /* Reset arrays */ 
   		        memset(label,       '\0', MAX_LABEL_LENGTH);
       	        memset(extra_label, '\0', MAX_LABEL_LENGTH);
                memset(word,        '\0', MAX_LINE_LENGTH);
                memset(cmd ,        '\0', MAX_LABEL_LENGTH);
 	            clear(operands,size);
            } /* End of CODE_DEC */          
        } /* End of validate_line */ 
    if(status == ERROR)
        is_valid = false;
        
    line_num++;
    } /* End of while loop & first pass */
    return is_valid;
}
/*------------------------------------------------------------*/
/* Gets the head of the table and updates all address value.  */
/* If the label has data attribute, adds ICF.                 */
void update_label_table(label **root)
{
    label *curr = *root;
    while(curr)
    {
        if(curr->is_data)
            curr->address += IC;

        curr = curr->next;
    }
}
/*------------------------------------------------------------*/

int validate_line(char *buffer,char *cmd,int line_num)
{
    command_syntax status = get_cmd_syntax(cmd);
    int j = 0;
    switch(status)
    {       
        case THREE_REGS: 
            if(regs_check(buffer, line_num, false, 3))
                return status;
            break;

        case TWO_REGS:
            if(regs_check(buffer, line_num, false, 2))
                return status;
            break;

        case TWO_REGS_NUM_IN_MID:
            if(regs_check(buffer, line_num, true, 3)) 
                return status;
            break;

        case TWO_REGS_AND_LABEL:
            if(is_valid_branchop(buffer, line_num))
                return status;
            break;

        case ONE_LABEL:
            if(is_valid_label(buffer, line_num))
                return status;
            break;
           
        case ONE_REG_OR_LABEL:
            if(is_valid_singleop(buffer, line_num))
                return status;
            break;

        case DH: 
        case DW: 
        case DB:
            if(is_valid_nums(buffer, line_num) > 0)
                return status;
            break;

        case STRING:
            if(is_valid_string(buffer, line_num))      
                return status;
            break;

        case NONE:
            SKIP_SPACE(buffer, j)
            if(is_line_over(buffer[j]))
                return status;
            else printf("Error: Extraneous operand at line %d.\n", line_num);
            break;

        case ERROR:
            printf("Error: Unknown command \"%s\" at line %d.\n", cmd, line_num);
    }  
    return ERROR;
}
/*------------------------------------------------------------*/
/*Fills the array type int with 0 */
void clear(int *arr,int size)
{
    int i;
    for(i  = 0; i < size; i++)
    arr[i] = 0;
}
