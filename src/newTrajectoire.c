#include <stdio.h>
#include <stdlib.h>
#include "libtrajectoire.h"

int newTrajectoire()
{
	Trajectoire trajectoire=scan_trajectoire();

	convert_struct_to_sysdyn_file(trajectoire);
	convert_struct_to_function(trajectoire);

	FILE *compileSys = popen("./compileSys.sh", "w");

	if (!compileSys)
	{
		perror("File opening failed");
		return EXIT_FAILURE;
	}
	fprintf(compileSys, "%s", trajectoire->equations->nom_sys);
	pclose(compileSys);

	return 0;
	
}
