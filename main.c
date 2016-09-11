//merit-based allocation software for high-demand low-supply situations

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

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

	char buffer[81];
	int bindex = 0;
	int column = 0;
	int pindex = 0;
	for (char c = fgetc(appf); c != EOF; c = fgetc(appf))
	{
		if (c == ',' || c == '\n')
		{
			buffer[bindex] = '\0';
			switch (column)
			{
				case (0):
					//this must be the marks
					people[pindex].marks = atoi(buffer);
					break;
				case (1):
					// this must be the id
					people[pindex].id = atoi(buffer);
					break;
				case (2):
					// this is the name
					people[pindex].name = malloc(strlen(buffer) + 1);
					strcat(people[pindex].name, &buffer[0]);
					break;
				case (3):
					// this must be the preferences
					people[pindex].prefs = malloc(strlen(buffer) + 1);
					strcat(people[pindex].prefs, &buffer[0]);
					break;
			}
			column++;
			bindex = 0;
			// if newline then 
			if (c == '\n')
			{
				pindex++;
				column = 0;
			}
		}
		else
		{
			buffer[bindex] = c;
			bindex++;
		}
	}
	for (int i = 0; i < appnum; i++)
	{
		printf("%lu|%s\n%d|%s\n", people[i].id, people[i].name, people[i].marks, people[i].prefs);
		free(people[i].name);
		free(people[i].prefs);
	}
	return 0;
}
