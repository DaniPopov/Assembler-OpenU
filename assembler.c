/*------------------------------------------------------------*/
/* Authors: Maor Maayan & Daniel Popov                        */
/* File   : assembler.c                                       */
/*                                                            */
/* Description: Main function that uses all previous code     */
/* to manufacture and print required files.                   */
/*------------------------------------------------------------*/
#include "assembler.h"
/*------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    /*Initialization :       */
    char *filename;
    FILE *outputfile, *inputfile;
    
    line     *head_line;
    code_img *head_code;
    label    *head_label;
    extra    *head_extra;
    
    bool fp_valid, sp_valid;
    
    int index_file = 1;
    data_img       = NULL;
  
    while(index_file < argc)
    {     
        head_code  = NULL;
        head_line  = NULL;
        head_label = NULL;
        head_extra = NULL;   
        /* Checks file name is valid */
        if(is_valid_file_name(argv[index_file]))
            filename = cut(argv[index_file]);
          
        else
        {
            printf("Error: Invalid file name: %s\n", argv[index_file++]);
            continue;
        }
        /*Open file */
        inputfile = fopen(argv[index_file], "r");
        
        if(!inputfile)
        {
            printf("Error: %s source file cannot be opened!\n", argv[index_file++]);
            continue;
        }
        outputfile = fopen(strcat(filename, ".ob"), "w");
        free(filename);
	    filename   = cut(argv[index_file]);
        assert(inputfile  != NULL);
        assert(outputfile != NULL);
        
        if( (fp_valid = first_pass(&head_code, &head_line, &head_label, inputfile)) )
        {
            update_label_table(&head_label);
            if( (sp_valid = second_pass(&head_code, &head_line, &head_label, &head_extra)) )
            {
                /* Print Object File: */ 
                fprintf(outputfile,"     %ld %ld", IC-INITIAL_IC_VALUE, DC);
                print_code_img(head_code, outputfile); 
                print_data_img(outputfile);

                /* Print Extra Files: */
                print_extra(&head_extra, filename);
            }
        } 
        /* Removes empty object file if there's an error. */
        if(!(fp_valid && sp_valid))
        {
            printf("Errors found in file %s.as!\n", filename);
            printf("/*------------------------END OF FILE------------------------*/\n");
            remove(strcat(filename, ".ob"));
        }
        
        /* Reset: */ 
        IC = INITIAL_IC_VALUE;
        DC = 0;
        index_file++;
        
        if(filename)
            free(filename);
        filename = NULL;
        
        free_line_list(&head_line);
        free_symbol_list(&head_label);  
        free_extra_list(&head_extra); 
        free_code_list(&head_code);
	    fclose(inputfile);
	    fclose(outputfile);
    }   /* end of loop */
    if(data_img)
        free(data_img);
    return 0;
}



   


