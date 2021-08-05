#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "declare.h"
#include "addon.h"
#include "options.h"

#define MAX_ARG_LEN 100

int main(int argc, char **argv)
{
	if (argc == 1) 
	{ 
		FILE *file;
		file = getstyrefile("config", "r");
		int temp;
		char* theline = ffindline(file, "DEFCOM", &temp);
		char* inside = getinsidequotes(theline);

		char *copy, *ptr;

		copy = (char*)malloc(strlen(inside) * sizeof(char));
		strcpy(copy, inside);
		ptr = strtok(copy, " "); 

		while (ptr != NULL)
		{
			if (ptr[0] == '-')
			{
				int c;
				c = ptr[1];
				ptr = strtok(NULL, " "); 
				parseargs(&c, ptr); 
			}
			else
			{
				ptr = strtok(NULL, " ");
			}
		}

		fclose(file);
		return 0;
	}

	int c;
	while ((c = getopt(argc, argv, "L:S:E:G?")) != -1)
	{ 
		parseargs(&c, optarg);
	}
	
	return 0;
}

