#include <stdio.h>
#include <stdlib.h>

#include "meridian.h"

// Supposed to sort the people according to MARKS only
// but if you are importing a CSV, then why not use
// some spreadsheet program to sort it before the export?
void sort (applicant people[])
{
    // TODO
	printf("Sorting not yet implemented.\nAssuming that input is already sorted.");
	return;
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

