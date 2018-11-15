#ifndef TRAJECTOIRE_H
#define TRAJECTOIRE_H

/*
	-ALL EQUATION AND NAMES STRINGS ARE TERMINATED WITH A '\n' FOLLOWED BY '\0'










*/


#define EQU_SIZE_LIMIT 100
#define PARAM_SIZE_LIMIT 20
#define SYS_NAME_SIZE_LIMIT 30

struct point
{
	double x;
	double y;
	double z;
};
typedef struct point Point;




struct sys_equation
{
	char* nom_sys;
	char* dx;
	char* dy;
	char* dz;
};
typedef struct sys_equation *Sys_equation;



struct parametres
{
	Point* point_init;
	float dt;
	int Tmax;
};

typedef struct parametres *Parametres;

struct trajectoire
{
	Sys_equation equations;
	Parametres parametres;
};

typedef struct trajectoire *Trajectoire;

struct fonctions
{
	double (*Dx)(Point *);
	double (*Dy)(Point *);
	double (*Dz)(Point *);
};

typedef struct fonctions *Fonctions;

#include "scanUser.h"
#include "convertToFile.h"
#include "fgetTrajectoire.h"
#include "modifyTrajectoire.h"
#include "newTrajectoire.h"
#include "plotTrajectoire.h"
#endif