#include <stdio.h>
#include <stdlib.h>
#include "libtrajectoire.h"
#ifdef ROOT

int plot_trajectoire(char* nom_trajectoire)
{
	//char* commands[]={"set parametric","splot","using","2:3:4","5:6:7""set terminal jpeg","set output","set margin","set multiplot"};
	//char* styles[]={"with","lines","dots","points","linespoints","vector","filled head"};
	//char* morestyles[]={"lc","lt","lw"};

	FILE* gnuplotc=popen("cd "ROOT"/data && gnuplot -persistent","w");

	if (!gnuplotc)
	{
		perror("File opening failed");
		return EXIT_FAILURE;
	}
	fprintf(gnuplotc,"set multiplot\n");
	fprintf(gnuplotc,"set title \"EL RIFAI OMAR:%s\"\n",nom_trajectoire);
	fprintf(gnuplotc,"set parametric\nsplot \"%s.dat\" using 2:3:4 with lines lw 0 lc 1\n",nom_trajectoire);
	fprintf(gnuplotc,"splot \"%s.dat\" using 2:3:4:5:6:7 with vectors filled head lw 0 lc 2\n",nom_trajectoire);
	fprintf(gnuplotc,"splot \"%s.dat\" using 8:9:10:11:12:13 with vectors filled head lw 0 lc 3\n",nom_trajectoire);
	fprintf(gnuplotc,"splot \"%s.dat\" using 2:3:4:5:6:7 with vectors filled head lw 0 lc 5\n",nom_trajectoire);
	fprintf(gnuplotc,"splot \"%s.dat\" using 8:9:10:11:12:13 with vectors filled head lw 0 lc 6\nexit\n",nom_trajectoire);
	//fprintf(gnuplotc,"%s %c%s%s%c %s\n",commands[1],'"',nom_trajectoire,".dat",'"',commands[2]);
	//fprintf(gnuplotc,"%s\n%s %c%s%s%c %s\n",commands[0],commands[1],'"',nom_trajectoire,".dat",'"',commands[2]);

	pclose(gnuplotc);

	return 0;
}
int plot(char* nom_trajectoire)
{
	FILE *compileSys = popen("cd "ROOT" && make plot", "w");

	if (!compileSys)
	{
		perror("File opening failed");
		return EXIT_FAILURE;
	}
	pclose(compileSys);
	plot_trajectoire(nom_trajectoire);
	return 0;
}
#endif