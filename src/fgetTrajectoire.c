#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libtrajectoire.h"

char* fgetParam(char file_name[])
{
	FILE *fp = fopen(file_name, "r");

	/*	ERROR HANDLING	*/
	
	if (!fp)
	{
		perror("File opening failed");
		return EXIT_FAILURE;
	}

	int c; //BECAUSE Char TYPE CANT CONTAIN AN EOF

	int nb_of_lines = 0;

	int i=0;

	char* parametres = (char *)malloc(EQU_SIZE_LIMIT*sizeof(char)); //CREATING A STRING THAT WILL CONTAIN ALL parameters OF MAX SIZE =SIZE PARAM_SIZE_LIMIT seperated by an \n
	while ((c = fgetc(fp)) != EOF && nb_of_lines<=4)
	{
		
		if (c == '\n')
		{
			nb_of_lines++;
		}
		parametres[i] = c;
		i++;
	}
	/*			ERROR HANDLING				*/
	if (ferror(fp))
		puts("I/O error when reading");
	

	fclose(fp);
	/*		DATA GATHERING FINISHED		*/

	return parametres;
}


char* fgetEquations(char file_name[])
{
	FILE *fp = fopen(file_name, "r");

	/*	ERROR HANDLING	*/
	if (!fp)
	{
		perror("File opening failed");
		return EXIT_FAILURE;
	}

	int c; //BECAUSE Char TYPE CANT CONTAIN AN EOF

	int nb_of_lines = 0, i=0;

	char* new_sys=(char*)malloc(3*EQU_SIZE_LIMIT*sizeof(char)); //CREATING A STRING THAT WILL CONTAIN ALL 3 EQUATIONS OF MAX SIZE=SIZE EQ_SIZE_LIMIT
	while ((c = fgetc(fp)) != EOF)
	{

		if (nb_of_lines >= 5) //EQUATIONS ARE REGISTERED AFTER THE 5TH LINE
		{
			new_sys[i] = c;

			i++;
		}
		if (c == '\n')
		{
			nb_of_lines++;
		}
	}
	/*			ERROR HANDLING				*/
	if (ferror(fp))
		puts("I/O error when reading");
	else if (feof(fp))
		puts("\nEnd of file reached successfully");

	fclose(fp);
	/*		DATA GATHERING FINISHED		*/
	return new_sys;
}