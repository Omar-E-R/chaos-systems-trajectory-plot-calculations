#ifndef SCANUSER_H
#define SCANUSER_H

void clear();
char*  add_extension_to_name(char* nom_trajectoire, char* dot_extension, char* directory);
int getNom(char* nom);
char* scanNom();
int scanInt(char* ch);
double scandv(char* ch);
Point scanPoint();
Parametres scanParam();
int getEquation(char V[]);
Sys_equation scan_equations();

Trajectoire scan_trajectoire();

#endif