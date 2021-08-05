#ifndef HELPER_HEADER
#define HELPER_HEADER

FILE* getstyrefile(char* filepath, char* mode);
void parseargs(int *c, char *arg);
char* fgetline(FILE *fp, int line);
char* ffindline(FILE *fp, char *text);
char* getinsidequotes(char *text);
char* getusername();
char* styresplit(char *text, int sec);

void G(char* arg);
void L(char* arg);
void S(char* arg);
void E(char* arg);

FILE* getstyrefile(char* filepath, char* mode)
{
	FILE *fp;
	char *username, path[255]; 
	username = getusername();
	sprintf(path, "/home/%s/.styre/%s", username, filepath);

	if ((fp = fopen((char*)path, mode)) == NULL)
	{
		printf("File \"%s\" not found! Error [01]\n", path);
		exit(1);
	} 
	
	return fp; 
}

void parseargs(int *c, char* arg)
{
	switch(*c) 
	{
		case 'L':
			L(arg);
			break;

		case 'S':
			S(arg);
			break;

		case 'E':
			E(arg);
			break;

		case 'G':
			G(arg);
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
			if (k == 0 && line[k] == '#')
				continue;
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
	return strtok(strchr(text, '"'), "\"");
}

char* getusername()
{
	static char *username;
	if (username != NULL)  
	{
		return username;
	}

	username = (char*)malloc(50 * sizeof(char));
	if (getlogin_r(username, sizeof(username)) != 0)
	{
		printf("Error fetching username! Error [02]\n");
		char c;
		printf("Would you like to enter the current user's name? [Y/n] : ");
		c = getc(stdin);
		if (c == 'y' || c == 'Y' || c == '\n')
		{
			printf("Username: ");	
			scanf("%s", username);
			return username;	
		}
		else
		{
			// mayb i should close file???? //
			exit(1);
		}
	}
	return username;
}

char* styresplit(char *text, int sec)
{
	char *temp; 
	temp = (char*)malloc(strlen(text) * sizeof(char));
	strcpy(temp, text);
	char *ptr = strtok(temp, ":");
	int iter;
	iter = 0;
	while (ptr != NULL)
	{
		++iter;
		if (iter == sec)
		{
			return ptr;
		}
		ptr = strtok(NULL, ":");
	}
	return NULL;
}

#endif 
