#include <stdio.h>
#include <stdlib.h>
#include "libtrajectoire.h"

int plot_trajectoire(char* data_file_name)
{
	//ADD COLOR SETTINGS AND SHIT
	char* commands[]={"set parametric", "splot","u 2:3:4"};
	FILE* gnuplotc=popen("cd data && gnuplot -persistent","w");

	if (!gnuplotc)
	{
		perror("File opening failed");
		return EXIT_FAILURE;
	}
	fprintf(gnuplotc,"%s\n%s %c%s%c %s\n",commands[0],commands[1],'"',data_file_name,'"',commands[2]);
	pclose(gnuplotc);

	return 0;
}
int plot(char* nom_trajectoire)
{
	FILE *compileSys = popen("make plot", "w");

	if (!compileSys)
	{
		perror("File opening failed");
		return EXIT_FAILURE;
	}
	fprintf(compileSys, "./bin/%s", nom_trajectoire);
	pclose(compileSys);
	return 0;
}