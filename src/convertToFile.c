#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libtrajectoire.h"

int convert_struct_to_sysdyn_file(Trajectoire trajectoire)
{
	
	char* file_name=add_extension_to_name(trajectoire->nom_sys,".sysdyn","./sysdyn/");

	FILE* sysdyn = fopen(file_name, "r");
	if (!sysdyn)
	{
		sysdyn = fopen(file_name, "w+");
		puts("New Dynamic System data file is created.");
	}
	else
	{
		fclose(sysdyn);
		char *old_name = add_extension_to_name(file_name,".old",NULL);

		int rc = rename(file_name, old_name);
		if (rc)
		{
			perror("Renaming modified Dynamic System");
			return 1;
		}
		sysdyn = fopen(file_name, "w+");
		if (!sysdyn)
		{
			perror("File opening failed");
			return EXIT_FAILURE;
		}
	}
	if (!sysdyn)
	{
		perror("File opening failed");
		return EXIT_FAILURE;
	}

	fprintf(sysdyn, "\n%f\n", trajectoire->parametres->dt);

	fprintf(sysdyn, "%d\n", trajectoire->parametres->Tmax);

	fprintf(sysdyn, "%f\n", trajectoire->parametres->point_init->x);
	fprintf(sysdyn, "%f\n", trajectoire->parametres->point_init->y);
	fprintf(sysdyn, "%f\n", trajectoire->parametres->point_init->z);

	fprintf(sysdyn, "%s\n", trajectoire->equations->dx);
	fprintf(sysdyn, "%s\n", trajectoire->equations->dy);
	fprintf(sysdyn, "%s\n", trajectoire->equations->dz);

	fprintf(sysdyn, "%s\n", trajectoire->nom_sys);

	fclose(sysdyn);

	free(file_name);
	
	return 0;
}

int convert_struct_to_data_file(Fonctions f, Parametres param_init, char* file_name)
{


	FILE *dat = fopen(file_name, "r");
	if (!dat)
	{
		dat = fopen(file_name, "w+");
		puts("New Dynamic System data file is created.");
	}
	else
	{
		fclose(dat);
		char* old_name=(char*)malloc(SYS_NAME_SIZE_LIMIT*sizeof(char));
		strcpy(old_name,file_name);
		strcat(old_name,".old");
		int rc = rename(file_name, old_name);
		if (rc)
		{
			perror("Renaming modified Dynamic System data file");
			return 1;
		}
		dat = fopen(file_name, "w+");
		if (!dat)
		{
			perror("File opening failed");
			return EXIT_FAILURE;
		}
	}


	int j = 0;//INT OR DOUBLE? WHICH IS BETTER? TEST
	double x, y, z;

	int Tmax = param_init->Tmax;
	double dt = param_init->dt;

	Point pt0=initpoint();
	pt0=param_init->point_init;


	fprintf(dat, "%d %lf %lf %lf\n", j, pt0->x, pt0->y, pt0->z);

	while (j < (Tmax / dt))
	{
		x = pt0->x + ((*(f->Dx))(pt0)) * dt;
		y = pt0->y + ((*(f->Dy))(pt0)) * dt;
		z = pt0->z + ((*(f->Dz))(pt0)) * dt;

		fprintf(dat, "%d %lf %lf %lf\n", j, x, y, z);

		pt0->x = x;
		pt0->y = y;
		pt0->z = z;

		j++;
	}


	fclose(dat);

	return 0;
}




