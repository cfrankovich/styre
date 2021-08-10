#ifndef OPTION_HEADER
#define OPTION_HEADER

// Set current goal //
void G(char* arg) 
{ 
	FILE *configfile, *tempconfigfile;
	configfile = getstyrefile("config", "r");
	tempconfigfile = getstyrefile("config.temp", "a");
	char *line;
	int iter, goallinenum;
	
	ffindline(configfile, "CGOAL", &goallinenum);
	iter = 1;
	while ((line = fgetline(configfile, iter)) != NULL)
	{
		if (iter == goallinenum)
		{
			fprintf(tempconfigfile, "CGOAL \"%s\"\n", arg);
		}
		else
		{
			fprintf(tempconfigfile, "%s\n", line);	
		}
		++iter;
	}

	fclose(configfile);
	char temppath[260], path[260];
	sprintf(path, "/home/%s/.styre/config", getusername());
	sprintf(temppath, "/home/%s/.styre/config.temp", getusername());
	if ((rename(temppath, path)) != 0)
	{
		printf("Error copying temp file.\n");
		fclose(tempconfigfile);
		exit(1);
	}
	fclose(tempconfigfile);
	printf("Changed current goal.\n");
}

// Create a list //
void L(char* arg)
{
	FILE *file;
	file = getstyrefile("lists", "a+");
	int i;	
	if (ffindline(file, arg, &i) != NULL)
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
	fprintf(listfile, "+%s\n\n", subsecname);
	fclose(listfile);

	printf("Created subsection \"%s\" in list \"%s\"\n", subsecname, listfilename);
}

// Create an entry in a list or subsection //
void E(char* arg)
{
	char *listfilename, *subsecname, *entryname, *uname, path[260];
	bool istheresubsec;
	FILE *listfile;
	
	entryname = styresplit(arg, 3); 
	subsecname = styresplit(arg, 2);
	listfilename = styresplit(arg, 1);
	istheresubsec = (entryname != NULL); 
	uname = getusername();
	sprintf(path, "/home/%s/.styre/Lists/%s", uname, listfilename);
	if (access(path, F_OK) == -1)
	{
		printf("List \"%s\" does not exist.\n", listfilename);
		exit(1);
	}
	
	if (istheresubsec)
	{
		char subsecthing[strlen(subsecname)+1];
		listfile = fopen(path, "r");
		sprintf(subsecthing, "+%s", subsecname);
		int linenum;
		if ((ffindline(listfile, subsecthing, &linenum)) == NULL)
		{
			printf("Subsection \"%s\" not found.\n", subsecname);
			fclose(listfile);
			exit(1);
		}

		// Need to find a better way than this //
		char temppath[260], *line;
		FILE *tempfile;
		int iter;
		sprintf(temppath, "%s.tmp", path);
		tempfile = fopen(temppath, "a");
		line = fgetline(listfile, 1);
		for (iter = 1; iter < strlen(line); ++iter)
		{
			fputc(line[iter], tempfile); 
		}
		fputc('\n', tempfile);
		iter = 2;
		while ((line = fgetline(listfile, iter)) != NULL)
		{
			if (iter == linenum+1)
			{
				--linenum;
				fprintf(tempfile, "-%s\n", entryname); 
			}
			else
			{
				++iter;
				fprintf(tempfile, "%s\n", line);
			}
		}
		fclose(tempfile);
		if ((rename(temppath, path)) != 0)
		{
			printf("Error copying temp file.\n");
			exit(1);
		}
		printf("Created entry \"%s\" under subsection \"%s\" in list \"%s\"\n", entryname, subsecname, listfilename);
	}
	else
	{
		listfile = fopen(path, "a");
		fprintf(listfile, "-%s\n", subsecname); 
		printf("Created entry \"%s\" in list \"%s\"\n", subsecname, listfilename);
	}

	fclose(listfile);
}

void g(char* arg) 
{ 
	FILE *file;
	char *quotes; 
	int i;
	file = getstyrefile("config", "r");
	quotes = getinsidequotes(ffindline(file, "CGOAL", &i));
	fclose(file);
	printf("Current Goal: %s\n", quotes);
}

#endif 
