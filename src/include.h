#ifndef HELPER_HEADER
#define HELPER_HEADER

void parseargs(int *c);

void parseargs(int *c)
{
	switch(*c)
	{
		case 'L':
			printf("Create list\n");
			break;

		case 'S':
			printf("Create subsection\n");
			break;

		case 'E':
			printf("Create entry\n");
			break;

		case 'G':
			printf("Set goal\n");
			break;

	}

}

#endif 
