#include<stdio.h>
#include<stdlib.h>
#include"libtrajectoire.h"


float dt=-382621.000000;
int Tmax=48281601;

double Dx(Point* pt)
{
	return 10*((pt->x)-(pt->y));
}
double Dy(Point* pt)
{
	return (pt->x)*(28-(pt->z))-(pt->y);
}double Dz(Point* pt)
{
	return (pt->x)*(pt->y)-(8/3)*(pt->z);
}


int main(int argc, char* argv[])
{

	Point point_initiale;
	point_initiale.x = -382621.000000;
	point_initiale.y = -382621.000000;
	point_initiale.z = -382621.000000;


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