#ifndef HELPER_HEADER
#define HELPER_HEADER

FILE* getconfig();
void parseargs(int *c);
char* fgetline(FILE *fp, int line);
char* ffindline(FILE *fp, char *text);
char* getinsidequotes(char *text);

void G();
void L();
void S();
void E();

FILE* getconfig()
{
	FILE *fp;
	char *username, path[255]; 
	username = (char*)malloc(50 * sizeof(char));	
	getlogin_r(username, sizeof(username));
	strcpy(path, "/home/");
	strcat(path, username);
	strcat(path, "/.styre/styrerc");
	
	if ((fp = fopen((char*)path, "r")) == NULL)
	{
		printf("Config file not found!\n");
		exit(1);
	}
	return fp;

}

void parseargs(int *c)
{
	switch(*c) 
	{
		case 'L':
			L();
			break;

		case 'S':
			S();
			break;

		case 'E':
			E();
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
