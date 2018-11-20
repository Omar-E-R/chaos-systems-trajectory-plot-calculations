#include<stdio.h>
#include<stdlib.h>
#include"libtrajectoire.h"




int main(int argc, char* argv[])
{
	//stdout=fopen("std.out","w+");
	//stdin=fopen("std.in","r");
	if(argc==1)
	{
		printf("\nSoit un point M qui subit des forces qui ne dependent que de la position et vitesse de point M.\n");

		printf("On utilise les coordonnees cartesiennes (x, y, z) pour reperer le point M dans l'espace.\n");

		printf("Soit le vecteur position de M U=(x,y,z)\n");

		printf("\n>On conclut d'apres la L.F.D que:\n");

		printf("A tout instant t on peut exprimer les derivees partielles de vecteur position de M: dx/dt, dy/dt, dz/dt\n");

		printf("en fonction des constantes et x, y, et z.\n");

		printf("\nA un instant t: U=(X,Y,Z), donc a t+dt: x=X+(dx/dt)(en X)*dt, de meme pour y et z\n");

		printf("Conclusion:\n\tsi on calcule tous les points entre t0 et Tmax(suffisement grand) avec dt=suffisement petit");

		printf("\n\ton pourrait tracer le trajectoire de M avec un incertitude->0 quand en t~0 dt->0 en t>>0 Tmax->infini\n");

		printf("\n[*convention d'ecriture]:\n\t-caracteres speciaux: + - . * / ( )\n\t-lettres pour designer les coordonnees: x y z\n[toute autres caratere serait rejetes et renvoie une erreur]\n");
		printf("\n\nPress any key to continue...\n");

		while(getchar()!='\n');

		printf("\n");
		if(newTrajectoire()==0)
		{
			exit(EXIT_SUCCESS);
		}	
		else
			exit(EXIT_FAILURE);
	}
	if(argc==2)
	{
		printf("----------------MODIFICATIONS DU SYSTEM \"%s\"-------------",argv[1]);
		if(modifyTrajectoire(argv[1])==0)
		{
			exit(EXIT_SUCCESS);
		}	
		else
			exit(EXIT_FAILURE);

	}

	//fclose(stdin);
	//fclose(stdout);
	return 0;

}