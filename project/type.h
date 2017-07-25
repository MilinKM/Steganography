#ifndef TYPE_H
#define TYPE_H
#define _GNU_SOURCE
#define ENCODE_H
#include<stdio.h>
typedef unsigned int uint;
typedef struct
{
	FILE *source_file, *secrect_file, *steganography_file;
	char *source_file_name, *secrect_file_name, *steganography_file_name;
	uint source_file_size, secrect_file_size;
}Encode_info;
typedef enum
{
	e_encode = 1,
	e_decode,
}operation_type;
typedef enum
{
	failure,
	success,
}status;
#endif
