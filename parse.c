/*------------------------------------------------------------*/
/* Authors: Maor Maayan & Daniel Popov                        */
/* File   : parse.c                                           */
/*                                                            */
/* Description: Parsing functions and tools.                  */
/*------------------------------------------------------------*/
#include "parse.h"
/*------------------------------------------------------------*/
/* Returns the index that points after the first word found.  */
/* Saves the word.                                            */
int getword(char *line,char *word)
{
    int i,j;
    i = j = 0;

    SKIP_SPACE(line, i);
        
    while(!is_whitespace(line[i]) && !is_line_over(line[i]))
         word[j++] = line[i++];
   
    word[j] = 0;
    return i;
}
/*------------------------------------------------------------*/
bool is_line_length_valid(char *line, int linenum)
{
    if(strlen(line) > MAX_LINE_LENGTH - 1)
    {
        printf("Error: Line %d too long!\n", linenum);
        return false;
    }
    return true;
}
/*------------------------------------------------------------*/
void *validatedcalloc(size_t nitems, size_t size)
{
    void  *mem  = (void *)calloc(nitems, size);
    assert(mem != NULL);
    return mem;
}
/*------------------------------------------------------------*/
void *validatedmalloc(size_t size)
{
    void  *mem  = (void *)malloc(size);   
    assert(mem != NULL);
    return mem;
}
/*------------------------------------------------------------*/
void *validatedrealloc(void * mem, size_t size)
{
    mem = (void *)realloc(mem, size);
    assert(mem != NULL);
    return mem;
}
/*------------------------------------------------------------*/
/* Checks if the line or file is over */ 
bool is_line_over(int c)
{
    bool flag = false;
    if(c == '\n' || c == EOF || c == '\0') 
        flag = true;

    return flag;       
}
/*------------------------------------------------------------*/
bool is_whitespace(char c)
{
    bool flag = false;
    if(c == ' ' || c == '\t') 
        flag = true;
    
    return flag;   
}
/*------------------------------------------------------------*/
bool is_empty_line(char *line,int size)
{
    int i = 0;
    SKIP_SPACE(line,i);
    if(line[i] == '\0' && i == size)
        return true;

    return false;      
}
/*------------------------------------------------------------*/
bool is_comment(char *line)
{
    int i = 0;    
    SKIP_SPACE(line,i);
    
    if(line[i] == ';')
        return true;
    
    return false;
}
/*------------------------------------------------------------*/
/* Gets a character, returns true if it's a sign(+-)          */
bool is_sign(char c)
{
    if(c == '+' || c == '-')
        return true;

    return false;
}
/*------------------------------------------------------------*/
/* Checks if file name has .as in the end                     */

bool is_valid_file_name(char name[])
{
    int ch = 0;
    int file_name_len = 0;
    file_name_len = strlen(name);
    
    if(name[ch] == '.')
        return false;
    while(name[ch++] != '.' && ch != file_name_len)
        ;
    
    if(ch == file_name_len)
        return false;
    
    else if(name[ch] == 'a')
    {
        if(name[++ch] == 's')
        {
            if(name[++ch] == '\0')
                return true;
            else
                return false;
        }
    }
    return false;
}
/*------------------------------------------------------------*/
/* Copies the file name without the extension.                */
/* Returns allocated pointer to the new string.               */

char *cut(char *buffer)
{
    int i = 0;
    int j = 0;
    char *name = (char *)validatedcalloc(strlen(buffer),sizeof(char));

    while(isalpha(buffer[i]))
        name[j++] = buffer[i++];
  
 return name;
} 
