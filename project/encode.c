#include <stdio.h>
#include "type.h"
#include <string.h>
#define Magic_string "xyz"
#define Magic_string_length 3
#define secrect_format ".mp4"
#define format_length 4
//function body
encode_function(Encode_info *ptr, char *source, char *stegno, char *secrect, char *password)
{
	char *magic_ptr = Magic_string;
	char *format_ptr = secrect_format;
	int idx, jdx = 0, kdx = 8;
	long temp;
	char buff[500];
	int password_size = strlen(password);
	ptr -> steganography_file = fopen(stegno, "w+");
	ptr -> source_file = fopen(source, "r");
	ptr -> secrect_file = fopen(secrect, "r");
	fseek(ptr -> secrect_file,0l,SEEK_END);

	//find the size of secret file for copying

	int secrect_file_size = ftell(ptr -> secrect_file);
	printf("size = %d\n", secrect_file_size);
	fseek(ptr -> secrect_file,0l,SEEK_SET);
	// read the header file from source to buffer
	fread(buff, 54, 1, ptr -> source_file);
	// write data from buffer to stegnography file
	fwrite(buff, 54, 1, ptr -> steganography_file);

	//hide the magic string length in source file and copy to stegno file
	for (idx = 7; idx >= 0; idx--)
	{
		temp = (((Magic_string_length << idx) >> 7) | (fgetc(ptr -> source_file) & ~(1)));
		fputc(temp, ptr -> steganography_file);
	}

	//hide magic string in source file and copy that data to stegno file
	for (idx = 0; idx < (Magic_string_length * 8); idx++)
	{
		kdx--;
		if (kdx == -1)
		{
			kdx = 7;
			jdx++;
		}
		temp = ((*(magic_ptr + jdx) << kdx) >> 7) |  (fgetc(ptr -> source_file) & ~(1));
		fputc(temp, ptr -> steganography_file);
	}

	//************hide password length and password in source file and copy to stegnofile**********************
	for (idx = 7; idx >= 0; idx--)
	{
		temp = (((password_size << idx) >> 7) | (fgetc(ptr -> source_file) & ~(1)));
		fputc(temp, ptr -> steganography_file);
	}
	kdx = 8, jdx = 0;
	for (idx = 0; idx < (password_size * 8); idx++)
	{
		kdx--;
		if (kdx == -1)
		{
			kdx = 7;
			jdx++;
		}
		temp = ((*(password + jdx) << kdx) >> 7) |  (fgetc(ptr -> source_file) & ~(1));
		fputc(temp, ptr -> steganography_file);
	}

	//************hide format length and format in source file and copy to stegnofile**********************

	for (idx = 7; idx >= 0; idx--)
	{
		temp = (((format_length << idx) >> 7) | (fgetc(ptr -> source_file) & ~(1)));
		fputc(temp, ptr -> steganography_file);
	}
	kdx = 8, jdx = 0;
	for (idx = 0; idx < (format_length * 8); idx++)
	{
		kdx--;
		if (kdx == -1)
		{
			kdx = 7;
			jdx++;
		}
		temp = ((*(format_ptr + jdx) << kdx) >> 7) |  (fgetc(ptr -> source_file) & ~(1));
		fputc(temp, ptr -> steganography_file);
	}

	//************hide secret file size  and file content in source file and copy to stegnofile**********************

	for (idx = 31; idx >= 0; idx--)
	{
		temp = (((secrect_file_size << idx) >> 31) | (fgetc(ptr -> source_file) & ~(1)));
		fputc(temp, ptr -> steganography_file);
	}
	kdx = 8, jdx = 0;
	int temp3;
	temp3 = fgetc(ptr -> secrect_file);
	for (idx = 0; idx < (secrect_file_size * 8); idx++)
	{
		kdx--;
		if (kdx == -1)
		{
			temp3 = fgetc(ptr -> secrect_file);
			kdx = 7;
			jdx++;
		}
		temp = (((temp3 << kdx) >> 7) |  (fgetc(ptr -> source_file) & ~(1)));
		fputc(temp, ptr -> steganography_file);
	}
	// copy remaining data
	while ((temp = fgetc(ptr -> source_file)) != EOF)
	{
		fputc(temp, ptr -> steganography_file);
	}
	fcloseall();
}

