#ifndef CSV_ROW_H_
#define CSV_ROW_H_

#include <csv_file.h>
#include <stdio.h>

/**
 * Struct per la rappresentazione delle informazioni di una riga.
 *
 * @param csv Puntatore al CSV di origine
 * @param field_counter Numero di campi della riga
 *
 * @param line_number Numero della riga
 * @param bytes Numero di bytes della riga
 * @param contents Contenuti separati per campo
 */
typedef struct {
	csv_file *csv;
	int field_counter;

	long line_number;
	long bytes;
	char **contents;
} csv_row;

csv_row* csv_read_line(csv_file *csv);

char* csv_row_field(csv_row *csv_row, char *name);

/**
 * Restituisce il contenuto della riga CSV  la memoria dinamica utilizzata per lo struct della riga CSV.
 */
char* csv_row_field_by_index(csv_row *csv_row, int index);

/**
 * Libera la memoria dinamica utilizzata per lo struct della riga CSV.
 */
void csv_row_free(csv_row *line);

/**
 * Funzione dedicata all'interpretazione del formato CSV e alla relativa suddivisione dei campi.
 */
int csv_row_wrap(csv_row *csv_row, FILE *fp);

#endif /* CSV_ROW_H_ */
