/*------------------------------------------------------------*/
/* Authors: Maor Maayan & Daniel Popov                        */
/* File   : assembler.c                                       */
/*                                                            */
/* Description: Parsing functions and tools.                  */
/*------------------------------------------------------------*/
#ifndef PARSE_H
#define PARSE_H

#include <assert.h>
#include "globals.h"
#include "line_structure.h"
/*------------------------------------------------------------*/
/* Gets the next word in line.                                */ 
int   getword(char *line, char* word);
/*------------------------------------------------------------*/
/* Check line is no more than 80 character */
bool is_line_length_valid(char *line, int linenum);
/*------------------------------------------------------------*/
/* Memory allocation validated that it's not null.            */
void *validatedcalloc(size_t nitems, size_t size);
void *validatedmalloc(size_t size);
void *validatedrealloc(void * mem, size_t size);
/*------------------------------------------------------------*/
/* Checks if char is null(end of line \0)                     */
bool is_line_over(int c);
/*------------------------------------------------------------*/
/* Checks if char is tab or space                             */
bool is_whitespace(char c);
/*------------------------------------------------------------*/
/* Checks if line start with char c                           */
bool is_str_starts_with(char *line, char c);
/*------------------------------------------------------------*/
/* Checks if line is just tab and spaces                      */
bool is_empty_line(char *line,int size);
/*------------------------------------------------------------*/
/* Checks if line start with  ;                               */
bool is_comment(char *line);
/*------------------------------------------------------------*/
/* Checks if c is '+' or '-'                                  */
bool is_sign(char c);
/*------------------------------------------------------------*/
/* Checks if file name has .as in the end                     */
bool is_valid_file_name(char name[]);
/*------------------------------------------------------------*/
/* Copies the file name without the extension                 */
/* Returns allocated pointer to the new string.               */
char *cut(char *buffer);
/*------------------------------------------------------------*/
#endif