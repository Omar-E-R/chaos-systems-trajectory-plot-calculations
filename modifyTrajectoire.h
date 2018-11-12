#include "trajectoire.h"
#ifndef MODIFYTRAJECTOIRE_H
#define MODIFYTRAJECTOIRE_H

void modify_struct_param(Trajectoire trajectoire);

void modify_struct_equations(Trajectoire trajectoire);

int modify_sysdyn_file_param(char nom_trajectoire[]);

int modify_sysdyn_file_equations(char nom_trajectoire[]);

int modifyTrajectoire(char filename[]);

#endif