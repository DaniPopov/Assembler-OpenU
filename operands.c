/*------------------------------------------------------------*/
/* File   : operands.h                                        */
/* Authors: Maor Maayan & Daniel Popov                        */
/*                                                            */
/* Description: Functions for getting and validating operands.*/
/*------------------------------------------------------------*/
#include "globals.h"
#include "parse.h"
#include "operands.h"
/*------------------------------------------------------------*/
/* Gets line that includes register operands only.            */
/* Immed is true if the second operand is an immediate value. */
/* Returns number of operands if valid else returns INT_MIN.  */ 

bool regs_check(char *subuffer, int linenum, bool immed, int required_count)
{
    int local_count = 0; /* Amount of valid register integer */
    local_count     = is_valid_regs(subuffer, linenum, immed);
    
    if ((local_count != required_count) && (local_count > 0))
        printf("Error: %d register operands expected at line %d.\n", required_count, linenum);

    return (local_count == required_count) && (local_count > 0);
}
/*------------------------------------------------------------*/
/* Gets a pointer to a string operand.                        */
/* Returns a pointer to an allocated string.                  */

char *get_string(char *subuffer)
{   
    int   i, j;
    char *str = (char *)validatedcalloc(MAX_LINE_LENGTH, sizeof(char));
    i = j = 0;
    
    SKIP_SPACE(subuffer, i)
        
    if(subuffer[i++] == '"')
        while(subuffer[i] != '"')
            str[j++] = subuffer[i++];
    
    return str;
}
/*------------------------------------------------------------*/
/* Gets a string of integer operands and extracts them.       */
/* Returns a pointer to the allocated long array.             */

long *get_nums(char *token, long **arr)
{
    const char delim[2] = ",";
    int   i   = 0;
    *arr = (long *)validatedmalloc(sizeof(long));

    token 	  = strtok(token, delim);
	**arr 	  = atol(token);
    token     = strtok(NULL,  delim);

    while(token)
    {
    	i++;
        *arr = (long *)validatedrealloc(*arr,(sizeof(long)*(i+1)));
        (*arr)[i] = atol(token);
	    token     = strtok(NULL,delim);
    }
    return *arr;
}
/*------------------------------------------------------------*/
/* Gets .asciz string operand and validates it.               */

bool is_valid_string(char *subuffer, int linenum)
{
    int i = 0;
    
    SKIP_SPACE(subuffer,i)
        
    if(subuffer[i++] != '"')
    {
        printf("Error: '\"' expected before string operand at line %d.\n", linenum);
        return false;
    }
    while(isprint(subuffer[i]) && !is_line_over(subuffer[i]) && subuffer[i] != '"')
        i++;
    if(!isprint(subuffer[i]))
    {
        printf("Error: Non-printable character in string operand at line %d.\n", linenum);
        return false;
    } 
    else if(subuffer[i] != '"')
    {
        printf("Error: '\"' expected after string operand at line %d.\n", linenum);
        return false;
    }
    i++;
    SKIP_SPACE(subuffer,i)
    if(!is_line_over(subuffer[i]))
    {
        printf("Error: Extraneous operand at line %d.\n", linenum);
        return false;
    }
    return true;
}
/*------------------------------------------------------------*/
/* Checks if .dh .db .dw operands are valid.                  */
/* Gets a string of operands and line number.                 */
/* Returns amount of (if)valid operands, INT_MIN otherwise.   */

int is_valid_nums(char *subuffer, int linenum)
{
    int i, counter;
    i = counter = 0;
    SKIP_SPACE(subuffer,i)
    
    if(is_sign(subuffer[i]))
        i++;

    if(isdigit(subuffer[i])) 
        i++;
    else
    {
       printf("Error: Number expected at line %d.\n",linenum);        
       return INT_MIN;
    }
    
    while(isdigit(subuffer[i]))
        i++;
    
    counter++;     
    SKIP_SPACE(subuffer,i)
    
    if(is_line_over(subuffer[i])) return counter;
    
    else if(subuffer[i++] != ',')
    {
        printf("Error: ',' expected at line %d.\n",linenum);
        return INT_MIN;
    }
    
    return counter += is_valid_nums(subuffer+i,linenum);
}
/*------------------------------------------------------------*/
/* Validates branch instruction's operands.                   */
/* Gets a line of operands and seperates them.                */
/* Returns true if both register and label operands are valid.*/