int convert_struct_to_function(Trajectoire traject)
{

	char *file_name = add_extension_to_name(traject->nom_sys,".c","./tmp/");

	FILE *fp = fopen(file_name, "w+");

	if (!fp)
	{
		perror("File opening failed");
		return EXIT_FAILURE;
	}

	int i = 0;

	fprintf(fp, "#include<stdio.h>\n");
	fprintf(fp, "#include<stdlib.h>\n");
	fprintf(fp, "#include\"libtrajectoire.h\"\n\n\n");

	fprintf(fp, "float dt=%f;\n",traject->parametres->dt);
	fprintf(fp, "int Tmax=%d;\n",traject->parametres->Tmax);

	fprintf(fp, "\n");

	fprintf(fp, "double Dx(Point pt)\n");
	fprintf(fp, "{");
	fprintf(fp, "\n");
	fprintf(fp, "\treturn ");

	char *dx = (traject->equations->dx);

	while (dx[i] != '\0')
	{
		if (dx[i] == 'x')
			fprintf(fp, "(pt->x)");
		else if (dx[i] == 'y')
			fprintf(fp, "(pt->y)");
		else if (dx[i] == 'z')
			fprintf(fp, "(pt->z)");
		else
			fprintf(fp, "%c", dx[i]);
		i++;
	}
	fprintf(fp, ";");

	fprintf(fp, "\n");

	fprintf(fp, "}");

	i = 0;

	fprintf(fp, "\n");

	fprintf(fp, "double Dy(Point pt)\n");
	fprintf(fp, "{");
	fprintf(fp, "\n");
	fprintf(fp, "\treturn ");
	char *dy = (traject->equations->dy);

	while (dy[i] != '\0')
	{
		if (dy[i] == 'x')
			fprintf(fp, "(pt->x)");
		else if (dy[i] == 'y')
			fprintf(fp, "(pt->y)");
		else if (dy[i] == 'z')
			fprintf(fp, "(pt->z)");
		else
			fprintf(fp, "%c", dy[i]);
		i++;
	}

	fprintf(fp, ";");

	fprintf(fp, "\n");

	fprintf(fp, "}");

	i = 0;

	fprintf(fp, "double Dz(Point pt)\n");
	fprintf(fp, "{");
	fprintf(fp, "\n");
	fprintf(fp, "\treturn ");

	char *dz = (traject->equations->dz);

	while (dz[i] != '\0')
	{
		if (dz[i] == 'x')
			fprintf(fp, "(pt->x)");
		else if (dz[i] == 'y')
			fprintf(fp, "(pt->y)");
		else if (dz[i] == 'z')
			fprintf(fp, "(pt->z)");
		else
			fprintf(fp, "%c", dz[i]);
		i++;
	}

	fprintf(fp, ";");

	fprintf(fp, "\n");

	fprintf(fp, "}");

	fprintf(fp, "\n");
	fprintf(fp, "\n");
	fprintf(fp, "\n");

	fprintf(fp, "int main(int argc, char* argv[])\n");
	fprintf(fp, "{");
	fprintf(fp, "\n");
	fprintf(fp, "\n");
	fprintf(fp, "\tPoint point_initiale=initPoint(%lf, %lf, %lf);\n", traject->parametres->point_init->x, traject->parametres->point_init->y, traject->parametres->point_init->z);

	fprintf(fp, "\n");
	fprintf(fp, "\n");
	fprintf(fp, "\tFonctions %s=(Fonctions)malloc(sizeof(struct fonctions));\n",traject->nom_sys);
	fprintf(fp, "\n");
	fprintf(fp, "\t(%s->Dx)=&Dx;\n", traject->nom_sys);
	fprintf(fp, "\t(%s->Dy)=&Dy;\n", traject->nom_sys);
	fprintf(fp, "\t(%s->Dz)=&Dz;\n", traject->nom_sys);
	fprintf(fp, "\n");
	fprintf(fp, "\tParametres param=initParametres(dt, Tmax, point_initiale);\n");
	fprintf(fp, "\n");


	fprintf(fp, "\tconvert_struct_to_data_file(%s, param, \"data/%s.dat\");\n",traject->nom_sys, traject->nom_sys);
	//fprintf(fp, "\tplot_trajectoire(\"%s.dat\");\n", traject->nom_sys);
	fprintf(fp, "\n");

	
	fprintf(fp, "\treturn 0;\n");
	
	fprintf(fp, "}");

	fclose(fp);

	//free(file_name);

	return 0;
}






