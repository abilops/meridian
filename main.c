//merit-based allocation software for high-demand low-supply situations

#include <stdio.h>
#include <math.h>
#include <ctype.h>
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
	// load all applicants into memory for sort
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

	// Sorted APPlicant FILE
	FILE* sappf = fopen(".tempsorted","w");
	for (int i = 0; i < appnum; i++)
	{
		applicant* pic = &people[i];
		fprintf(sappf, "%lu,%s,%u,%s\n", pic->id, pic->name, pic->marks, pic->prefs);
	}
	fclose(sappf);

	// ready to unload!
	for (int i = 0; i < appnum; i++)
	{
		free(people[i].name);
		free(people[i].prefs);
	}
	// load colleges into memory
	FILE* dems = fopen(argv[1], "r");
	// TODO I think I need a function for this
	if (dems == NULL)
	{
		printf("Error opening file.\n");
		fclose(dems);
		return -1;
	}
	// Find number of demands
	// TODO need a function for this too
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
		// TODO function for this
		demand* dic = &demands[i];
		getnextcol(dems, buffer);
		dic->id = atoi(buffer);
		getnextcol(dems,buffer);
		dic->name = malloc(strlen(buffer));
		strcpy(dic->name, buffer);
		getnextcol(dems,buffer);
		dic->seats = atoi(buffer);
                FILE* dicf = fopen(dic->name, "w");
                if (dicf == NULL)
                {
                        printf("Can't create/overwrite demands file\n");
                        return -1;
                }
                else
                {
                    fprintf(dicf, "%s%s\n", "List of students admitted into ", dic->name);
                    fclose(dicf);
                }
        }
	fclose(dems);
	printf("Loaded college data into memory\n");

	// start with people[0]
	appf = fopen(".tempsorted", "r");
	if (appf == NULL)
	{
		printf("Can't open file\n");
		return -1;
	}
	FILE* result = fopen(argv[3], "w");
	if (result == NULL)
	{
		printf("Can't open file\n");
		return -1;
	}
	for (int i = 0; i < appnum; i++)
	{
		// get data
		// TODO function for this
		applicant* pic = &people[i];
		getnextcol(appf,buffer);
		pic->id = atoi(buffer);
		getnextcol(appf,buffer);
		pic->name = malloc(strlen(buffer));
		strcpy(pic->name, buffer);
		getnextcol(appf, buffer);
		pic->marks = atoi(buffer);
		getnextcol(appf,buffer);
		pic->prefs = malloc(strlen(buffer));
		strcpy(pic->prefs, buffer);
                pic->supply = 4294967295;
		// extract preferences and assign college
		for (int k = 0, n = strlen(pic->prefs); k < n; k++)
		{
			// get number between the ';'s
			while (!isdigit(pic->prefs[k]))
			{ k++;}
			int bindex = 0;
			// what if number is longer than one digit?
			while (isdigit(pic->prefs[k]))
			{
				buffer[bindex] = pic->prefs[k];
				bindex++;
				k++;
			}
			buffer[bindex] = '\0';
			unsigned long curpref = atoi(buffer);
			// highest number, meaning no supply
			
			for (int l = 0; l < collnum; l++)
			{
				// This is the real check
				if (demands[l].id == curpref)
				{
                                    if (demands[l].seats > 0)
                                    {
					pic->supply = demands[l].id;
					demands[l].seats--;
                                        if (demands[l].seats == 0)
                                        {
                                            demands[l].cutoff = pic->marks;
                                        }
					// write to file before another segmentation fault
					fprintf(result, "%lu,%d,%s,%lu,%s\n", pic->id, pic->marks, pic->name, pic->supply, demands[l].name); 
                                        FILE* sic = fopen(demands[l].name, "a");
                                        if (sic == NULL)
                                        {
                                                printf("Can't open file\n");
                                                return -1;
                                        }
                                        fprintf(sic, "%lu,%s,%d\n",  pic->id, pic->name, pic->marks);
                                        fclose(sic);
					break;
                                    }
                                    else if (demands[l].seats == 0)
                                    {
                                        
                                        // Seats are zero, then what was the cutoff?
                                        if (demands[l].cutoff == pic->marks)
                                        {
                                            // Ethical conflict!! Same marks, but no more seats. What TODO?
                                            //TODO 
                                            printf("ALERT: Marks of applicant %s are same as cutoff of %s\n", pic->name, demands[l].name);
                                        }
                                        break;
                                    }
				}
				
			}
			// if supply is assigned, then no need to get next preference,
			// actually, it is better to get out of that loop.
			if (!(pic->supply == 4294967295))
			{
				break;
			}
		}
		// only malloc'd the strlen of buffer
		// so better to free and remalloc
		free(pic->name);
		free(pic->prefs);
	}
	fclose(appf);
	fclose(result);
        
	for (int i = 0; i < collnum; i++)
	{
		free(demands[i].name);
	}
	free(buffer);
	// Phew
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

/* void getnextline(FILE* file, char* plate)
{
	// TODO
} */
// Supposed to sort the people according to MARKS only
// but if you are importing a CSV, then why not use
// some spreadsheet program to sort it before the export?
void sort (applicant people[])
{
	// TODO
	printf("Sorting not yet implemented.\nAssuming that input is already sorted.");
	return;
}
