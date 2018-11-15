#ifndef CONVERTTOFILE_H
#define CONVERTTOFILE_H

int convert_struct_to_sysdyn_file(Trajectoire trajectoire);
int convert_struct_to_data_file(Fonctions f, Parametres param_init, char file_name[]);
int convert_struct_to_function(Trajectoire traject);
int charToInt(char* c);
float charToFloat(char *c);
Trajectoire convert_sysdyn_file_to_struct(char nom_trajectoire[]);
int convert_sysdyn_file_to_function(char file_name[]);

#endif