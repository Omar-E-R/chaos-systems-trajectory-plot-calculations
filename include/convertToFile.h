#ifndef CONVERTTOFILE_H
#define CONVERTTOFILE_H

int convert_struct_to_sysdyn_file(Trajectoire trajectoire);
int convert_struct_to_data_file(Fonction f, Parametres param_init, char file_name[]);
int convert_struct_to_function(Trajectoire traject);
int charToInt(char* c);
double charToFloat(char *c);
Trajectoire convert_sysdyn_file_to_struct(char nom_trajectoire[]);
#endif