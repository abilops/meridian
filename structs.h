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
