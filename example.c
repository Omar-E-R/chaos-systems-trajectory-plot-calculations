#include<stdio.h>
#include"trajectoire.h"
long double Dx()
{
	//EQUATION IN CODE
	return 0;
}
long double Dy()
{
	//EQUATION IN CODE
	return 0;
}
long double Dz()
{
	//EQUATION IN CODE
	return 0;
}

int main(int argc, char* argv[])
{
	Fonctions f=(Fonctions)malloc(sizeof(Fonctions));

	(f->Dx)=&Dx;
	(f->Dy)=&Dy;
	(f->Dz)=&Dz;

	if(argc>1)\n{
	do_all();
	else
plot_sys(%s.c);
	}
}