#include <stdio.h>
#include <string.h>

main(int argc, char *argv[])
{
	FILE *fp, *fp1;
	long temp;
	char buffer[500];
	int len = strlen(argv[1]), idx;
	char *ch =(char *) &len;
	printf("%d\n", *ch);
	fp = fopen(argv[2], "r");
	fseek(fp,0L, SEEK_END);
	size_t sz = ftell(fp);
	printf("%lu\n",sz);
	fseek(fp,0L, SEEK_SET);
	fp1 = fopen(argv[3], "w+");
	fread(buffer,54,1,fp);
	fwrite(buffer,54,1,fp1);
	for (idx = 7; idx >= 0; idx--)
	{
	temp = (((*ch << idx) >> 7) |  (fgetc(fp) & ~(1)));
	fputc(temp, fp1);
	}
	while ((temp = fgetc(fp)) != EOF)
	{
		fputc(temp, fp1);
	} 
	fclose(fp1);
	fclose(fp);
}
