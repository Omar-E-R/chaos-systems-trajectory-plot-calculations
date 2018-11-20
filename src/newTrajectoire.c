#include <stdio.h>
#include <stdlib.h>
#include "libtrajectoire.h"

int newTrajectoire()
{
	Trajectoire trajectoire=scan_trajectoire();

	convert_struct_to_sysdyn_file(trajectoire);
	convert_struct_to_function(trajectoire);

	plot(trajectoire->nom_sys);
	return 0;
	
}