int charToInt(char* c)
{
	int i=0, max= strlen(c);
	int res=0;
	while (i<max)
	{
		res = res*10 + (c[i]-48);
		i++;
	}
	return res;
}




double charToFloat(char *c)
{
	int i=0;
	double a=0,b=0;
	while(c[i]!='\0')
	{
		if(c[i]=='.')
		{
			c[i]='\0';
			a=charToInt(c);
			b=charToInt(&(c[i+1]));
			i=i+1;
			while (c[i] !='\0')
			{
				b=b/10;
				i++;
			}
			return a + b;
		}
		i++;

	}
	return 0;
}

/*--------------------------------------------------------------*/



Trajectoire convert_sysdyn_file_to_struct(char nom_trajectoire[])
{

	char *file_name =add_extension_to_name(nom_trajectoire, ".sysdyn","./sysdyn/");

	char *traj = fgetall(file_name);

	Trajectoire trajectoire = initTrajectoire(initParametres(charToFloat(parser(traj, '\n', 1, 2)), charToInt(parser(traj, '\n', 2, 3)), initPoint(charToFloat(parser(traj, '\n', 3, 4)), charToFloat(parser(traj, '\n', 4, 5)), charToFloat(parser(traj, '\n', 5, 6)))), initEquations(parser(traj, '\n', 6, 7), parser(traj, '\n', 7, 8), parser(traj, '\n', 8, 9)), parser(traj, '\n', 9, 10));

	/*
	int Tmax=0;cd
	float dt=0;

	Point *pt=(Point*)malloc(sizeof(Point*));

	char* param=(char*)malloc(EQU_SIZE_LIMIT*sizeof(char));
	
	param=fgetParam(file_name);



	char* p=&(param[0]);

	int i=0, quitt=1, nb_of_lines=0;

	while (quitt>0)
	{
		
		if (p[i]=='\n')
		{

			if(nb_of_lines==0)
			{
				p[i]='\0';

				dt=charToFloat(p);

				p=&(p[i+1]);

			}
			if(nb_of_lines==1)
			{
				p[i]='\0';

				Tmax=charToInt(p);
				p=&(p[i+1]);
			}
			if(nb_of_lines==2)
			{
				p[i]='\0';
				pt->x=charToFloat(p);
				p=&(p[i+1]);
			}
			if(nb_of_lines==3)
			{
				p[i]='\0';
				pt->y=charToFloat(p);
				p=&(p[i+1]);
			}
			if(nb_of_lines==4)
			{
				p[i]='\0';
				pt->z = charToFloat(p);
				quitt=-1;
			}
			nb_of_lines++;
			i=-1;

		}
		i++;
	}

	quitt=1;
	nb_of_lines=0;
	i=0;



	trajectoire->parametres->dt=dt;
	trajectoire->parametres->Tmax=Tmax;
	trajectoire->parametres->point_init=pt;

	char *equ = (char *)malloc(3*EQU_SIZE_LIMIT * sizeof(char));

	equ=fgetEquations(file_name);//ERROR IN NOM_SYS, IF LORENZ -> LORENZ6



	char* equations=&(equ[0]);



	while (quitt > 0)
	{
		if (equations[i] == '\n')
		{
			if (nb_of_lines == 0)
			{
				equations[i] = '\0';
				trajectoire->equations->dx=equations;
				equations= &(equations[i + 1]);
			}
			if (nb_of_lines == 1)
			{
				equations[i] = '\0';
				trajectoire->equations->dy=equations;
				equations= &(equations[i + 1]);
			}
			if (nb_of_lines == 2)
			{
				equations[i] = '\0';
				trajectoire->equations->dz=equations;
				equations= &(equations[i + 1]);
			}
			if (nb_of_lines == 3)
			{
				equations[i] = '\0';
				trajectoire->nom_sys=equations;
				quitt=-7;
			}
			nb_of_lines++;
			i=-1;
		}
		i++;
	}

	//free(equ);
	//free(param);
*/
	return trajectoire;
}