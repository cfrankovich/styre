#ifndef OPTION_HEADER
#define OPTION_HEADER

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "declare.h"

// Remove Something //
void X(char *arg)
{
	char *list, *sub, *entry, *line, path[260];
	list = styresplit(arg, 1);
	sub = styresplit(arg, 2);
	entry = styresplit(arg, 3);
	
	// 1 - list | 2 - sub | 3 - entry //
	int cse;
	cse = (sub != NULL) ? ((entry != NULL) ? 3 : 2) : 1;

	FILE *listfile;
	sprintf(path, "/home/%s/.styre/Lists/%s", getusername(), list);
	if ((listfile = fopen(path, "r")) == NULL)
	{
		printf("List \"%s\" does not exist\n", list);
		exit(1);
	}
	fclose(listfile);

	FILE *fp, *tfp;
	int iter;
	char lookinfor[260];

	if (cse == 1)
	{
		if (remove(path) != 0)
		{
			printf("Error deleting list \"%s\"\n", list);
			fclose(listfile);
			exit(1);
		}

		sprintf(path, "/home/%s/.styre/lists.tmp", getusername());
		tfp = fopen(path, "a");
		sprintf(path, "/home/%s/.styre/lists", getusername());
		fp = fopen(path, "r");
		strcpy(lookinfor, list);
	}
	else if (cse == 2 || cse == 3)
	{
		sprintf(path, "/home/%s/.styre/Lists/%s.tmp", getusername(), list);
		tfp = fopen(path, "a");
		sprintf(path, "/home/%s/.styre/Lists/%s", getusername(), list);
		fp = fopen(path, "r");
		if (cse == 2) sprintf(lookinfor, "+%s", sub);
		else sprintf(lookinfor, "-%s", entry);
	}

	// First line always buggin //
	bool found;
	found = false;
	
	line = fgetline(fp, 1);
	if (strcmp(line+1, lookinfor) == 0) found = true;
	else fprintf(tfp, "%s\n", line+1);

	iter = 2;
	while ((line = fgetline(fp, iter)) != NULL)
	{
		if (!found && strcmp(line, lookinfor) == 0) found = true; 
		else fprintf(tfp, "%s\n", line);
		++iter;
	}
	fclose(tfp);
	fclose(fp);

	char temppath[264];
	sprintf(temppath, "%s.tmp", path);

	if ((rename(temppath, path)) != 0)
	{
		printf("Error copying temp file\n");
		exit(1);
	}

	if (!found) printf("No deletions have occured\n");

}

// Set default command //
void D(char *arg)
{
	FILE *configfile, *tempconfigfile;
	configfile = getstyrefile("config", "r");
	tempconfigfile = getstyrefile("config.temp", "a");
	char *line;
	int iter, goallinenum;
	
	ffindline(configfile, "DEFCOM", &goallinenum);
	iter = 1;
	while ((line = fgetline(configfile, iter)) != NULL)
	{
		if (iter == goallinenum)
		{
			fprintf(tempconfigfile, "DEFCOM \"%s\"\n", arg);
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
	printf("Changed default command.\n");
}

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
		char temppath[264], *line;
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

// List current goal //
void g(char* arg) 
{ 
	FILE *file;
	char *quotes; 
	int i;
	file = getstyrefile("config", "r");
	quotes = getinsidequotes(ffindline(file, "CGOAL", &i));
	fclose(file);
	if (quotes == NULL)
		printf("Could not find \"CGOAL\" in config.\n");
	else
		printf("%s\n", quotes);
}

// List out all lists //
void l()
{
	FILE *listfile;
	listfile = getstyrefile("lists", "r");
	int iter;
	iter = 1;
	char *line;
	
	while ((line = fgetline(listfile, iter)) != NULL)
	{
		printf("%s\n", line);		
		++iter;
	}
	fclose(listfile);
}

// List subsecs of a list //
void s(char *arg)
{
	FILE *listfile;
	char path[260], *line;
	int iter;

	sprintf(path, "/home/%s/.styre/Lists/%s", getusername(), arg);
	if((listfile = fopen(path, "r")) == NULL)
	{
		printf("List \"%s\" does not exist.\n", arg);
		exit(1);
	}

	iter = 1;	
	printf("_%s\n", arg);
	while ((line = fgetline(listfile, iter)) != NULL)
	{
		if (line[0] == '+')
		{
			printf("%s\n", line);
		}
		++iter;
	}
	fclose(listfile);
}

// List subsecs of a list //
void e(char* arg)
{
	char *line, *subname, path[260];
	subname = styresplit(arg, 2);
	sprintf(path, "/home/%s/.styre/Lists/%s", getusername(), styresplit(arg, 1));

	FILE *listfile;
	if((listfile = fopen(path, "r")) == NULL)
	{
		printf("List \"%s\" does not exist.\n", styresplit(arg, 1));
		exit(1);
	}

	bool issub;
	issub = subname != NULL;
	if (issub)
	{
		e2(listfile, subname);  
		return;
	}
	
	int iter;
	iter = 2;	
	printf("\n");
	bool inside;
	while ((line = fgetline(listfile, iter)) != NULL)
	{
		if (line[0] != '\0')
		{
			if (inside)
				printf("  %s\n", line);
			else
				printf("%s\n", line);
		}
		else
		{
			inside = false;
		}

		if (line[0] == '+') 
			inside = true;
		++iter;
	}
	printf("\n");
	fclose(listfile);
}

void e2(FILE *fp, char *subname)
{
	int iter;
	iter = 2;
	printf("\n");
	bool inside;
	inside = false;
	char subwplus[strlen(subname)+1], *line;
	sprintf(subwplus, "+%s", subname);
	while ((line = fgetline(fp, iter)) != NULL)
	{
		if (strcmp(subwplus, line) == 0)
		{
			inside = true; 
			++iter;
			printf("%s\n", line);
			continue;
		}
		
		if (inside) 
		{
			printf("  %s\n", line);
			inside = line[0] != '\0';
		}

		++iter;
	}
	fclose(fp);
}

#endif 
