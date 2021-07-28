#ifndef HELPER_HEADER
#define HELPER_HEADER

void parseargs(int *c);
char* gfetline(FILE *fp, int line);

void parseargs(int *c)
{
	switch(*c) {
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
			G();
			break;

	}

}

char* fgetline(FILE *fp, int line)
{
	int maxlen = 128;
	char *buffer = (char*)malloc(sizeof(char) * maxlen);
	char ch = getc(fp);
	int count, lcount;
	count = lcount = 0;

	while (ch != EOF)
	{
		if (ch == '\n')
		{
			lcount++;
			if (lcount == line)
			{
				buffer[count] = '\0';
				return buffer;
			}
			strcpy(buffer, "");
			count = 0;
			ch = getc(fp);
			continue;
		}

		if (count == maxlen)
		{
			maxlen += 128;
			buffer = realloc(buffer, maxlen);
		}
		buffer[count] = ch;
		count++;
		ch = getc(fp);

	}

	buffer[count] = '\0';
	return buffer;
}

#endif 
