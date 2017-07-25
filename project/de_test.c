#include <stdio.h>

main(int argc, char *argv[])
{
	FILE *fp, *fp1;
	int temp;
	int temp1 = 0;
	int idx;
	fp = fopen(argv[1],"r");
	fp1 = fopen("temp.txt","w+");
	fseek(fp,54l,SEEK_SET);
	for (idx = 0; idx < 8; idx++)
	{
		temp = fgetc(fp);
		temp = ((temp & 1) << idx);
		temp1 = (temp1 & ~(1 << idx)) | temp;
	}
  printf("%x\n", temp1);	
  fseek(fp1,0l,SEEK_SET);
  fputc(temp1+48,fp1);





}
