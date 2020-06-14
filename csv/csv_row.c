/**
 * @file csv_row.c
 * @brief Implementazione delle funzionalità relative alle righe dei file CSV.
 * 
 * File contenente l'implementazione delle funzioni relative alle righe dei file CSV, definite nell'header csv_row.h.
 * 
 * @see csv_row.h
 */

#include "csv_row.h"
#include <stdlib.h>
#include <string.h>
#include "utils.h"

csv_row *csv_read_line(csv_file *file)
{
	// Allocazione dinamica
	csv_row *line = malloc(sizeof(csv_row));
	line->csv = file;

	// Apertura del file
	FILE *fp = fopen(file->filepath, "r+");
	if (fp == NULL)
	{
		fprintf(stderr, "Impossibile aprire il file: %s\n", file->filepath);
		exit(EXIT_FAILURE);
	}

	// Lettura della riga successiva
	fseek(fp, file->current_byte, SEEK_SET);
	int error = csv_row_wrap(line, fp);

	// Chiusura del file
	fclose(fp);

	// Restituzione di NULL nel caso in cui il record successivo non sia raggiungibile
	if (error)
	{
		free(line);

		return NULL;
	}

	return line;
}

int csv_row_wrap(csv_row *row, FILE *fp)
{
	// Inizializzazione del puntatore all'array di campi
	size_t pointer_size = sizeof(char *);
	int content_size = 0;
	char **contents = malloc(pointer_size * content_size);
	check_allocation(contents);

	// Avanzamento per evitare la molteplice lettura di singole righe
	long current_byte = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);

	if (current_byte >= size)
	{
		return 1;
	}

	fseek(fp, current_byte, SEEK_SET);
	long bytes_counter = 0;

	// Inizializzazione della stringa per il salvataggio dei campi in memoria
	long length, index;
	char *line;

	// Carattere separatore
	char separator = row->csv->field_separator;

	char c;			   // Carattere corrente
	int field_end = 1; // Flag per la generazione di un nuovo campo
	int line_end = 0;  // Flag per segnalare la fine della riga
	while (!line_end)
	{
		// Lettura del carattere
		c = fgetc(fp);
		bytes_counter++;

		// Allocazione di una nuova stringa
		if (field_end)
		{
			index = 0;
			length = 100;
			line = malloc(sizeof(char) * length);
			check_allocation(line);

			field_end = 0; // Ripristino flag di chiusura del campo
		}

		// Allargamento della stringa
		if (index >= length)
		{
			length = length * 2;
			line = realloc(line, sizeof(char) * length);
			check_allocation(line);
		}

		// Controllo sullo stato del campo
		line_end = (c == '\n' || c == EOF);
		field_end = (c == separator || line_end);

		// Scrittura del carattere nella stringa generale
		*(line + index) = field_end ? '\0' : c;
		index++;

		// Salvataggio del campo separatamente
		if (field_end)
		{
			if (index != 1)
			{
				// Restrizione della stringa alla dimensione attuale
				line = realloc(line, sizeof(char) * index);
				check_allocation(line);
			}
			// Puntatore a NULL nel caso di campo mancante
			else
			{
				free(line);
				line = NULL;
			}

			// Aggiunta all'elenco dei campi
			content_size++;
			contents = realloc(contents, pointer_size * content_size);
			check_allocation(contents);
			*(contents + content_size - 1) = line;
		}
	}

	// Aggiornamento riga del CSV
	row->contents = contents;
	row->field_counter = content_size;
	row->line_number = row->csv->line_counter; // Campo utilizzato per le righe
	row->bytes = bytes_counter;				   // Campo utilizzato per l'header

	// Aggiornamento CSV
	row->csv->line_counter = row->csv->line_counter + 1;
	row->csv->current_byte = row->csv->current_byte + bytes_counter;

	return 0;
}

char *csv_row_to_line(csv_row *row)
{
	// Dimensione della stringa da allocare
	long length = (row->field_counter - 1) + 1; // Numero di separatori + 1 per la chiusura della stringa
	for (int i = 0; i < row->field_counter; i++)
	{
		char *field = *(row->contents + i);
		long field_length = field != NULL ? strlen(field) : 0; // Supporto a puntatori non inizializzati

		length += field_length;
	}

	char separator = row->csv->field_separator;

	// Allocazione dinamica della memoria per i contenuti dell'intera riga
	char *contents = calloc(length, sizeof(char));
	check_allocation(contents);

	for (int i = 0; i < row->field_counter; i++)
	{
		if (i != 0)
		{
			contents = strncat(contents, &separator, 1);
		}

		char *field_content = *(row->contents + i);
		if (field_content != NULL)
		{
			contents = strcat(contents, field_content);
		}
	}

	return contents;
}

char *csv_row_field(csv_row *row, char *name)
{
	// Ricerca del campo nell'header
	int index = csv_header_field_index(row->csv, name);

	return csv_row_field_by_index(row, index);
}

char *csv_row_field_by_index(csv_row *row, int index)
{
	// Verifica locale degli indici
	if (index >= row->field_counter || index < 0)
	{
		return NULL;
	}

	return *(row->contents + index);
}

void csv_row_free(csv_row *row)
{
	// Liberazione dei singoli campi
	for (int i = 0; i < row->field_counter; i++)
	{
		free(*(row->contents + i));
	}

	// Liberazione dell'array dei campi
	free(row->contents);

	// Liberazione dello struct dalla memoria allocata dinamicamente
	free(row);
}

csv_row *csv_row_create(csv_file *file)
{
	// Inizializzazione struct
	csv_row *row = malloc(sizeof(csv_row));
	row->csv = file;
	row->field_counter = file->field_counter;

	row->line_number = -2; // Impostazione del numero di riga per APPEND

	// Inizializzazione a NULL dei contenuti
	char **contents = malloc(sizeof(char *) * row->field_counter);
	check_allocation(contents);
	for (int i = 0; i < row->field_counter; i++)
	{
		contents[i] = NULL;
	}
	row->contents = contents;

	return row;
}

char *csv_row_field_set(csv_row *row, char *name, char *content)
{
	// Ricerca del campo nell'header
	int index = csv_header_field_index(row->csv, name);

	// Verifica locale degli indici
	if (index >= row->field_counter || index < 0)
	{
		return NULL;
	}

	// Individuazione valore precedente e salvataggio del nuovo contenuto
	char *previous = *(row->contents + index);
	*(row->contents + index) = content;

	return previous;
}
