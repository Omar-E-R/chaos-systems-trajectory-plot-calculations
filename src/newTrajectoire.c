#include <stdio.h>
#include <stdlib.h>
#include "libtrajectoire.h"

int newTrajectoire()
{
	Trajectoire trajectoire=scan_trajectoire();
	char* file_name=(char*)malloc(SYS_NAME_SIZE_LIMIT*sizeof(char));
	add_extension_to_name(file_name,trajectoire->equations->nom_sys,".sysdyn","./sysdyn");
	//char* checkIfexists=(char*)malloc(MAX_SYSTEMS*sizeof(char));

	//checkIfexists=fgetline(file_name,0,10);

	convert_struct_to_sysdyn_file(trajectoire);
	convert_struct_to_function(trajectoire);

	plot(trajectoire->equations->nom_sys);
	return 0;
	
}
