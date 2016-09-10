//merit-based allocation software for high-demand low-supply situations

#include <stdio.h>
#include <math.h>
#include <strings.h>
#include <stdlib.h>
#include "structs.h"

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
	printf("Enter name for applicant1: ");
	applicant a1;
	a1.name = malloc(20);
	scanf("%s", a1.name);
	printf("Enter id for a1: ");
	scanf("%lu", &a1.id);
	printf("%s's id is %lu.\n", a1.name, a1.id);
	free(a1.name);
	return 0;
}
