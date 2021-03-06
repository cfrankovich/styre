#ifndef HELPER_HEADER
#define HELPER_HEADER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "declare.h"

FILE* getstyrefile(char* filename, char* mode)
{
	FILE *fp;
	char *username, path[255]; 
	username = getusername();
	sprintf(path, "/home/%s/.styre/%s", username, filename);

	if ((fp = fopen((char*)path, mode)) == NULL)
	{
		printf("File \"%s\" not found! Error [01]\n", path);
		exit(1);
	} 
	
	return fp; 
}

void parseargs(int *c, char* arg, char **argv)
{
	switch(*c) 
	{
		case 'R':
			R(arg, argv[3]);
			break;

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

		case 'D':
			D(arg);
			break;
		
		case 'X':
			X(arg);
			break;

		case 'g':
			g();
			break;
		
		case 'l':
			l();
			break;

		case 's':
			s(arg);
			break;

		case 'e':
			e(arg);
			break;

		case '?':
			fprintf(stderr, "Unkown option '%c'\n", optopt);
			break;

	}

}

char* fgetline(FILE *fp, int line)
{
	int maxlen = 128;
	char *buffer = malloc(sizeof(char) * maxlen);
	int count, lcount;
	count = lcount = 0;
	
	fseek(fp, 0, SEEK_SET);
	char ch = getc(fp);
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
	return NULL;
}

char* ffindline(FILE *fp, char *text, int *num)
{
	int k, len;
	len = strlen(text);
	char *line, comp[len+1];
	*num = 1;
	while ((line = fgetline(fp, *num)) != NULL)
	{
		for (k = 0; k < strlen(text); ++k)
		{
			comp[k] = line[k];
		}
		comp[k] = '\0';

		if ((strcmp(comp, text)) == 0)
		{
			return line;
		}

		(*num)++;	

	}
	return NULL; 
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

	username = malloc(50 * sizeof(char));
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
			exit(1);
		}
	}
	return username;
}

char* styresplit(char *text, int sec)
{
	char *temp; 
	temp = malloc(strlen(text) * sizeof(char));
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
