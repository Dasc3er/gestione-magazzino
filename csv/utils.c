#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void check_allocation(void *pointer)
{
	if (pointer == NULL)
	{
		fprintf(stderr, "Errore di allocazione dinamica\n");
		exit(EXIT_FAILURE);
	}
}
