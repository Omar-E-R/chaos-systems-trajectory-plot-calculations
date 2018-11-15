#ifndef FGETTRAJECTOIRE_H
#define FGETTRAJECTOIRE_H
char* fgetline(char file_name[], int startLine, int endLine);
char* parser(char* file_name,char startparsingCaracter,char endparsingCaracter, int start, int end);
char* fgetParam(char nom_trajectoire[]);
char* fgetEquations(char file_name[]);

#endif