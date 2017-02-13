typedef struct applicant {
	char* name;
	unsigned long int id;
	char* prefs;
	unsigned int marks;
	unsigned long int supply;
} applicant;

typedef struct demand {
	unsigned long int id;
	char* name;
	unsigned int seats;
        unsigned int cutoff;
} demand;
/* Reads CSV files column by column and returns each entry in plate */
void getnextcol(FILE* file, char* plate);

/* Sorts the people.
   Supposed to also take into account
   what to do when 2/more applicants equally
   qualified */
void sort(applicant people[]);

/* Opens file, checks not null 
	and returns pointer */
FILE* openfile(char* name, char* mode);
