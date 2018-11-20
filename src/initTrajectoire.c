#include<stdio.h>
#include<stdlib.h>
#include"libtrajectoire.h"


Point initpoint()
{
	Point pt = (Point)malloc(sizeof(struct point));

	return pt;
}

Point initPoint(double x, double y, double z)
{
	Point pt = initpoint();

	pt->x=x;
	pt->y=y;
	pt->z=z;

	return pt;
}

Parametres initparametres()
{
	Parametres param = (Parametres)malloc(sizeof(struct parametres));

	param->point_init=initpoint();

	return param;
}

Parametres initParametres(float dt, int Tmax, Point pt)
{
	Parametres param = initparametres();

	param->dt = dt;
	param->Tmax = Tmax;
	param->point_init = pt;
	
	return param;
}

char* initnom()
{
	char* nom_sys= (char *)malloc(SYS_NAME_SIZE_LIMIT * sizeof(char));
	
	return nom_sys;
}

char* initequation()
{
	char* equation = (char *)malloc(EQU_SIZE_LIMIT * sizeof(char));

	return equation;
}

Sys_equation initequations()
{
	Sys_equation equ = (Sys_equation)malloc(sizeof(struct sys_equation));

	equ->dx = initequation();
	equ->dy = initequation();
	equ->dz = initequation();

	return equ;
}
Sys_equation initEquations(char* dx, char* dy, char* dz)
{
	Sys_equation equ = initequations();

	equ->dx = dx;
	equ->dy = dy;
	equ->dz = dz;

	return equ;
}



Trajectoire inittrajectoire()
{
	Trajectoire traject = (Trajectoire)malloc(sizeof(struct trajectoire));

	traject->parametres=initparametres();
	traject->equations=initequations();
	traject->nom_sys=initnom();

	return traject;
}

Trajectoire initTrajectoire(Parametres param, Sys_equation equ, char* nom_sys)
{
	Trajectoire traject = inittrajectoire();

	traject->parametres = param;
	traject->equations =equ;
	traject->nom_sys = nom_sys;

	return traject;
}

