#include<stdio.h>
#include<stdlib.h>
#include"libtrajectoire.h"


float dt=1.000000;
int Tmax=1;

double Dx(Point* pt)
{
	return 1;
}
double Dy(Point* pt)
{
	return 1;
}double Dz(Point* pt)
{
	return 1;
}


int main(int argc, char* argv[])
{

	Point point_initiale;
	point_initiale.x = 1.000000;
	point_initiale.y = 1.000000;
	point_initiale.z = 1.000000;


	Fonctions lorenz=(Fonctions)malloc(sizeof(Fonctions));

	(lorenz->Dx)=&Dx;
	(lorenz->Dy)=&Dy;
	(lorenz->Dz)=&Dz;

	Parametres param=(Parametres)malloc(sizeof(Parametres));

	param->point_init=&point_initiale;

	param->dt=dt;

	param->Tmax=Tmax;
	convert_struct_to_data_file(lorenz, param, "data/lorenz.dat");
	plot_trajectoire("lorenz.dat");

	return 0;
}