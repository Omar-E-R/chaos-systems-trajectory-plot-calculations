#ifndef SCANUSER_H
#define SCANUSER_H

void clear();
void  add_extension_to_name(char* file_name, char* nom_trajectoire, char* dot_extension);
int scan_nom(char* nom);
Parametres scan_param();
int scan_deriv(char V[]);
Sys_equation scan_equations();
Trajectoire scan_trajectoire();

#endif