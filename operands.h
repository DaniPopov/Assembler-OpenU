/*------------------------------------------------------------*/
/* File   : operands.h                                        */
/* Authors: Maor Maayan & Daniel Popov                        */
/*                                                            */
/* Description: Functions for getting and validating operands.*/
/*------------------------------------------------------------*/
#ifndef OPERANDS_H
#define OPERANDS_H

#include <limits.h>
/*------------------------------------------------------------*/
/* Specially written macro for repeating code in is_valid_regs*/ 
#define AFTER_DIGIT(subuffer,i) \
    SKIP_SPACE(subuffer,i)\
\
	if (is_line_over(subuffer[i])) return regcounter+1;\
\
    else if(subuffer[i] == ',')\
    {\
        if(immed)\
        {\
            immed = false;\
            i += is_valid_immed(subuffer+i+1,linenum);\
            if(i < 0)\
                return INT_MIN;\
\
            regcounter = 1;\
        }\
        SKIP_SPACE(subuffer,i)\
\
        if(!is_line_over(subuffer[i]))\
           return (regcounter += 1 + is_valid_regs(subuffer+i+1,linenum,immed));\
\
        printf("Invalid operand: Lone ',' at line %d",linenum);\
    }\
    else\
        printf("Error: Comma expected at line %d.\n",linenum);

/*------------------------------------------------------------*/
/* Validates a label, either as a label definition or operand.*/
/* As operand - Used by is_valid_branchop.                    */
/* As label   - Gets a word without spaces and ':' at the end */

bool  is_valid_label(char *line, int linenum);
/*------------------------------------------------------------*/
/* Gets the first word (without any spaces).                  */
/* Returns true if it's a label definition and removes the ':'*/

bool  islabel(char *word);
/*------------------------------------------------------------*/
bool  is_in_reg_range(int reg);
/*------------------------------------------------------------*/
/* Gets line that includes register operands only             */
/* without label or command.                                  */
/* Immed is true if the second operand is an immediate value. */
/* Returns number of operands if valid else returns INT_MIN   */ 

int   is_valid_regs(char *subuffer, int linenum, bool immed);
/*------------------------------------------------------------*/
/* Gets a string of operands, Expects an integer              */
/* value and a comma.                                         */
/* Returns the length of subuffer if operand is valid.        */

int   is_valid_immed(char* subuffer, int linenum);
/*------------------------------------------------------------*/
/* Validates branch instruction's operands.                   */
/* Gets a line of operands and seperates them.                */
/* Returns true if both register and label operands are valid.*/

int   is_valid_branchop(char *line, int linenum);
/*------------------------------------------------------------*/
/* Validates J type instructions.                             */
/* Gets a single operand and line number.                     */

bool  is_valid_singleop(char *line, int linenum);
/*------------------------------------------------------------*/
/* Gets .asciz string operand and validates it.               */

bool is_valid_string(char *subuffer, int linenum);
/*------------------------------------------------------------*/
/* Checks if .dh .db .dw operands are valid.                  */
/* Gets a string of operands and line number.                 */
/* Returns amount of (if)valid operands, INT_MIN otherwise.   */

int   is_valid_nums(char *subuffer, int linenum);
/*------------------------------------------------------------*/
/* Gets is_valid_regs parameters and a counter of registers.  */
/* Returns true if regs are valid and counter = number of ops.*/

bool  regs_check(char *subuffer, int linenum, bool immed, int counter);
/*------------------------------------------------------------*/
/* Gets a string of integer operands and extracts them.       */
/* Returns a pointer to the allocated long array.             */
long *get_nums(char *token, long **arr);
/*------------------------------------------------------------*/
/* Gets line of operands, retuns an array holding registers.  */
void get_three_regs(char *line, int *arr);
void get_two_regs  (char *line, int *arr);
void get_one_regs  (char *line, int *arr);
/*------------------------------------------------------------*/
/* Gets a pointer to a string operand.                        */
/* Returns a pointer to an allocated string.                  */

char *get_string(char *subuffer);
/*------------------------------------------------------------*/
/* Gets a line and returns the label operand from the end.    */

void get_label_from_end(char *line,char *save);

#endif
