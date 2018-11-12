#include"trajectoire.h"
#ifndef SCANUSER_H
#define SCANUSER_H
void clear();

char* add_extension_to_name(char nom_trajectoire[], char dot_extension[]);

int scan_nom(char nom[]);


int scan_deriv(char V[]);

Parametres scan_param();

Sys_equation scan_equations();

Trajectoire scan_trajectoire();

#endif