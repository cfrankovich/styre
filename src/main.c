#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "declare.h"

#define MAX_ARG_LEN 100
#define OPT_LIST "e:s:lgX:D:L:S:E:G:R:?"

int main(int argc, char **argv)
{
	if (argc == 1) 
	{ 
		FILE *file;
		file = getstyrefile("config", "r");
		int temp;
		char* inside = getinsidequotes(ffindline(file, "DEFCOM", &temp));
		fclose(file);

		char *copy, *ptr;
		copy = malloc(strlen(inside) * sizeof(char));
		strcpy(copy, inside);
		ptr = strtok(copy, " "); 

		while (ptr != NULL)
		{
			if (ptr[0] == '-')
			{
				int c;
				c = ptr[1]; ptr = strtok(NULL, " "); 
				parseargs(&c, ptr, argv); 
			}
			else
			{
				ptr = strtok(NULL, " ");
			}
		}

		return 0;
	}

	int c;
	while ((c = getopt(argc, argv, OPT_LIST)) != -1)
	{ 
		parseargs(&c, optarg, argv);
	}
	
	return 0;
}

