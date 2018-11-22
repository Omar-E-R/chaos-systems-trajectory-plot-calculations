#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libtrajectoire.h"
#ifdef ROOT

int convert_struct_to_sysdyn_file(Trajectoire trajectoire)
{
	
	char* file_name=add_extension_to_name(trajectoire->nom_sys,SYSDYN,ROOT"/"DATA);

	FILE* sysdyn = fopen(file_name, "r");
	if (!sysdyn)
	{
		sysdyn = fopen(file_name, "w+");
		fputs("\nNew Dynamic System data file is created\n",stderr);
	}
	else
	{
		fclose(sysdyn);
		char *old_name = add_extension_to_name(file_name,".old",NULL);

		int success = rename(file_name, old_name);
		if (success)
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

int convert_struct_to_data_file(Fonction f, Parametres param_init, char* file_name)
{


	FILE *dat = fopen(file_name, "r");
	if (!dat)
	{
		dat = fopen(file_name, "w+");
		fputs("\nNew Dynamic System data file is created\n",stderr);
	}
	else
	{
		char* old_name=initnom();
		
		strcpy(old_name,file_name);
		strcat(old_name,".old");
		
		int success = rename(file_name, old_name);
		
		if (success)
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

	int Tmax = param_init->Tmax;

	double dt = param_init->dt;
	double temps =dt;
	
	Point pt0=param_init->point_init;

	Point pt=initpoint();
	Point vitesse0=initPoint(0,0,0);
	Point vitesse=initPoint(0,0,0);
	Point delta=initPoint(0,0,0);

	fprintf(dat, "0 %lf %lf %lf 0 0 0 0 0 0 0 0 0 0 0\n", pt0->x, pt0->y, pt0->z);

	while (temps < Tmax)
	{
		((*(f->Derive))(pt, pt0, 0));
		((*(f->Derive))(vitesse0, pt0, 2));
		((*(f->Derive))(delta, pt0, 1));
		((*(f->Derive))(vitesse, pt, 2));

		fprintf(dat, "%lf %lf %lf %lf",dt, pt->x, pt->y, pt->z);

		fprintf(dat, " %lf %lf %lf", delta->x, delta->y, delta->z);

		fprintf(dat, " %lf %lf %lf", vitesse->x, vitesse->y, vitesse->z);

		fprintf(dat, " %lf %lf %lf\n", vitesse->x - vitesse0->x, vitesse->y - vitesse0->y, vitesse->z - vitesse0->z);

		temps=temps + dt;

		((*(f->Derive))(pt0, pt, 3));




	}


	fclose(dat);

	return 0;
}




int convert_struct_to_function(Trajectoire traject)
{

	char *file_name = add_extension_to_name(traject->nom_sys,".c",ROOT"/tmp/");

	FILE *fp = fopen(file_name, "w+");

	if (!fp)
	{
		perror("File opening failed");
		return EXIT_FAILURE;
	}


	fprintf(fp, "#include<stdio.h>\n");
	fprintf(fp, "#include<stdlib.h>\n");
	fprintf(fp, "#include\"libtrajectoire.h\"\n\n\n");

	fprintf(fp, "double dt=%f;\n",traject->parametres->dt);
	fprintf(fp, "int Tmax=%d;\n",traject->parametres->Tmax);

	fprintf(fp, "\n");

	fprintf(fp, "void calcultraj(Point pt, Point pt0, int choix)\n");
	fprintf(fp, "{");
	
	fprintf(fp, "\n");
	
	fprintf(fp, "\n\tdouble x, y, z;");
	
	fprintf(fp, "\n\tx = pt0->x;");
	fprintf(fp, "\n\ty = pt0->y;");
	fprintf(fp, "\n\tz = pt0->z;");
	
	fprintf(fp, "\n");
	fprintf(fp, "\n\tif(choix==0)");
	fprintf(fp, "\n");
	fprintf(fp, "\n\t{");
	fprintf(fp, "\n\t\tpt->x = pt0->x + (%s)*dt;", traject->equations->dx);
	fprintf(fp, "\n\t\tpt->y = pt0->y + (%s)*dt;", traject->equations->dy);
	fprintf(fp, "\n\t\tpt->z = pt0->z + (%s)*dt;", traject->equations->dz);
	fprintf(fp, "\n");
	fprintf(fp, "\n\t}");
	fprintf(fp, "\n");

	fprintf(fp, "\n\tif(choix==1)");
	fprintf(fp, "\n\t{");
	fprintf(fp, "\n");
	fprintf(fp, "\n\t\tpt->x = (%s)*dt;", traject->equations->dx);
	fprintf(fp, "\n\t\tpt->y = (%s)*dt;", traject->equations->dy);
	fprintf(fp, "\n\t\tpt->z = (%s)*dt;", traject->equations->dz);
	fprintf(fp, "\n\t");
	fprintf(fp, "\n\t}");

	fprintf(fp, "\n");
	
	fprintf(fp, "\n\tif(choix==2)");
	fprintf(fp, "\n\t{");
	fprintf(fp, "\n\t\tpt->x =  %s;", traject->equations->dx);
	fprintf(fp, "\n\t\tpt->y =  %s;", traject->equations->dy);
	fprintf(fp, "\n\t\tpt->z =  %s;", traject->equations->dz);
	fprintf(fp, "\n");
	fprintf(fp, "\t}");

	fprintf(fp, "\n");
	
	fprintf(fp, "\n\tif(choix==3)");
	fprintf(fp, "\n\t{");
	fprintf(fp, "\n\t\tpt->x = pt0->x;");
	fprintf(fp, "\n\t\tpt->y = pt0->y;");
	fprintf(fp, "\n\t\tpt->z = pt0->z;");
	fprintf(fp, "\n\t}");
	fprintf(fp, "\n");
	fprintf(fp, "}");

	fprintf(fp, "int main(int argc, char* argv[])\n");
	fprintf(fp, "{");
	fprintf(fp, "\n");
	fprintf(fp, "\n");
	fprintf(fp, "\tPoint point_initiale=initPoint(%lf, %lf, %lf);\n", traject->parametres->point_init->x, traject->parametres->point_init->y, traject->parametres->point_init->z);

	fprintf(fp, "\n");
	fprintf(fp, "\n");
	fprintf(fp, "\tFonction %s=(Fonction)malloc(sizeof(struct fonction));\n", traject->nom_sys);
	fprintf(fp, "\n");
	fprintf(fp, "\t(%s->Derive)=&calcultraj;\n", traject->nom_sys);
	fprintf(fp, "\n");
	fprintf(fp, "\tParametres param=initParametres(dt, Tmax, point_initiale);\n");
	fprintf(fp, "\n");

	fprintf(fp, "\tconvert_struct_to_data_file(%s, param, \"%s/data/%s.dat\");\n", traject->nom_sys, ROOT, traject->nom_sys);
	fprintf(fp, "\n");

	fprintf(fp, "\treturn 0;\n");

	fprintf(fp, "}");

	fclose(fp);


	free(file_name);
	return 0;
	/*
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
*/
	
}






int charToInt(char* c)
{
		
	int i=0, negatif=1, max=0;
	if(c[0]=='-')
	{
		max= strlen(c)-1;
		negatif=-1;
		i=1;
	}
	max= strlen(c);
	int res=0;
	while (i<max)
	{
		res = res*10 + (c[i]-48);
		i++;
	}
	return negatif*res;
}




double charToFloat(char *c)
{
	int i=0, negatif=1;
	double a=0,b=0;
	while(c[i]!='\0')
	{
		if(c[i]=='.')
		{
			c[i]='\0';
			if(c[0]=='-')
			{
				a = charToInt(&(c[1]));
				negatif=-1;
			}
			else
				a = charToInt(c);

			b=charToInt(&(c[i+1]));
			i=i+1;
			while (c[i] !='\0')
			{
				b=b/10;
				i++;
			}
			return negatif*(a + b);
		}
		i++;

	}
	return 0;
}

/*--------------------------------------------------------------*/



Trajectoire convert_sysdyn_file_to_struct(char nom_trajectoire[])
{

	char *file_name =add_extension_to_name(nom_trajectoire, SYSDYN,ROOT"/"DATA);

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

#endif