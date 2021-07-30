#ifndef OPTION_HEADER
#define OPTION_HEADER

void G() 
{ 
	FILE *file;
	file = getconfig();
	char *cgoalline, *inside;
	cgoalline = ffindline(file, "CGOAL");
	inside = getinsidequotes(cgoalline);
	fclose(file);
	printf("Current Goal: %s\n", inside);
}

void L() { printf("L.\n"); }
void S() { printf("S.\n"); }
void E() { printf("E.\n"); }

#endif 
