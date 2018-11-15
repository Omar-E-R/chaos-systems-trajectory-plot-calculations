#include<stdio.h>
#include<stdlib.h>
#include"libtrajectoire.h"
Point* initpoint()
{
	Point* pt = (Point*)malloc(sizeof(Point*));
	return pt;
}

Point* initPoint(double x, double y, double z)
{
	Point* pt = initpoint();

	pt->x=x;
	pt->y=y;
	pt->z=z;

	return pt;
}

Parametres initparametres()
{
	Parametres param = (Parametres)malloc(sizeof(Parametres));
	param->point_init=initpoint;
	return param;
}

Parametres initParametres(float dt, int Tmax, Point* pt)
{
	Parametres param = initparametres();

	param->dt = dt;
	param->Tmax = Tmax;
	param->point_init= pt;
	
	return param;
}


Sys_equation initequations()
{
	Sys_equation equ = (Sys_equation)malloc(sizeof(Sys_equation));

	equ->nom_sys = (char *)malloc(2 * SYS_NAME_SIZE_LIMIT * sizeof(char));

	equ->dx = (char *)malloc(EQU_SIZE_LIMIT * sizeof(char));
	equ->dy = (char *)malloc(EQU_SIZE_LIMIT * sizeof(char));
	equ->dz = (char *)malloc(EQU_SIZE_LIMIT * sizeof(char));

	return equ;
}
Sys_equation initEquations(char* dx, char* dy, char* dz, char* nom_system)
{
	Sys_equation equ = initequations();

	equ->nom_sys = nom_system;

	equ->dx = dx;
	equ->dy = dy;
	equ->dz = dz;

	return equ;
}



Trajectoire inittrajectoire()
{
	Trajectoire traject = (Trajectoire)malloc(sizeof(Trajectoire));

	traject->equations=initequations();
	traject->parametres=initparametres();


}

Trajectoire initTrajectoire(Sys_equation equ, Parametres param)
{
	Trajectoire traject = inittrajectoire();

	traject->equations =equ;
	traject->parametres = param;

	return traject;
}

