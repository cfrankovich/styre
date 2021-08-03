#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "extra.h"
#include "options.h"

int main(int argc, char **argv)
{
	if (argc == 1) 
	{ 
		FILE *file;
		file = getstyrefile("styrerc", "r");
		char* theline = ffindline(file, "DEFCOM");
		char* inside = getinsidequotes(theline);
		
		// Issue #1 //
		int i;
		for (i = 1; i < strlen(inside); ++i)
		{
			int c = inside[i];
			parseargs(&c);
		}

		fclose(file);
		return 0;
	}

	int c;
	while ((c = getopt(argc, argv, "L:S:E:G")) != -1)
	{ 
		parseargs(&c);
	}
	
	return 0;
}

