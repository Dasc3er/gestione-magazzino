#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_file.h"
#include "csv_row.h"
#include "utils.h"

csv_file *csv_init(char *filepath, int has_header)
{
	csv_file *pointer = malloc(sizeof(csv_file));

	pointer->filepath = filepath;
	pointer->has_header = has_header != 0;
	pointer->current_byte = 0;
	pointer->line_counter = 1; // Linea 0 riservata all'header

	pointer->field_counter = 0;
	pointer->field_separator = ',';

	// Lettura dell'header (se presente)
	csv_row *header = csv_read_line(pointer);
	if (header == NULL)
	{
		fprintf(stderr, "Errore nella lettura dell'header del file CSV: %s\n", filepath);
		exit(EXIT_FAILURE);
	}

	// Conteggio dei campi
	pointer->field_counter = header->field_counter;

	// Informazioni sull'header
	if (pointer->has_header)
	{
		pointer->header = header->contents;
		pointer->header_bytes = header->bytes;
	}
	else
	{
		free(header->contents);
	}

	// Liberazione della memoria per lo struct dell'header
	free(header);

	// Reimpostazione dello struct
	csv_reset(pointer);

	return pointer;
}

void csv_free(csv_file *file)
{
	if (file->has_header)
	{
		free(file->header);
	}

	free(file);
}

void csv_write(csv_file *file, int line_number, char *content)
{
	// Creazzione nome temporaneo
	int char_size = sizeof(char);
	char *template = "XXXXXX";

	char *filename = malloc(char_size * (strlen(file->filepath) + strlen(template) + 1));
	if (filename == NULL)
	{
		fprintf(stderr, "Errore di allocazione dinamica\n");
		exit(EXIT_FAILURE);
	}
	sprintf(filename, "%s%s", file->filepath, template);
	mkstemp(filename);

	// Spostamento del file originale
	int result = rename(file->filepath, filename);
	if (result != 0)
	{
		printf("Errore nel salvataggio del file\n");
		exit(EXIT_FAILURE);
	}

	// Apertura dei file
	FILE *reader = fopen(filename, "r");
	FILE *writer = fopen(file->filepath, "w+");
	if (writer == NULL || reader == NULL)
	{
		printf("Errore nel salvataggio del file\n");
		exit(EXIT_FAILURE);
	}

	int inserted = 0;
	int was_last_line_empty = 1;
	int line_counter = file->has_header ? 0 : 1; // Linea 0 riservata all'header

	// Aggiunta della riga come prefisso al file (PREPEND)
	if (line_number == -1)
	{
		fputs(content, writer);
		inserted = 1;

		// Controllo sui contenuti
		if (strlen(content) != 0)
		{
			was_last_line_empty = 0;
		}
	}

	size_t buffer_size = 32, characters;
	char *buffer;

	// Allocazione dinamica
	buffer = malloc(buffer_size * sizeof(char));
	check_allocation(buffer);

	// Lettura linea da file
	characters = getline(&buffer, &buffer_size, reader);
	while (characters != -1)
	{
		// Aggiunta del carattere di invio a capo solo se necessario
		if (
			!was_last_line_empty &&
			(line_counter != line_number || strlen(content) != 0)
			)
		{
			fputc('\n', writer);
		}

		// Linea normale
		if (line_counter != line_number)
		{
			int length = strlen(buffer) - 1;
			buffer[length] = '\0'; // Rimozione invio a capo automatico
			fputs(buffer, writer);

			was_last_line_empty = (length == 0);
		}

		// Linea da sostituire
		else
		{
			// Scrittura del nuovo contenuto
			fputs(content, writer);
			inserted = 1;

			was_last_line_empty = strlen(content) == 0;
		}

		// Conteggio della riga
		line_counter++;
		free(buffer);

		// Allocazione dinamica
		buffer = malloc(buffer_size * sizeof(char));
		check_allocation(buffer);

		// Lettura linea da file
		characters = getline(&buffer, &buffer_size, reader);
	}

	free(buffer);

	// Aggiunta della riga come suffisso al file (APPEND)
	if (!inserted || line_number >= line_counter)
	{
		if (!was_last_line_empty && strlen(content) != 0)
			fputc('\n', writer);
		fputs(content, writer);
		inserted = 1;
	}

	// Chiusura dei file
	fclose(writer);
	fclose(reader);

	// Rimozione del file temporaneo
	remove(filename);
	free(filename);
}

void csv_reset(csv_file *file)
{
	// Ripristino inizio del file
	file->current_byte = file->header_bytes;
	file->line_counter = 1;
}

char *csv_header_field(csv_file *file, int index)
{
	// Controllo sulla presenza di header e sugli indici
	if (!file->has_header || index >= file->field_counter || index < 0)
	{
		return NULL;
	}

	return *(file->header + index);
}

int csv_header_field_index(csv_file *file, char *field)
{
	int index = -1;

	// Controllo sulla presenza di header
	if (!file->has_header)
	{
		return index;
	}

	// Ricerca del campo richiesto nell'header
	for (int i = 0; i < file->field_counter; i++)
	{
		if (strcmp(field, *(file->header + i)) == 0)
		{
			index = i;
		}
	}

	return index;
}
