//merit-based allocation software for high-demand low-supply situations

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"

#define INT_SIZE 2
void getnextcol(FILE* file, char* plate);
void sort(applicant people[]);

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
		strcpy(pic->prefs, buffer);
	}
	//free(buffer);
	fclose(appf);
	printf("Loaded student data into memory\n");
	sort(people);

	FILE* sappf = fopen("sorted_students.dat","w");
	for (int i = 0; i < appnum; i++)
	{
		applicant* pic = &people[i];
		fprintf(sappf, "%lu,%s,%u,%s\n", pic->id, pic->name, pic->marks, pic->prefs);
	}
	fclose(sappf);

	// load colleges into memory
	FILE* dems = fopen(argv[1], "r");
	if (dems == NULL)
	{
		printf("Error opening file.\n");
		fclose(dems);
		return -1;
	}
	// Find number of applicants
	unsigned int collnum = 0;
	for (char c = fgetc(dems); c != EOF; c = fgetc(dems))
	{
		if (c == '\n')
		{
			collnum++;
		}
	}

	// Array of demand options
	demand demands[collnum];

	buffer[0] = '\0';
	// Set pointer back to beginning
	fseek(dems, 0, SEEK_SET);
	for (int i = 0; i < collnum; i++)
	{
		// Init demand in context for easy typing
		demand* dic = &demands[i];
		getnextcol(dems, buffer);
		dic->id = atoi(buffer);
		getnextcol(dems,buffer);
		dic->name = malloc(strlen(buffer));
		strcpy(dic->name, buffer);
		getnextcol(dems,buffer);
		dic->seats = atoi(buffer);
	}
	free(buffer);
	fclose(dems);
	printf("Loaded college data into memory\n");

	// start with people[0]
	FILE* appf = fopen(argv[2], "r");
	if (appf == NULL)
	{
		printf("Can't open file\n");
		return;
	}
	for (i = 0; i < appnum; i++)
	{
		// TODO	
	}

	// WRITE OUT: student-college.dat

	// WRITE OUT: college[x]-students.dat

	// ready to unload!
	for (int i = 0; i < appnum; i++)
	{
		applicant* pic = &people[i];
		printf("%lu|%s\n%d|%s\n", pic->id, pic->name, pic->marks, pic->prefs);
		free(people[i].name);
		free(people[i].prefs);
	}
	for (int i = 0; i < collnum; i++)
	{
		demand* dic = &demands[i];
		printf("%lu|%s|%u\n", dic->id, dic->name, dic->seats);
		free(demands[i].name);
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

void getnextline(FILE* file, char* plate)
{
	// TODO
}

void sort (applicant people[])
{
	printf("Sorting not yet implemented.\nAssuming that input is already sorted.");
	return;
}
