#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libtrajectoire.h"


char* fgetline(char file_name[], int startLine, int endLine)
{
	FILE *fp = fopen(file_name, "r");

	/*	ERROR HANDLING	*/
	if (!fp)
	{
		perror("File opening failed");
		exit(EXIT_FAILURE);
	}

	int c; //BECAUSE Char TYPE CANT CONTAIN AN EOF

	int nb_of_lines = 0, i=0;//FIRST LINE NUMBER IS 0

	char* stringLine=(char*)malloc(6*EQU_SIZE_LIMIT*sizeof(char)); //CREATING A STRING THAT WILL CONTAIN ALL DATA
	
	while ((c=fgetc(fp)) != EOF)
	{

		if (startLine <= nb_of_lines && nb_of_lines <= endLine) //EQUATIONS ARE REGISTERED AFTER THE 5TH LINE
		{
			stringLine[i] = c;

			i++;
		}
		if (c == '\n')
		{
			nb_of_lines++;
		}
	}
	/*			ERROR WHILE READING THE FILE CHECKING				*/
	if (ferror(fp))
		puts("I/O error when reading");

	fclose(fp);
	/*		DATA GATHERING FINISHED		*/
	return stringLine;
}
char* parser(char* file_name,char startparsingCaracter,char endparsingCaracter, int start, int end)
{
	char* stringToparse=fgetline(file_name, start, end);
	char* result=(char*)malloc(30*MAX_SYSTEMS*sizeof(char));
	int i=0;
	
	while(1)
	{
		if(stringToparse[i] == startparsingCaracter)
		{
			i++;
			while (stringToparse[i] != endparsingCaracter)
			{
				result[i]=stringToparse[i];
				i++;
			}
			break;
		}
		i++;
	}
	result[i]='\0';
	free(stringToparse);
	return result;
}
char* fgetParam(char file_name[])
{
	return fgetline(file_name, 0, 4);
}

char* fgetEquations(char file_name[])
{
	return fgetline(file_name, 5, 9);
}