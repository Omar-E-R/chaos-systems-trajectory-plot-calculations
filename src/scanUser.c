#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libtrajectoire.h"

/* ------TO CLEAR THE BUFFER---*/

void clear()
{
	char c;
	while (((c = getchar())!='\n') && (c != EOF) && (c!='\0'));
}

/*--------------ADD THE EXTENSION .C OR .SYSDYN TO THE SYSTEM NAME (NULL TERMINATED STRING) SO WE GET THE FILNAME------*/
char*  add_extension_to_name(char* nom_trajectoire, char* dot_extension, char* directory)
{

	char *file_name = initnom();

	if(directory!=NULL)
	{
		strcpy(file_name, directory);
	}

	strcat(file_name, nom_trajectoire);

	if(dot_extension!=NULL)
	{
		strcat(file_name, dot_extension);
	}


	return file_name;
}



int getNom(char* nom)
{

	int read;
	int i=0;

	while((read = getchar())!= EOF && read != '\n')
	{
		if (!isalpha(read))
		{
			puts("Error: Invalid character, name can only contains alphanumeric characters \"ABCDE abcde 01234\"");
			clear();
			return 0;
		}
		nom[i]=read;
		i++;
		if(i == (SYS_NAME_SIZE_LIMIT-15))
		{
			puts("Memory full");
			clear();
			break;
		}
	}

	nom[i]='\0';

	return i;
	
}

char* scanNom()
{
	char* nom=initnom();

	while(1)
	{
		do{
			printf("Nom du systeme:\n");
		}while (!getNom(nom));

		char *file_name = add_extension_to_name(nom, ".sysdyn", "./sysdyn/");

		FILE *sysdyn = fopen(file_name, "r");
		if (!sysdyn)
		{
			puts("Sucess: Dynamic System name");
			break;
		}
		else
		{
			puts("ERROR: DYNAMIC SYSTEM NAME ALREADY EXISTS");
			printf("Nom existe deja, veuillez utiliser un autre nom\n");
		}
	}
	return nom;
}

int scanInt(char* ch)
{
	int t=0;
	while (1)
	{
		printf("\n%s=",ch);
		if (!scanf("%d", &(t)))
		{
			printf("scan%s: syntax error, '%s' is of type 'int'\n",ch,ch);
			clear();
		}
		else
			break;
	}
	return t;
}

double scandv(char* ch)
{
	double dv=0;
	while (1)
	{
		printf("\n%s=",ch);
		if (!scanf("%lf", &(dv)))
		{
			printf("scan%s: syntax error, '%s' is of type 'double'\n",ch,ch);
			clear();
		}
		else
			break;
	}
	return dv;
}
Point scanPoint()
{
	printf("\nEntrez les coordonnees du point initiale de trajectoire (x0, y0, z0)\n");

	Point pt=initPoint(scandv("x0"),scandv("y0"), scandv("z0"));

	return pt;
}

Parametres scanParam()
{
	printf("\nEntrez la valeur de l'increment de temps dt puis celle du temps maximale Tmax\n");
	printf("\nAttention: Il y'aura Tmax/dt points.\n");

	
	Parametres param=initParametres(scandv("dt"),scanInt("Tmax"),scanPoint());

	return param;
}

/*









EQUATIONS VERFICAATION IMPLEMENTATION







*/

int getEquation(char V[])
{
	int eq_size=0;
	char c;

	while (((c = getchar()) != EOF && c != '\n'))
	{
		if (c != 32 && eq_size < (EQU_SIZE_LIMIT - 2))// ASCII 32 correspond aux espaces
		{
			if(!(('('<=c && c<='9' && c!=',')||(c=='x')||(c=='y')||(c=='z')))
			{
				printf("-scanUser: getEquation: syntax error, '%c' is not an accepted caracter\n", c);
				clear();
				return 0;
			}
			else
			{
				V[eq_size]=c;
			}
			eq_size++;

		}
	}
	V[eq_size]='\0';//assurer que les string se terminenent par null
	return eq_size;

}


Sys_equation scan_equations()
{
	Sys_equation equ=initequations();
	
	do
	{
		printf("\n(dx/dt)=");
	}while(!getEquation(equ->dx));

	do
	{	
		printf("\n(dy/dt)=");
	}while(!getEquation(equ->dy));

	do
	{	
		printf("\n(dz/dt)=");
	}while (!getEquation(equ->dz));

	return equ;

}



Trajectoire scan_trajectoire()
{
	printf("\n----------------------CREATING NEW SYSTEM--------------------\n");
	Trajectoire traject = initTrajectoire(scanParam(), scan_equations(), scanNom());


	return traject;
}

