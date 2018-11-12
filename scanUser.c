#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include"scanUser.h"




void clear()
{
	char c;
	while (((c = getchar())!='\n') && (c != EOF) && (c!='\0'));
}

char* add_extension_to_name(char nom_trajectoire[], char dot_extension[])
{
	/*		COPYING TRAJECT NAME INTO A STRING OF ENOUGH SIZE TO HOLD ONLY TRAJECT NAME AND EXTENSION + NULL	*/

	int size_name = strlen(nom_trajectoire);
	int size_ext = strlen(dot_extension);

	char nom_file[size_name + size_ext + 1];//+ 1 FOR NULL AT THE END OF STRING

	strcpy(nom_file, nom_trajectoire);

	/*		ADDING EXTENSION TO THE STRING SO IT MATCHES THE FILENAME		*/

	strcat(nom_file, dot_extension);

	return nom_file;
}



int scan_nom(char nom[])
{
	int i = 0;
	char c;
	printf("\nNom du systeme(25 caracteres maximum sans espace et caractere alphanum ou speciaux):");
	while ((c = getchar()) != EOF && c != '\n')
	{
		if (isalpha(c) && i < (SYS_NAME_SIZE_LIMIT - 2))
		{
			nom[i] = c;
			i++;
		}
	}
	return i;
}





Parametres scan_param()
{
	Parametres param=(Parametres)malloc(sizeof(Parametres));

	printf("Entrez les parametres et point initiales\n");

	while (1)
	{
		printf("\ndt=");
		if (!scanf("%f", &(param->dt)))
		{
			printf("-start.c: scan_param: syntax error, 'dt' is of type 'float'\n");
			clear();
		}
		else
			break;
	}
	while (1)
	{
		printf("\nTmax=");
		if (!scanf("%d", &(param->Tmax)))
		{
			printf("-start.c: scan_param: syntax error, 'Tmax' is of type 'int'\n");
			clear();
		}
		else
			break;
	}

	printf("\na t=0, M=(x0, y0, z0)");

	while (1)
	{
		printf("\nx0=");
		if (!scanf("%Lf", &(param->point_init->x)))
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
		if (!scanf("%Lf", &(param->point_init->y)))
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
		if (!scanf("%Lf", &(param->point_init->z)))
		{
			printf("-start.c: scan_param: syntax error, 'z0' is of type 'float'\n");
			clear();
		}
		else
			break;
	}
	return param;
}





int scan_deriv(char V[])
{
	int eq_size=0;
	char c;
	while(((c=getchar()) != EOF && c!='\n'))
	{
		if (c != 32 && eq_size < (EQU_SIZE_LIMIT - 2))
		{
			if(!(('('<=c && c<='9' && c!=',')||(c=='x')||(c=='y')||(c=='z')))
			{
				printf("-start.c: scan_deriv: syntax error, '%c' is not an accepted caracter\n",c);
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
	V[eq_size]='\0';
	
	return eq_size;

}

Sys_equation scan_equations()
{
	Sys_equation equ=(Sys_equation)malloc(sizeof(Sys_equation));

	while (!scan_nom(equ->nom_sys))
	{

		printf("-scan_user.c: scan_equations: syntax error, 'Nom du systeme' can't be (null)\n");

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
	printf("Saisie de donnees:\n");

	trajectoire->equations=scan_equations();
	trajectoire->parametres=scan_param();

	return trajectoire;
}

