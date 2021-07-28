#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "options.h"
#include "extra.h"

char* getconfigpath();

int main(int argc, char **argv)
{
	if (argc == 1) 
	{ 
		FILE *fp;
		char *path;
		path = getconfigpath();
		if ((fp = fopen((char*)path, "r")) == NULL)
		{
			printf("Config file not found! Exiting.\n");
			exit(1);
		}
	
		char *firstline;
		firstline = fgetline(fp, 2);

		printf("Line: %s\n", firstline);
		
		fclose(fp);
		return 0;
	}

	int c;
	while ((c = getopt(argc, argv, "LSEG")) != -1)
	{ 
		parseargs(&c);
	}
	
	return 0;
}

char* getconfigpath()
{
	char *username;
	username = (char*)malloc(50 * sizeof(char));
	getlogin_r(username, sizeof(username));

	// this doesnt feel right //	
	static char path[255];
	strcpy(path, "/home/");
	strcat(path, username);
	strcat(path, "/.styre/styrerc");
	return path;
}

