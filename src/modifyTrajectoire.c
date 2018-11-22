#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libtrajectoire.h"


/* -------------------------USELESS FUNCTIONS-------------------
/////////////////////////////////////////////////////////////////////////
int modify_sysdyn_file_param(char file_name[])
{

	char* new_equ=fgetEquations(file_name);
	

	FILE *fp = fopen(file_name,"w+");
	
	//	ERROR HANDLING	
	if (!fp)
	{
		perror("File opening failed");
		return EXIT_FAILURE;
	}

	Parametres new_param=(Parametres)malloc(sizeof(Parametres));
	new_param=scan_param();


	fprintf(fp, "%f\n", new_param->dt);
	fprintf(fp, "%d\n", new_param->Tmax);

	fprintf(fp, "%lf\n", new_param->point_init->x);
	fprintf(fp, "%lf\n", new_param->point_init->y);
	fprintf(fp, "%lf\n", new_param->point_init->z);

	fprintf(fp, "%s", new_equ);
	fclose(fp);


	return 0;
}




int modify_sysdyn_file_equations(Sys_equation new_equations)
{
	char* file_name=(char *)malloc(SYS_NAME_SIZE_LIMIT*sizeof(char));

	add_extension_to_name(file_name, new_equations->nom_sys, ".sysdyn");

	char* new_param=fgetParam(file_name);


	FILE *fp = fopen(file_name, "w+");

	if (!fp)
	{
		perror("File opening failed");
		return EXIT_FAILURE;
	}

	fprintf(fp, "%s",new_param);
	
	fprintf(fp, "%s\n", new_equations->dx);
	fprintf(fp, "%s\n", new_equations->dy);
	fprintf(fp, "%s\n", new_equations->dz);

	fprintf(fp, "%s\n", new_equations->nom_sys);


	fclose(fp);
	return 0;
}


/////////////////////////////////////////////////////////////////////////




*/


void modify_struct_point(Trajectoire trajectoire)
{
	trajectoire->parametres->point_init=scanPoint();

}
void modify_struct_param(Trajectoire trajectoire)
{
	char choix;
	do
	{
		printf("\nEnter: \n\t'i' to modify initial point");
		printf("\n\t't' to modify Time interval\n");

	}while ((choix = getchar()) != 'i' && choix != 't');
	clear();
	if(choix=='i')
	{
		modify_struct_point(trajectoire);
		return;
	}
	if(choix=='t')
	{
		trajectoire->parametres->Tmax=scanInt("Tmax");
		trajectoire->parametres->dt=scandv("dt");
		return;
	}


}

void modify_struct_equations(Trajectoire trajectoire)
{
	trajectoire->equations = scan_equations();
}

int modifyTrajectoire(char* nom_trajectoire)
{
	Trajectoire trajectoire = convert_sysdyn_file_to_struct(nom_trajectoire);
	

	char choix;

	do
	{
		printf("\n\n\nEnter:\n\t'p' to modify the Parameters\n\t'e' to modify the Equations\n\t'n' the system name\n\t'q' to abort modification\n");

	} while ((choix = getchar()) != 'e' && choix != 'p' && choix != 'n' && choix != 'q');
	clear();
	if(choix=='e')
	{

		modify_struct_equations(trajectoire);

		
	}
	if(choix=='p')
	{

		modify_struct_param(trajectoire);


	}
	if(choix=='q')
	{
		return 0;
	}
	if(choix=='n')
	{

		trajectoire->nom_sys=scanNom();

		
	}
	if (choix == 'e' || choix=='p')
	{
		char choice;
		do
		{
			printf("\nDo you want to save modifications in a new System and keep the old one? y/n\n");
		} while ((choice = getchar()) != 'n' && choice != 'y');
		if (choix == 'y')
		{
			clear();
			printf("Enter the new system Name to save this modification\n");
			trajectoire->nom_sys = scanNom();
		}
	}
	convert_struct_to_sysdyn_file(trajectoire);

	convert_struct_to_function(trajectoire);

	plot(trajectoire->nom_sys);

	return 0;
	
}