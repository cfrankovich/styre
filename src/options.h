#ifndef OPTION_HEADER
#define OPTION_HEADER

void G() 
{ 
	FILE *file;
	char *quotes; 
	int i;
	file = getconfig();
	quotes = getinsidequotes(ffindline(file, "CGOAL"));
	fclose(file);

	char inside[strlen(quotes)-1];
	for (i = 0; i < strlen(quotes)-2; ++i)
	{
		inside[i] = quotes[i+1];
	}
	inside[strlen(quotes)-2] = '\0';

	printf("Current Goal: %s\n", inside);
}

void L() { printf("L.\n"); }
void S() { printf("S.\n"); }
void E() { printf("E.\n"); }

#endif 
