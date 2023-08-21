#include "data_img.h"
/* Declaration of data_img */
unsigned char *data_img;
/*------------------------------------------------------------*/


void print_data_img(FILE *dest)
{
	int i = 0;
    if (DC > 0)  fprintf(dest, "\n0%ld ", IC);      /* First address */

    while (i < DC)
    {
	    if (data_img[i] < 0xf) fprintf(dest, "0");  /* Leading zero  */
    	fprintf(dest, "%X ",data_img[i++]);

    	if (!(i % 4) && i != DC)                    /* Print address */
    	{
    		fprintf(dest, "\n");
    		if (i + IC < 1000) fprintf(dest, "0");  /* Leading zero  */
    		fprintf(dest, "%ld ", i + IC);
		}
    }
}
/*------------------------------------------------------------*/


void encode_num_operands(long *nums, char *cmd, int len)
{
    int i, j, bytecounter;
    
    i = j = bytecounter = 0;
    bytecounter = get_cmd_syntax(cmd);
    data_img    = (unsigned char *)validatedrealloc(data_img, (DC + bytecounter*len) );

    while (i < len)
    {
        while (j < bytecounter)
        {
            data_img[DC++] = (nums[i] & 0xff);
            nums[i] >>= 8;
            j++;
        }
        j = 0;
        i++;
    }
}
/*------------------------------------------------------------*/


void encode_string(char *str)
{
    int i    = 0;
    int len  = strlen(str);
    DC       += len + 1;
    data_img = (unsigned char *)validatedrealloc(data_img, DC);

    while(i < len)
    {
        data_img[DC - len-1 + i] = str[i];
        i++;
    }
}
/*------------------------------------------------------------*/
