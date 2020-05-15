#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_file.h"
#include "csv_row.h"

csv_file* csv_init(char *filepath, int has_header) {
	csv_file *pointer = malloc(sizeof(csv_file));

	pointer->filepath = filepath;
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

void csv_free(csv_file *file) {
	if (file->has_header) {
		free(file->header);
	}

	free(file);
}

void csv_write(csv_file *file, int line_number, char *content) {
	// Spostamento del file originale in uno temporaneo
	int char_size = sizeof(char);
	char *template = "XXXXXX";

	char *filename = malloc(char_size * (strlen(file->filepath) + strlen(template) + 1));
	if (filename == NULL) {
		fprintf(stderr, "Errore di allocazione dinamica\n");
		exit(1);
	}
	sprintf(filename, "%s%s", file->filepath, template);
	mkstemp(filename);

	// Spostamento
	int result = rename(file->filepath, filename);
	if (result != 0) {
		printf("Errore nel salvataggio del file\n");
		exit(1);
	}

	// Apertura dei file
	FILE *reader = fopen(filename, "r");
	FILE *writer = fopen(file->filepath, "w+");
	if (writer == NULL || reader == NULL) {
		printf("Errore nel salvataggio del file\n");
		exit(1);
	}

	int inserted = 0;
	int line_counter = 0;
	char c = fgetc(reader);
	while (c != EOF) {
		// Linea normale
		if (line_counter != line_number) {
			fputc(c, writer);

			// Aumento del numero di riga
			if (c == '\n') {
				line_counter++;
			}
		}

		// Linea da sostituire
		else {
			line_counter++;
			inserted = 1;
			int index = 0;

			// Lettura del primo carattere disponibile
			char cl = *(content);
			while (cl != '\0') {
				fputc(cl, writer);
				index++;

				// Lettura carattere successivo
				cl = *(content + index);
			}

			// Rimozione della riga dal file originale
			while (c != '\n' && c != EOF) {
				c = fgetc(reader);
			}
		}

		// Lettura del carattere successivo
		c = fgetc(reader);
	}

	// Aggiunta della riga se il numero era eccessivamente elevato
	if (!inserted && line_number >= line_counter) {
		line_counter++;

		int index = 0;
		// Lettura del primo carattere disponibile
		char cl = *(content);
		while (cl != '\0') {
			fputc(cl, writer);
			index++;

			// Lettura carattere successivo
			cl = *(content + index);
		}
	}

	// Chiusura dei file
	fclose(writer);
	fclose(reader);

	// Rimozione del file temporaneo
	remove(filename);
	free(filename);
}
