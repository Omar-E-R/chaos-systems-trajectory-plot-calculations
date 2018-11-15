#ifndef INITTRAJECTOIRE_H
#define INITTRAJECTOIRE_H
Point* initpoint();
Point* initPoint(double x, double y, double z);
Parametres initparametres();
Parametres initParametres(float dt, int Tmax, Point* pt);
Sys_equation initequations();
Sys_equation initEquations(char* dx, char* dy, char* dz, char* nom_system);
Trajectoire inittrajectoire();
Trajectoire initTrajectoire(Sys_equation equ, Parametres param);

#endif