int is_valid_branchop(char *line, int linenum)
{
    int commacounter, i;
    bool regsflag, labelflag; /* Flags for regs and label validation */
    regsflag = labelflag = false;
    commacounter = i =  0;
    
    while(!is_line_over(line[i]) && commacounter < 2)
        if(line[i++] == ',')
            commacounter++;
    
    if(line[i-1] == ',')
        line[i-1] = '\0';    /* Seperates the regs and label */
    else
        printf("Error: Not enough operands at line %d.\n", linenum);
    
    regsflag  = regs_check(line, linenum, false, 2);
    labelflag = is_valid_label((line + i), linenum);
    line[i-1] = ',';        /* Returns the line back to normal */ 
    
    return (regsflag && labelflag);
}
/*------------------------------------------------------------*/
/* Gets line that includes register operands only             */
/* without label or command.                                  */
/* Immed is true if the second operand is an immediate value. */
/* Returns number of operands if valid else returns INT_MIN.  */

int is_valid_regs(char *subuffer, int linenum, bool immed)
{
    int regcounter, i, reg;
    regcounter = i = reg = 0;
    
    SKIP_SPACE(subuffer,i)
        
    if(subuffer[i] != '$') 
    {
        printf("Error: '$' expected at line %d.\n",linenum);
        return INT_MIN;
    }
    else if(isdigit(subuffer[++i]))
    {
        reg = subuffer[i] - '0'; /* Saves the value of the char into integer */
        i++;
        if (isdigit(subuffer[i])) /* In case the register has 2 digits */
        {
            reg = reg * 10 + (subuffer[i] - '0'); 
            if(!is_in_reg_range(reg))
            {
                printf("Error: Register out of range at line %d.\n",linenum);
                return INT_MIN;
            }
            
            i++;
			SKIP_SPACE(subuffer,i)                                         /* AFTER_DIGIT macro start */
    
		    if (is_line_over(subuffer[i])) return regcounter+1;

		    else if(subuffer[i] == ',')
		    {
		        if(immed)
		        {
		            immed = false;
		            i += is_valid_immed(subuffer+i+1, linenum);
		            if(i < 0)
		                return INT_MIN;

		            regcounter = 1;
		        }
		        SKIP_SPACE(subuffer,i)

		        if(!is_line_over(subuffer[i]))
		           return (regcounter += 1 + is_valid_regs(subuffer+i+1,linenum,immed));

		        printf("Invalid operand: Lone ',' at line %d.\n",linenum);
		    }                               
            else
                printf("Error: Comma expected at line %d.\n",linenum);      /* AFTER_DIGIT macro end */
        }
        AFTER_DIGIT(subuffer,i)
    }
    else
    {
        printf("Error: Digit expected at line %d.\n",linenum); 
    }
    return INT_MIN;
}
/*------------------------------------------------------------*/
/* Gets a string of operands, Expects an integer value and    */
/* a comma.                                                   */
/* Returns the index of subuffer if operand is valid.         */

int is_valid_immed(char* subuffer, int linenum)
{
    int i = 0;

    SKIP_SPACE(subuffer,i)

    if(is_sign(subuffer[i]))
        i++;
    
    if(isdigit(subuffer[i])) 
        i++;
    else
    {
        printf("Error: Number expected at line %d\n",linenum);        
        return INT_MIN;
    }

    while(isdigit(subuffer[i]))
        i++;

    SKIP_SPACE(subuffer,i)

    if(subuffer[i++] != ',')
    {
        printf("Error: ',' expected at line %d\n",linenum);
        return INT_MIN;
    }
    return i;
}
/*------------------------------------------------------------*/
/* Gets the first word(without any spaces)                    */
/* Returns true if it's a label definition and removes the ':'*/

