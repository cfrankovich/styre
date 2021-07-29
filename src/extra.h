#ifndef HELPER_HEADER
#define HELPER_HEADER

void parseargs(int *c);
char* fgetline(FILE *fp, int line);
char* ffindline(FILE *fp, char *text);
char* getinsidequotes(char *text);

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
				//printf("Returning!\nLC: %d\tL: %d\n", lcount, line);
				buffer[count] = '\0';
				fseek(fp, 0, SEEK_SET);
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

	fseek(fp, 0, SEEK_SET);
	buffer[count] = '\0';
	return "!NOTFOUND!";
}

char* ffindline(FILE *fp, char *text)
{
	// Horrid Code fix l8tr //
	char *line;
	int i, k, m;
	m = 0;
	i = 1;
	while (strcmp((line = fgetline(fp, i)), "!NOTFOUND!") != 0)
	{
		for (k = 0; k < strlen(line); ++k)
		{
			if (text[k] == line[k])
			{
				m++;
				if (m == strlen(text))
					return line;
			}
		}
		i++;	

	}
	
	return "!NOTFOUND!";
}

char* getinsidequotes(char *text)
{
	// Could be NULL //
	return strchr(text, '"');	
}

#endif 
