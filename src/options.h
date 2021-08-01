#ifndef OPTION_HEADER
#define OPTION_HEADER

// List current goal //
void G() 
{ 
	FILE *file;
	char *quotes; 
	int i;
	file = getstyrefile("styrerc", "r");
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

// Create a list //
void L()
{
	// Find if optarg is anywhere in ~/.styre/lists //
	FILE *file;
	file = getstyrefile("lists", "r");
	if (strcmp("!NOTFOUND!", ffindline(file, optarg)) != 0)
	{
		printf("List already exists!\n");
		fclose(file);
		exit(1);
	}
	fclose(file);
	
	// We have confirmed it doesn't so now create entry //
	char path[260];
	char *uname;
	uname = getusername();	
	sprintf(path, "/home/%s/.styre/Lists/%s.syr", uname, optarg);
	FILE *newlistfile;
	newlistfile = fopen(path, "w+");
	fclose(newlistfile);

	printf("Created list \"%s\"\n", optarg);
}

// Create subsection in list //
void S() { printf("S.\n"); }

// Create an entry in a list or subsection //
void E() { printf("E.\n"); }

#endif 