bool islabel(char *word)
{
    if(word[strlen(word)-1] == ':')
    {
        word[strlen(word)-1] = '\0';
        return true;
    }
    return false;
}
/*------------------------------------------------------------*/
/* Validates a label, either as a label definition or operand.*/
/* As operand - used by is_valid_branchop.                    */
/* As label   - Gets a word without spaces and ':' at the end */

bool is_valid_label(char *line, int linenum)
{
    int i, j, k, len;               /* index */
    char label[MAX_LABEL_LENGTH];
    i = j = k = 0;
    
    SKIP_SPACE(line, i)
        
    j = i;
    while(!is_whitespace(line[j]) && !is_line_over(line[j])) 
        j++;           /* Make j point to the end of the label */
   
    len = j - i;
    
    if(!((len) > (MAX_LABEL_LENGTH)))
    {
        if(isalpha(line[i++]))
        {
            label[k++] = line[i-1];
            while(i < j)
            {
                label[k++] = line[i];
                if(!isalnum(line[i++]))
                {
                    printf("Error: Labels must be alphanumeric at line %d.\n",linenum);
                    return false;
                }
            }
            if(is_reserved_word(label))
            {
                printf("Error: Reserved words cannot be used as labels at line %d.\n",linenum);
                return false;
            } 
            SKIP_SPACE(line,i)
            if(!is_line_over(line[i]))
            {
                printf("Error: Extraneous label operand at line %d.\n",linenum);
                return false;
            }
            return true;
        }
        else printf("Error: First letter in a label must be alphabetic at line %d.\n", linenum);
    }
    else printf("Error: Labels' length must be less than %d at line %d.\n", MAX_LABEL_LENGTH-1, linenum);
    
    return false;
}
/*------------------------------------------------------------*/
/* Validates J type instructions.                             */
/* Gets a single operand and line number.                     */

bool is_valid_singleop(char *line, int linenum)  
{
    bool flag = false;
    int  i    = 0;
    SKIP_SPACE(line, i)
    
    if(line[i] != '$')
        flag = is_valid_label(line, linenum);
    else
        flag = regs_check(line, linenum, false, 1);
    
    return flag;
}

/*------------------------------------------------------------*/
/* Gets line of operands, retuns an array holding registers.  */
/*get 3 regs from a line  and return pointer to array of ints*/

void get_three_regs(char *line,int *arr)
{

    int reg1, reg2, reg3;
    if (3 == sscanf(line,
                    
        "%*[^0123456789]%d%*[^-+0123456789]%d%*[^0123456789]%d",
 
        &reg1,&reg2,&reg3))
    {
	    arr[0] = reg1;
        arr[1] = reg2;
        arr[2] = reg3;
    }   
}

/*------------------------------------------------------------*/
/*get 2 regs from a line  and return pointer to array of ints*/

void get_two_regs(char *line,int *arr)
{
    int reg1, reg2;
    if (2 == sscanf(line,

        "%*[^0123456789]%d%*[^-+0123456789]%d",
 
        &reg1,&reg2))
    {
	    arr[0] = reg1;
        arr[1] = reg2;
    }   
}
/*------------------------------------------------------------*/
/*get 1 regs from a line  and return pointer to array of ints*/

void get_one_regs(char *line,int *arr)
{
    int reg1;
    if (1 == sscanf(line,

        "%*[^0123456789]%d",
 
        &reg1))
 
    {
	    arr[0] = reg1;
    }   
}
/*------------------------------------------------------------*/
/*get the label in the end of the string TODO: FIX*/

void get_label_from_end(char *line,char *save)
{
    int i   = 0;
    int len = strlen(line);
    
    len--;
    while(is_whitespace(line[len]))
        len--; 
    
    while(isalnum(line[len])  && isalnum(line[len-1]) ) 
        len--;
	

    while(line[len] != '\0' && (isalnum(line[len])))
	{ 
        save[i] = line[len];
        i++;
        len++;
	}
    save[i] = '\0';
}
/*------------------------------------------------------------*/
bool is_in_reg_range(int reg)
{
    bool flag = true;
    if (reg < 0 || reg > 31) 
        flag = false;
    
    return flag;
}