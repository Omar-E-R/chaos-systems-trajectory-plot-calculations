#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include"convertToFile.h"




int convert_struct_to_sysdyn_file(Trajectoire trajectoire)
{
	
	char* nom_system=add_extension_to_name(trajectoire->equations->nom_sys,".sysdyn");

	FILE *sysdyn = fopen(nom_system, "w+");
	if (!sysdyn)
	{
		perror("File opening failed");
		return EXIT_FAILURE;
	}


	fprintf(sysdyn, "%f\n", trajectoire->parametres->dt);
	fprintf(sysdyn, "%d\n", trajectoire->parametres->Tmax);

	fprintf(sysdyn, "%Lf\n", trajectoire->parametres->point_init->x);
	fprintf(sysdyn, "%Lf\n", trajectoire->parametres->point_init->y);
	fprintf(sysdyn, "%Lf\n", trajectoire->parametres->point_init->z);

	fprintf(sysdyn, "%s\n", trajectoire->equations->dx);
	fprintf(sysdyn, "%s\n", trajectoire->equations->dy);
	fprintf(sysdyn, "%s\n", trajectoire->equations->dz);

	fprintf(sysdyn, "%s\n", trajectoire->equations->nom_sys);

	fclose(sysdyn);
	return 0;
}

int convert_struct_to_function(Trajectoire traject)
{
	Sys_equation systeme=traject->equations;
	char* nom_system = add_extension_to_name(systeme->nom_sys, ".c");

	FILE *fp = fopen(nom_system, "w+");

	if (!fp)
	{
		perror("File opening failed");
		return EXIT_FAILURE;
	}

	int i = 0;

	fprintf(fp, "#include<stdio.h>\n");
	fprintf(fp, "#include\"trajectoire.h\"\n\n\n");

	fprintf(fp, "float dt=%f;\n",traject->parametres->dt);
	fprintf(fp, "int Tmax=%d;\n",traject->parametres->Tmax);
	fprintf(fp, "Point point_initiale;\n");
	fprintf(fp, "point_initiale->x = %Lf;\n", traject->parametres->point_init->x);
	fprintf(fp, "point_initiale->y = %Lf;\n", traject->parametres->point_init->y);
	fprintf(fp, "point_initiale->z = %Lf;\n", traject->parametres->point_init->z);

	fprintf(fp, "long double Dx(Point* pt)\n");
	fprintf(fp, "{\n\treturn ");

	char *dx = (systeme->dx);

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

	free(dx);

	fprintf(fp, ";\n");
	fprintf(fp, "}");

	i = 0;

	fprintf(fp, "\n");

	fprintf(fp, "long double Dy(Point* pt)\n");
	fprintf(fp, "{\n\treturn ");

	char *dy = (systeme->dy);

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

	free(dy);

	fprintf(fp, ";\n");
	fprintf(fp, "}");

	fprintf(fp, "\n");

	i = 0;

	fprintf(fp, "long double Dz(Point* pt)\n");

	fprintf(fp, "{\n\treturn ");

	char *dz = (systeme->dz);

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

	free(dz);

	fprintf(fp, ";\n");
	fprintf(fp, "}");

	fprintf(fp, "\n");

	fprintf(fp, "int main(int argc, char* argv[])\n");
	fprintf(fp, "{\n\t");
	fprintf(fp, "Fonctions %s=(Fonctions)malloc(sizeof(Fonctions));\n",systeme->nom_sys);
	fprintf(fp, "\t(%s->Dx)=&Dx;\n", systeme->nom_sys);
	fprintf(fp, "\t(%s->Dy)=&Dy;\n", systeme->nom_sys);
	fprintf(fp, "\t(%s->Dz)=&Dz;\n", systeme->nom_sys);
	fprintf(fp, "\tif(argc==1)\n{");
	fprintf(fp, "\n\t\t");
	fprintf(fp, "plot_sys(\"%s.dat\");\n",systeme->nom_sys);
	fprintf(fp, "\t}\n");
	fprintf(fp, "\tif(argc==2)\n{");
	fprintf(fp, "\n\t\t");
	fprintf(fp, "plot_sys(\"%s.dat\");\n",systeme->nom_sys);
	fprintf(fp, "\t}\n");
	fprintf(fp, "\n\telse\n");
	fprintf(fp, "\t\tplot_sys(%s.c);",systeme->nom_sys);

	fclose(fp);
	return 0;
}



int convert_struct_to_data_file(Fonctions f, Parametres param_init, char file_name[])
{

	long int j = 0;
	long double x, y, z;

	FILE *dat = fopen(file_name, "w+");

	int Tmax = param_init->Tmax;
	float dt = param_init->dt;
	Point pt0;
	pt0.x = param_init->point_init->x;
	pt0.y = param_init->point_init->y;
	pt0.z = param_init->point_init->z;

	fprintf(dat, "%ld %Lf %Lf %Lf\n", j, pt0.x, pt0.y, pt0.z);

	while (j < (Tmax / dt))
	{
		x = pt0.x + ((*(f->Dx))(&pt0)) * dt;
		y = pt0.y + ((*(f->Dy))(&pt0)) * dt;
		z = pt0.z + ((*(f->Dz))(&pt0)) * dt;

		fprintf(dat, "%ld %Lf %Lf %Lf\n", j, x, y, z);
		pt0.x = x;
		pt0.y = y;
		pt0.z = z;
		j++;
	}
	fclose(dat);

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




float charToFloat(char *c)
{
	int i=0;
	float a=0,b=0;
	while(c[i]!='\0')
	{
		if(c[i]!='.')
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


Trajectoire convert_sysdyn_file_to_struct(char file_name[])
{
	Trajectoire trajectoire = (Trajectoire)malloc(sizeof(Trajectoire));

	int Tmax=0;
	float dt=0;
	Point pt;

	char* param= fgetParam(file_name);

	int i=0, nb_of_lines=0;
	while (1)
	{
		if (param[i]=='\n')
		{

			if(nb_of_lines==0)
			{
				param[i]='\0';
				dt=charToFloat(param);
				param=&(param[i+1]);
			}
			if(nb_of_lines==1)
			{
				param[i]='\0';
				Tmax=charToInt(param);
				param=&(param[i+1]);
			}
			if(nb_of_lines==2)
			{
				param[i]='\0';
				pt.x=charToFloat(param);
				param=&(param[i+1]);
			}
			if(nb_of_lines==3)
			{
				param[i]='\0';
				pt.y=charToFloat(param);
				param=&(param[i+1]);
			}
			if(nb_of_lines==4)
			{
				param[i]='\0';
				pt.z = charToFloat(param);
				break;
			}
			
			nb_of_lines++;
			i=-1;

		}
		i++;
	}

	trajectoire->parametres->dt=dt;
	trajectoire->parametres->Tmax=Tmax;
	trajectoire->parametres->point_init=&pt;

	char* equations=fgetEquations(file_name);

	while (1)
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
				trajectoire->equations->nom_sys=equations;
				break;
			}
			nb_of_lines++;
			i=-1;
		}
		i++;
	}

	return trajectoire;
}

int convert_sysdyn_file_to_function(char file_name[])
{
	Trajectoire traject=convert_sysdyn_file_to_struct(file_name);

	convert_struct_to_function(traject);

	return 0;
}