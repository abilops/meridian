//merit-based allocation software for high-demand low-supply situations

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

void getnextcol(FILE* file, char* plate);

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		printf("Usage:\n./meridian demands applicants results\n");
		return -1;
	}
	FILE* appf = fopen(argv[2], "r");
	if (appf == NULL)
	{
		printf("Error opening file.\n");
		fclose(appf);
		return -1;
	}
	// Find number of applicants
	unsigned int appnum = 0;
	for (char c = fgetc(appf); c != EOF; c = fgetc(appf))
	{
		if (c == '\n')
		{
			appnum++;
		}
	}

	// Array of applicants
	applicant people[appnum];

	// Set pointer back to beginning
	fseek(appf, 0, SEEK_SET);
	char* buffer = malloc(81);
	for (int i = 0; i < appnum; i++)
	{
		// Init person in context for easy typing
		applicant* pic = &people[i];
		getnextcol(appf, buffer);
		pic->marks = atoi(buffer);
		getnextcol(appf,buffer);
		pic->id = atoi(buffer);
		getnextcol(appf,buffer);
		pic->name = malloc(strlen(buffer));
		strcat(pic->name, buffer);
		getnextcol(appf,buffer);
		pic->prefs = malloc(strlen(buffer));
		strcat(pic->prefs, buffer);
	}
	free(buffer);
	fclose(appf);
	
	for (int i = 0; i < appnum; i++)
	{
		applicant* pic = &people[i];
		printf("%lu|%s\n%d|%s\n", pic->id, pic->name, pic->marks, pic->prefs);
		free(people[i].name);
		free(people[i].prefs);
	}
	return 0;
}

// Serves the value of the next column in the CSV file in the
// provided plate
void getnextcol(FILE* file, char* plate)
{
	int pindex = 0;
	char c = fgetc(file);
	while (c != ',' && c != '\n' && c != EOF)
	{
		plate[pindex] = c;
		pindex++;
		c = fgetc(file);
	}
	plate[pindex] = '\0';
}
