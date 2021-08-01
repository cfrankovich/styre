#ifndef HELPER_HEADER
#define HELPER_HEADER

FILE* getstyrefile(char* filepath, char* mode);
void parseargs(int *c);
char* fgetline(FILE *fp, int line);
char* ffindline(FILE *fp, char *text);
char* getinsidequotes(char *text);
char* getusername();

void G();
void L();
void S();
void E();

FILE* getstyrefile(char* filepath, char* mode)
{
	FILE *fp;
	char *username, path[255]; 
	username = getusername();
	sprintf(path, "/home/%s/.styre/%s", username, filepath);
	/*
	strcpy(path, "/home/");
	strcat(path, username);
	strcat(path, "/.styre/");
	strcat(path, filepath);
	*/

	if ((fp = fopen((char*)path, mode)) == NULL)
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
	// issue #2 //
	return strchr(text, '"');
}

char* getusername()
{
	char *username;
	username = (char*)malloc(50 * sizeof(char));
	getlogin_r(username, sizeof(username));
	return username;
}

#endif 
