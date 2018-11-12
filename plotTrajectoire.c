#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "plotTrajectoire.h"


int plot_c(Trajectoire trajet)
{
	convert_struct_to_function(trajet);
	system("");//RUN TRAJET->NOM.C
	return 0;
}

int read()
{
	FILE *fp = fopen("test.txt", "r");
	if (!fp)
	{
		perror("File opening failed");
		return EXIT_FAILURE;
	}

	int c; // note: int, not char, required to handle EOF
	while ((c = fgetc(fp)) != EOF)
	{ // standard C I/O file reading loop
		putchar(c);
	}

	if (ferror(fp))
		puts("I/O error when reading");
	else if (feof(fp))
		puts("End of file reached successfully");

	fclose(fp);
	return 0;
}
