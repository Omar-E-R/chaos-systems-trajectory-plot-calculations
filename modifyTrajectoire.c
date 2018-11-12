#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include"modifyTrajectoire.h"

void modify_struct_param(Trajectoire trajectoire)
{
	trajectoire->parametres=scan_param();


}

void modify_struct_equations(Trajectoire trajectoire)
{
	trajectoire->equations = scan_equations();
}



int modify_sysdyn_file_param(char file_name[])
{

	char* new_equ=fgetEquations(file_name);
	

	FILE *fp = fopen(file_name,"w+");
	
	/*	ERROR HANDLING	*/
	if (!fp)
	{
		perror("File opening failed");
		return EXIT_FAILURE;
	}
	Parametres new_param=scan_param();

	fprintf(fp, "%s\n",file_name);

	fprintf(fp, "%f\n", new_param->dt);
	fprintf(fp, "%d\n", new_param->Tmax);

	fprintf(fp, "%Lf\n", new_param->point_init->x);
	fprintf(fp, "%Lf\n", new_param->point_init->y);
	fprintf(fp, "%Lf\n", new_param->point_init->z);

	fprintf(fp, "%s", new_equ);

	fclose(fp);


	return 0;
}




int modify_sysdyn_file_equations(char file_name[])
{
	
	char* new_param= fgetParam(file_name);


	FILE *fp = fopen(file_name, "w+");

	
	if (!fp)
	{
		perror("File opening failed");
		return EXIT_FAILURE;
	}

	Sys_equation new_equations = scan_equations();



	fprintf(fp, "%s",new_param);
	
	fprintf(fp, "%s\n", new_equations->dx);
	fprintf(fp, "%s\n", new_equations->dy);
	fprintf(fp, "%s\n", new_equations->dz);

	fprintf(fp, "%s\n", new_equations->nom_sys);


	fclose(fp);
	return 0;
}



int modifyTrajectoire(char file_name[])
{
	char choix;
	do
	{
		printf("\nTo modify Parameters enter p, or enter e to modify Equations:");
	}while((choix=getchar())!='e' && choix!='p' );

	if(choix=='p')
	{
		modify_sysdyn_file_param(file_name);
		convert_sysdyn_file_to_function(file_name);
	}
	if(choix=='e')
	{
		modify_sysdyn_file_equations(file_name);
		convert_sysdyn_file_to_function(file_name);
	}
	return 0;
	
}