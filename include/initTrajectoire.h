#ifndef INITTRAJECTOIRE_H
#define INITTRAJECTOIRE_H
Point initpoint();
Point initPoint(double x, double y, double z);
Parametres initparametres();
Parametres initParametres(float dt, int Tmax, Point pt);
char* initnom();
char* initequation();
Sys_equation initequations();
Sys_equation initEquations(char* dx, char* dy, char* dz);
Trajectoire inittrajectoire();
Trajectoire initTrajectoire(Parametres param, Sys_equation equ, char* nom_sys);
#endif