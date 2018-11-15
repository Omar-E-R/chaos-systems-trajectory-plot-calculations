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
void  add_extension_to_name(char* file_name, char* nom_trajectoire, char* dot_extension)
{

	char str[10]="./data/";
	strcpy(file_name, str);
	strcat(file_name, nom_trajectoire);

	/*		ADDING EXTENSION TO THE STRING SO IT MATCHES THE FILENAME		*/

	strcat(file_name, dot_extension);

}


/*------------SCAN THE NAME OF THE SYSTEM FROM THE USER--------

IT RETURNS THE NUMBER OF CHARACTERS THE STRING CONTAINS, SO WE CAN VERIFY THAT THE STRING IS NOT EMPTY 

*/
int scan_nom(char* nom)
{
	int i = 0;
	char c;
	printf("\nNom du systeme(25 caracteres maximum sans espace et sans caractere alphanum):");
	while ((c = getchar()) != EOF && c != '\n')
	{
		if (isalpha(c) && i < (SYS_NAME_SIZE_LIMIT - 2))
		{
			nom[i] = c;
			i++;
		}
	}
	nom[i]='\0';
	return i;
}



/* ---------------FUNCTION THAT SCANS ALL THE PARAMETERS----------------

			IT  ALLOCATE MEMORY FOR THE VARIBALES

*/

Parametres scan_param()
{
	Parametres param=(Parametres)malloc(sizeof(Parametres));

	param->point_init=(Point*)malloc(sizeof(Point*));

	float dt;
	int Tmax;
	double x;
	double y;
	double z;

	printf("\nEntrez la valeur de l'increment de temps dt puis celle du temps maximale Tmax\n");
	printf("\nAttention: Il y'aura Tmax/dt points.\n");

	while (1)
	{
		printf("\ndt=");
		if (!scanf("%f", &(dt)))
		{
			printf("-scanUser: scan_param: syntax error, 'dt' is of type 'float'\n");
			clear();
		}
		else
			break;
	}
	while (1)
	{
		printf("\nTmax=");
		if (!scanf("%d", &(Tmax)))
		{
			printf("-scanUser: scan_param: syntax error, 'Tmax' is of type 'int'\n");
			clear();
		}
		else
			break;
	}

	param->dt=dt;
	param->Tmax=Tmax;

	printf("\nEntrez les coordonnees du point initiale M0=(x0, y0, z0) a t=0");

	while (1)
	{
		printf("\nx0=");
		if (!scanf("%lf", &(x)))
		{
			printf("-start.c: scan_param: syntax error, 'x0' is of type 'float'\n");
			clear();
		}
		else
			break;
	}

	while (1)
	{
		printf("\ny0=");
		if (!scanf("%lf", &(y)))
		{
			printf("-start.c: scan_param: syntax error, 'y0' is of type 'float'\n");
			clear();
		}
		else
			break;
	}
	while (1)
	{
		printf("\nz0=");
		if (!scanf("%lf", &(z)))
		{
			printf("-start.c: scan_param: syntax error, 'z0' is of type 'float'\n");
			clear();
		}
		else
			break;
	}

	param->point_init->x=x;
	param->point_init->y=y;
	param->point_init->z=z;

	return param;
}





int scan_deriv(char V[])
{
	int eq_size=0;
	char c;

	while(((c=getchar()) != EOF && c!='\n'))
	{
		if (c != 32 && eq_size < (EQU_SIZE_LIMIT - 2))// ASCII 32 correspond aux espaces
		{
			if(!(('('<=c && c<='9' && c!=',')||(c=='x')||(c=='y')||(c=='z')))
			{
				printf("-scanUser: scan_deriv: syntax error, '%c' is not an accepted caracter\n", c);
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
	Sys_equation equ=(Sys_equation)malloc(sizeof(Sys_equation));

	equ->nom_sys=(char *)malloc(2*SYS_NAME_SIZE_LIMIT*sizeof(char));

	equ->dx=(char *)malloc(EQU_SIZE_LIMIT*sizeof(char));
	equ->dy=(char *)malloc(EQU_SIZE_LIMIT*sizeof(char));
	equ->dz=(char *)malloc(EQU_SIZE_LIMIT*sizeof(char));

	while (!scan_nom(equ->nom_sys))
	{

		printf("-scanUser: scan_equations: syntax error, 'Nom du systeme' can't be a (special character) or (null)\n");
	}

	do
	{
		printf("\n(dx/dt)=");
	}while(!scan_deriv(equ->dx));

	do
	{	
		printf("\n(dy/dt)=");
	}while(!scan_deriv(equ->dy));

	do
	{	
		printf("\n(dz/dt)=");
	}while (!scan_deriv(equ->dz));

	return equ;

}



Trajectoire scan_trajectoire()
{
	Trajectoire trajectoire = (Trajectoire)malloc(sizeof(Trajectoire));

	printf("\nSaisie de donnees:\n");

	trajectoire->equations=scan_equations();
	trajectoire->parametres=scan_param();

	return trajectoire;
}

