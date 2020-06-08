#include <stdlib.h>
#include "csv_records.h"
#include "csv_row.h"
#include "utils.h"

csv_records *csv_read(csv_file *file)
{
	// Inizializzazione del contenitore dei record
	csv_records *results = malloc(sizeof(csv_records));
	check_allocation(results);
	results->length = 0;

	long length = 100;
	size_t pointer_size = sizeof(csv_row *);
	csv_row **contents = malloc(pointer_size * length);
	check_allocation(contents);

	// Ripristino inizio del file
	csv_reset(file);

	// Apertura del file
	FILE *fp = fopen(file->filepath, "r+");
	if (fp == NULL)
	{
		fprintf(stderr, "Impossibile aprire il file: %s\n", file->filepath);
		exit(EXIT_FAILURE);
	}

	// Rimozione dell'header dai risultati
	fseek(fp, file->header_bytes, SEEK_SET);

	// Lettura delle righe
	int error = 0;
	long index = 0;
	while (!error)
	{
		// Allargamento dell'elenco risultati
		if (index >= length)
		{
			length = length * 2;
			contents = realloc(contents, pointer_size * length);
			check_allocation(contents);
		}

		// Creazione della singola riga
		csv_row *line = malloc(sizeof(csv_row));
		line->csv = file;

		error = csv_row_wrap(line, fp);
		if (error)
		{
			free(line);
		}
		else
		{
			*(contents + index) = line;
			index++;
		}
	}

	// Chiusura del file
	fclose(fp);

	// Reallocazione finale
	contents = realloc(contents, pointer_size * index);

	// Salvataggio dei risultati
	results->results = contents;
	results->length = index;

	// Ripristino del file CSV
	csv_reset(file);

	return results;
}

void csv_records_free(csv_records *records)
{
	// Liberazione delle singole righe
	for (int i = 0; i < records->length; i++)
	{
		csv_row *line = *(records->results + i);
		csv_row_free(line);
	}

	// Liberazione dell'array dei risultati
	free(records->results);

	// Liberazione dello struct dalla memoria dinamica
	free(records);
}
