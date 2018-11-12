#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include"newTrajectoire.h"


char* newTrajectoire()
{
	Trajectoire new_trajet=scan_trajectoire();

	convert_struct_to_sysdyn_file(new_trajet);
	convert_struct_to_function(new_trajet);

	return new_trajet->equations->nom_sys;
	
}
