#include <stdlib.h>
#include "csv_records.h"
#include "csv_row.h"
#include "utils.h"

csv_records* csv_read(csv_file *file) {
	// Inizializzazione del contenitore dei record
	csv_records *results = malloc(sizeof(csv_records));
	check_allocation(results);
	results->length = 0;

	int length = 100;
	size_t pointer_size = sizeof(csv_row*);
	csv_row **contents = malloc(pointer_size * length);
	check_allocation(contents);

	// Apertura del file
	FILE *fp = file_open(file->filepath);

	// Rimozione dell'header dai risultati
	if (file->has_header) {
		fseek(fp, file->header_bytes, SEEK_SET);
	} else {
		fseek(fp, 0L, SEEK_SET);
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
		line->csv = file;

		error = csv_row_wrap(line, fp);
		if (error) {
			free(line);
		} else {
			*(contents + index) = line;
			index++;
		}
	}

	// Chiusura del file
	file_close(fp);

	// Reallocazione finale
	length = index;
	contents = realloc(contents, pointer_size * length);

	// Salvataggio dei risultati
	results->results = contents;
	results->length = length;

	return results;
}

void csv_records_free(csv_records *records) {
	// Liberazione delle singole righe
	for (int i = 0; i < records->length; i++) {
		csv_row *line = *(records->results + i);
		csv_row_free(line);
	}

	// Liberazione dell'array dei risultati
	free(records->results);

	// Liberazione dello struct dalla memoria dinamica
	free(records);
}

