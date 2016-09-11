typedef struct applicant {
	char* name;
	unsigned long int id;
	char* prefs;
	unsigned int marks;
} applicant;

typedef struct demand {
	unsigned long int id;
	char* name;
	unsigned int seats;
} demand;
