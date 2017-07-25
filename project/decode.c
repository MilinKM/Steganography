#include <stdio.h>
#include "type.h"
#include <string.h>
//function body
status decode_function(Encode_info *ptr, char *stegno, char *magic_str, char *password)
{
	long temp, temp1 =0, temp2 = 0, idx, jdx = 0, kdx = 0;
	ptr -> steganography_file = fopen(stegno, "r");
	// move the file pointer to the end of header file
	fseek(ptr -> steganography_file, 54l,SEEK_SET);
	//decode magic string length and stored in temp1
	for (idx = 0; idx < 8; idx++)
	{
		temp = fgetc(ptr -> steganography_file);
		temp = ((temp & 1) << idx);
		temp1 = (temp1 & ~(1 << idx)) | temp;
	}
	// based on the length decode the magic string and check whether it is same as entered magic string or not
	for (idx = 0; idx < (temp1 * 8); idx++)
	{
		temp = fgetc(ptr -> steganography_file);
		temp = ((temp & 1) << jdx);
		temp2 = (temp2 & ~(1 << jdx)) | temp;
		jdx++;
		if (jdx == 8)
		{
			jdx = 0;
			if (temp2 != *(magic_str + kdx) || temp1 != strlen(magic_str))
			{
				printf("pattern string is not matching\n");
				return failure;
			}
			kdx++;
			temp2 = 0;
		}
	}
	temp1 = 0;

	// decode password
	for (idx = 0; idx < 8; idx++)
	{
		temp = fgetc(ptr -> steganography_file);
		temp = ((temp & 1) << idx);
		temp1 = (temp1 & ~(1 << idx)) | temp;
	}
	// based on the length decode the password and check whether it is same as entered password or not
	temp2 = 0, kdx = 0;
	for (idx = 0; idx < (temp1 * 8); idx++)
	{
		temp = fgetc(ptr -> steganography_file);
		temp = ((temp & 1) << jdx);
		temp2 = (temp2 & ~(1 << jdx)) | temp;
		jdx++;
		if (jdx == 8)
		{
			jdx = 0;
			if (temp2 != *(password + kdx) || temp1 != strlen(password))
			{
				printf("password is not matching\n");
				return failure;
			}
			kdx++;
			temp2 = 0;
		}
	}
	temp1 = 0;
	// decode format length and format
	for (idx = 0; idx < 8; idx++)
	{
		temp = fgetc(ptr -> steganography_file);
		temp = ((temp & 1) << idx);
		temp1 = (temp1 & ~(1 << idx)) | temp;
	}
	temp2 = 0, kdx = 0;
	char decoded_file[100] = {'m','y','_','f','i','l','e'};
	int pdx = 7;
	char *decoded_file_ptr;
	for (idx = 0; idx < (temp1 * 8); idx++)
	{
		temp = fgetc(ptr -> steganography_file);
		temp = ((temp & 1) << jdx);
		temp2 = (temp2 & ~(1 << jdx)) | temp;
		jdx++;
		if (jdx == 8)
		{
			decoded_file_ptr = (char *)&temp2;
			decoded_file[pdx] = *decoded_file_ptr;
			jdx = 0;
			pdx++;
			kdx++;
			temp2 = 0;
		}
	}
	decoded_file[pdx] = '\0';
	// based on the format create a new file
	ptr -> secrect_file = fopen(decoded_file,"w+");
	fseek(ptr -> secrect_file,0l,SEEK_SET);
	temp1 = 0;
	// decode secret file size and decode content and copy to new file
	for (idx = 0; idx < 32; idx++)
	{
		temp = fgetc(ptr -> steganography_file);
		temp = ((temp & 1) << idx);
		temp1 = (temp1 & ~(1 << idx)) | temp;
	}
	temp2 = 0, kdx = 0;
	for (idx = 0; idx < (temp1 * 8); idx++)
	{
		temp = fgetc(ptr -> steganography_file);
		temp = ((temp & 1) << jdx);
		temp2 = (temp2 & ~(1 << jdx)) | temp;
		jdx++;
		if (jdx == 8)
		{
			jdx = 0;
			fputc(temp2, ptr -> secrect_file);
			kdx++;
			temp2 = 0;
		}
	}
	fcloseall();
}
