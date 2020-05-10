#include <stdlib.h>
#include "csv_records.h"
#include "csv_row.h"
#include "utils.h"

csv_records* csv_read(csv_file *csv) {
	// Inizializzazione del contenitore dei record
	csv_records *results = malloc(sizeof(csv_records));
	check_allocation(results);
	results->length = 0;

	int length = 100;
	size_t pointer_size = sizeof(csv_row*);
	csv_row **contents = malloc(pointer_size * length);
	check_allocation(contents);

	// Apertura del file
	FILE *file = file_open(csv->filepath);

	// Rimozione dell'header dai risultati
	if (csv->has_header) {
		fseek(file, csv->header_bytes, SEEK_SET);
	} else {
		fseek(file, 0L, SEEK_SET);
	}

	// Lettura delle righe
	int error = 0;
	int index = 0;
	while (!error) {
		// Allargamento dell'elenco risultati
		if (index >= length) {
			length = length * 2;
			contents = realloc(contents, pointer_size * length);
			check_allocation(contents);
		}

		// Creazione della singola riga
		csv_row *line = malloc(sizeof(csv_row));
		line->csv = csv;

		error = csv_row_wrap(line, file);
		if (error) {
			free(line);
		} else {
			*(contents + index) = line;
			index++;
		}
	}

	// Chiusura del file
	file_close(file);

	// Reallocazione finale
	length = index;
	contents = realloc(contents, pointer_size * length);
	check_allocation(contents);

	results->results = contents;
	results->length = length;

	return results;
}

void csv_records_free(csv_records *records) {
	for (int i = 0; i < records->length; i++) {
		csv_row *line = *(records->results + i);
		free(line);
	}

	free(records);
}

