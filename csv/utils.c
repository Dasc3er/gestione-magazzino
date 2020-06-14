/**
 * @file utils.c
 * @brief Implementazione delle funzioni di utility della libreria.
 * 
 * File contenente l'implementazione delle funzioni ausiliarie per la libreria CSV, definite nell'header utils.h.
 * 
 * @see utils.h
 */

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
