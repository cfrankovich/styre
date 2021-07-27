#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "include.h"

int main(int argc, char **argv)
{
	int c;
	while ((c = getopt(argc, argv, "LSEG")) != -1) { parseargs(&c); }

	char *username;
	username = (char*)malloc(50 * sizeof(char));
	getlogin_r(username, sizeof(username));
	
	// path to the config and lists //
	char path[255];
	strcpy(path, "/home/");
	strcat(path, username);
	// strcat(path, "/.styre");

	printf("Path: %s\n", path);

	return 0;
}

