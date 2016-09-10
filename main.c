//merit-based allocation software for high-demand low-supply situations

#include <stdio.h>
#include <math.h>
#include <strings.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Usage:\n./meridian infile outfile\n");
	}
	FILE* f = fopen(argv[1], "r");
	if (f == NULL)
	{
		printf("Error opening file.\n");
		fclose(f);
		return -1;
	}
	char c;
	for (c = fgetc(f); c != EOF; c = fgetc(f))
	{
		printf("%c",c);
	}
	fclose(f);
	return 0;
}
