/*------------------------------------------------------------*/
/* Authors: Daniel Popov & Maor Maayan                        */
/* File   :                                                   */
/*                                                            */
/* Description: Validates lines and encodes data and code     */
/* into appropriate structures.                               */
/*------------------------------------------------------------*/
#ifndef FIRST_PASS_H
#define FIRST_PASS_H
/*Includes: */ 
#include "globals.h"
#include "parse.h"
#include "operands.h"
#include "code_img.h"
#include "data_img.h"
#include "line_structure.h"
#include "label_structure.h"
#include "extra_structure.h"
/*------------------------------------------------------------*/
/* Define: */
#define CONTINUE \
{ \
    line_num++; \
    is_valid = false;\
    continue; \
}
/*------------------------------------------------------------*/
/* Gets the head of the table and updates all address value.  */
/* If the label has data attribute, adds ICF.                 */
void update_label_table(label **root);
/*------------------------------------------------------------*/
/* Gets a line and command from the line and checks if the syntex of the line is valid */
/* Return enum command_syntax that match the command */

int  validate_line(char *buffer, char *cmd, int line_num);
/*------------------------------------------------------------*/
/* Description: Validates lines and encodes data and code     */
/* into appropriate structures.                               */
bool first_pass(code_img **head_code, line **head_line, label **head_label, FILE *inputfile);
/*------------------------------------------------------------*/
/*Fills the array type int with 0 */
void clear(int *arr, int size);

    
    
    
    
#endif    
