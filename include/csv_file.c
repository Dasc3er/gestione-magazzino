#include <csv_file.h>
#include <csv_row.h>
#include <stdio.h>
#include <stdlib.h>

csv_file* csv_init(char *filename, int has_header) {
	csv_file *pointer = malloc(sizeof(csv_file));

	pointer->filepath = filename;
	pointer->has_header = has_header != 0;
	pointer->current_byte = 0;
	pointer->line_counter = 0;

	// Lettura dell'header (se presente)
	csv_row *header = csv_read_line(pointer);

	// Conteggio dei campi
	pointer->field_counter = header->field_counter;

	// Informazioni sull'header
	if (pointer->has_header) {
		pointer->header = header->contents;
		pointer->header_bytes = header->bytes;
	} else {
		free(header->contents);
	}

	free(header);

	return pointer;
}

void csv_free(csv_file *csv) {
	if (csv->has_header) {
		free(csv->header);
	}

	free(csv);
}

