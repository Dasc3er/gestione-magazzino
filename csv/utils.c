#include <stdlib.h>
#include "utils.h"

void check_allocation(void *pointer) {
	if (pointer == NULL) {
		fprintf(stderr, "Errore di allocazione dinamica\n");
		exit(EXIT_FAILURE);
	}
}

FILE* file_open(char *filepath) {
	// Apertura del file
	FILE *fp = fopen(filepath, "r+");
	if (fp == NULL) {
		fprintf(stderr, "Impossibile aprire il file %s\n", filepath);
		exit(EXIT_FAILURE);
	}

	// Ripristino all'inizio del file
	fseek(fp, 0L, SEEK_SET);

	return fp;
}

void file_close(FILE *file) {
	fclose(file);
}
