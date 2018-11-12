#include"trajectoire.h"
#ifndef CONVERTTOFILE_H
#define CONVERTTOFILE_H

int convert_struct_to_sysdyn_file(Trajectoire trajectoire);

int charToInt(char *c);
float charToFloat(char *c);

int convert_struct_to_function(Trajectoire trajectoire);
//creates a function.c and function.h library and it adds to actual one so it can be used by main

int convert_struct_to_data_file(Fonctions f, Parametres param_init, char file_name[]);

Trajectoire convert_sysdyn_file_to_struct(char file_name[]);

int convert_sysdyn_file_to_function(char file_name[]);

#endif