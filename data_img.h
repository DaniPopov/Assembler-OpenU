#ifndef DATA_IMG_H
#define DATA_IMG_H

#include "globals.h"
#include "parse.h"

/*------------------------------------------------------------*/
/* Declaration of data_img */
extern unsigned char *data_img;
/*------------------------------------------------------------*/
/* Gets a pointer to the output file and prints the data      */
/* image into the file.                                       */
void print_data_img(FILE *outputfile);
/*------------------------------------------------------------*/
/* Gets an operands array, command string and length of said  */
/* array, encodes the array into the data image.              */

void encode_num_operands(long *nums, char *cmd, int len);
/*------------------------------------------------------------*/
/* Gets a valid string and encodes it into the data image.    */
void encode_string(char *str);
/*------------------------------------------------------------*/

#endif