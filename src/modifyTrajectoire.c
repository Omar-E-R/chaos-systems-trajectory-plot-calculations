#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libtrajectoire.h"

/* -------------------------USELESS FUNCTIONS-------------------*/
/////////////////////////////////////////////////////////////////////////
void modify_struct_param(Trajectoire trajectoire)
{
	trajectoire->parametres=scan_param();


}

void modify_struct_equations(Trajectoire trajectoire)
{
	trajectoire->equations =scan_equations();
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








int modifyTrajectoire(char* nom_trajectoire)
{
	Trajectoire trajectoire=convert_sysdyn_file_to_struct(nom_trajectoire);

	char choix;

	do
	{
		printf("\nEnter:\n\tp to modify the Parameters\n\te to modify the Equations and/or the system name\n");

	}while((choix=getchar())!='e' && choix!='p' );

	if(choix=='p')
	{
		clear();

		trajectoire->parametres= scan_param();


	}
	if(choix=='e')
	{
		clear();

		trajectoire->equations = scan_equations();

		FILE *removeSys = popen("./removeSys.sh", "w");

		if (!removeSys)
		{
			perror("File opening failed");
			return EXIT_FAILURE;
		}
		fprintf(removeSys, "%s\n", trajectoire->equations->nom_sys);
		fprintf(removeSys, "%s\n", nom_trajectoire);
		pclose(removeSys);
	}

	convert_struct_to_sysdyn_file(trajectoire);

	convert_struct_to_function(trajectoire);

	FILE *compileSys = popen("./compileSys.sh", "w");

	if (!compileSys)
	{
		perror("File opening failed");
		return EXIT_FAILURE;
	}
	fprintf(compileSys, "%s", trajectoire->equations->nom_sys);
	pclose(compileSys);
	return 0;
	
}