#ifndef MODIFYTRAJECTOIRE_H
#define MODIFYTRAJECTOIRE_H

void modify_struct_param(Trajectoire trajectoire);

void modify_struct_equations(Trajectoire trajectoire);

int modify_sysdyn_file_param(char nom_trajectoire[]);

int modify_sysdyn_file_equations(Sys_equation new_equations);

int modifyTrajectoire(char *nom_trajectoire);

#endif