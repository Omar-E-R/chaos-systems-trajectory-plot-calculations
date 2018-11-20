#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libtrajectoire.h"


char* fgetall(char file_name[])
{
	FILE *fp = fopen(file_name, "r");

	/*	ERROR HANDLING	*/
	if (!fp)
	{
		perror("System Dynamique File opening failed");
		return NULL;
	}

	int c; //BECAUSE Char TYPE CANT CONTAIN AN EOF

	int i=0;//FIRST LINE NUMBER IS 0

	char* str=(char*)malloc(10*EQU_SIZE_LIMIT*sizeof(char)); //CREATING A str THAT WILL CONTAIN ALL DATA
	
	while ((c=fgetc(fp)) != EOF)
	{
		str[i] = c;
		i++;
	
	}
	/*			ERROR WHILE READING THE FILE CHECKING				*/
	if (ferror(fp))
		puts("I/O error when reading");

	fclose(fp);
	/*		DATA GATHERING FINISHED		*/
	return str;
}
char* parser(char *stringToparse, char parsingCaracter, int start, int end)
{
	char* result=(char*)malloc(10*EQU_SIZE_LIMIT*sizeof(char));
	int i=0,j=0;
	int nb=0;

	while(nb<end)
	{
		if(stringToparse[i] == parsingCaracter)
		{
			nb++;
			i++;
		}
		if (start <= nb && nb <end)
		{

			result[j] = stringToparse[i];
			j++;
		}
		i++;
	}
	result[j]='\0';
	return result;
}/*
char* fgetParam(char file_name[])
{
	return fgetall(file_name, 1, 5);
}

char* fgetEquations(char file_name[])
{
	return fgetall(file_name, 6, 10);
}
*/