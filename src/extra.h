#ifndef HELPER_HEADER
#define HELPER_HEADER

void parseargs(int *c);
char* gfetline(FILE *fp);

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

char* fgetline(FILE *fp)
{
	int maxlen = 128;
	char *buffer = (char*)malloc(sizeof(char) * maxlen);
	char ch = getc(fp);
	int count = 0;

	while ((ch != '\n') && (ch != EOF))
	{
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
