#ifndef OPTION_HEADER
#define OPTION_HEADER

/*
underscore - list name
plus - subsection (can do multiple)
minus - task 
*/

// List current goal //
void G() 
{ 
	FILE *file;
	char *quotes; 
	int i;
	file = getstyrefile("config", "r");
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
	FILE *file;
	file = getstyrefile("lists", "a+");
	if (strcmp("!NOTFOUND!", ffindline(file, optarg)) != 0)
	{
		printf("List already exists!\n");
		fclose(file);
		exit(1);
	}
	fprintf(file, "%s\n", optarg);
	fclose(file);
	
	char path[260];
	char *uname;
	FILE *newlistfile;
	uname = getusername();	
	sprintf(path, "/home/%s/.styre/Lists/%s", uname, optarg);
	newlistfile = fopen(path, "a");
	fprintf(newlistfile, "_%s\n", optarg);
	fclose(newlistfile);

	printf("Created list \"%s\"\n", optarg);
}

// Create subsection in list //
void S()
{
	char *listfilename, *subsecname;
	// styre -S <list name>:<sub sec name>
	listfilename = styresplit(optarg, 1);
	subsecname = styresplit(optarg, 2);
	if (subsecname == NULL)
	{
		printf("Please provide all arguments.\n");
		exit(1);
	}

	char path[260];
	char *uname;
	FILE *listfile;

	uname = getusername();
	sprintf(path, "/home/%s/.styre/Lists/%s", uname, listfilename);
	if (access(path, F_OK) == -1)
	{
		printf("List \"%s\" does not exist.\n", listfilename);
		exit(1);
	}
	listfile = fopen(path, "a");
	fprintf(listfile, "+%s\n", subsecname);
	fclose(listfile);

	printf("Created subsection \"%s\" in list \"%s\"\n", subsecname, listfilename);
}

// Create an entry in a list or subsection //
void E() { printf("E.\n"); }

#endif 
