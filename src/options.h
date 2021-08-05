#ifndef OPTION_HEADER
#define OPTION_HEADER

/*
underscore - list name
plus - subsection (can do multiple)
minus - task 
*/

// List current goal //
// Should be set //
void G(char* arg) 
{ 
	FILE *file;
	char *quotes; 
	int i;
	file = getstyrefile("config", "r");
	quotes = getinsidequotes(ffindline(file, "CGOAL"));
	fclose(file);
	printf("Current Goal: %s\n", quotes);
}

// Create a list //
void L(char* arg)
{
	FILE *file;
	file = getstyrefile("lists", "a+");
	if (strcmp("!NOTFOUND!", ffindline(file, arg)) != 0)
	{
		printf("List already exists!\n");
		fclose(file);
		exit(1);
	}
	fprintf(file, "%s\n", arg);
	fclose(file);
	
	char path[260];
	char *uname;
	FILE *newlistfile;
	uname = getusername();	
	sprintf(path, "/home/%s/.styre/Lists/%s", uname, arg);
	newlistfile = fopen(path, "a");
	fprintf(newlistfile, "_%s\n", arg);
	fclose(newlistfile);

	printf("Created list \"%s\"\n", arg);
}

// Create subsection in list //
void S(char* arg)
{
	char *listfilename, *subsecname;
	// styre -S <list name>:<sub sec name>
	listfilename = styresplit(arg, 1);
	subsecname = styresplit(arg, 2);
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
void E(char* arg) { printf("E.\n"); }

#endif 
