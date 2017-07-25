#include <stdio.h>
#include "type.h"

status error_check(Encode_info *ptr, status s)
{
	if (s == e_encode)
	{
		if (NULL == ptr->source_file )
		{
			perror("fopen");
			printf("Error: unable to open file %s\n", ptr -> source_file_name);
			return failure;
		}
		if (NULL == ptr -> secrect_file)
		{
			perror("fopen");
			printf("Error: unable to open file %s\n", ptr -> secrect_file_name);
			return failure;
		}
		else
			return success;
	}
	else if(s == e_decode)
	{
		if (NULL == ptr -> steganography_file)
		{
			perror("fopen");
			printf("Error: unable to open file %s\n", ptr -> steganography_file_name);
			return failure;
		}
		else
			return success;
	}
}

int main(int argc, char *argv[])
{
	Encode_info encode;
	char c_encode[10] = "-e";
	char c_decode[10] = "-d";
	// error checking
	if (argc < 5)
	{
	printf("ERROR: for enoding -> ./<executablefile> <password> <-e> <sourcefile> <secretfile> <steganographyfile>\n"
			" for decoding -> ./<executablefile> <magicstring> <-d> <password> <steganographyfile>\n");
	return failure;
	}
	if (!strcmp(argv[2], c_encode))
	{
		if (argc != 6)
		{
			printf("invalid arguments pass correct number of arguments\n");
			return failure;
		}
		encode.source_file_name = argv[3];
		encode.secrect_file_name = argv[4];
		encode.source_file = fopen(argv[3], "r");
		fseek(encode.source_file, 0l, SEEK_END);
		size_t source_size = ftell(encode.source_file);
		fseek(encode.source_file, 0l, SEEK_SET);
		encode.secrect_file = fopen(argv[4], "r");
		fseek(encode.secrect_file, 0l, SEEK_END);
		size_t secret_size = ftell(encode.secrect_file);
		fseek(encode.secrect_file, 0l, SEEK_SET);
		if (secret_size >= source_size)
		{
			printf("secret file size is larger than source file\n");
			return failure;
		}
		if (error_check(&encode, e_encode) == failure)
		{
			printf("Error: open files function failed\n");
			return 1;
		}
		else
			printf("success: open files function success\n");
		// encode_function call
		encode_function(&encode, argv[3], argv[5], argv[4], argv[1]);
	}
	else if (!strcmp(argv[2], c_decode))
	{
		if (argc != 5)
		{
			printf("invalid arguments pass correct number of arguments\n");
			return failure;
		}
		encode.steganography_file_name = argv[4];
		encode.steganography_file = fopen(argv[4], "r");
		if (error_check(&encode, e_decode) == failure)
		{
			printf("Error: open files function failed\n");
			return 1;
		}
		else
			printf("success: open files function success\n");
		// decode function call
		decode_function(&encode, argv[4], argv[1], argv[3]);	
	}
	fcloseall();
}
