#include "csv_row.h"
#include <stdlib.h>
#include <string.h>
#include "utils.h"

csv_row* csv_read_line(csv_file *file) {
	csv_row *line = malloc(sizeof(csv_row));
	line->csv = file;

	// Lettura della riga
	FILE *fp = file_open(file->filepath);
	fseek(fp, file->current_byte, SEEK_SET);
	int error = csv_row_wrap(line, fp);
	file_close(fp);

	// Restituzione di NULL nel caso in cui il record successivo non sia raggiungibile
	if (error) {
		free(line);

		return NULL;
	}

	return line;
}

int csv_row_wrap(csv_row *row, FILE *fp) {
	// Inizializzazione del puntatore all'array di campi
	size_t pointer_size = sizeof(char*);
	int content_size = 0;
	char **contents = malloc(pointer_size * content_size);

	// Avanzamento per evitare la molteplice lettura di singole righe
	long current_byte = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);

	if (current_byte >= size) {
		return 1;
	}

	fseek(fp, current_byte, SEEK_SET);
	long bytes_counter = 0;

	// Inizializzazione della stringa per il salvataggio dei campi in memoria
	int length, index;
	char *line;
	int field_end = 1; // Flag per la generazione di un nuovo campo
	int line_end = 0;

	char c;
	while (!line_end) {
		// Lettura del carattere
		c = fgetc(fp);
		bytes_counter++;

		// Allocazione di una nuova stringa
		if (field_end) {
			index = 0;
			length = 100;
			line = malloc(sizeof(char) * length);
			check_allocation(line);

			field_end = 0;
		}

		// Allargamento della stringa
		if (index >= length) {
			length = length * 2;
			line = realloc(line, sizeof(char) * length);
			check_allocation(line);
		}

		// Controllo sullo stato del campo
		line_end = (c == '\n' || c == EOF);
		field_end = (c == ';' || line_end);

		// Scrittura del carattere nella stringa generale
		*(line + index) = field_end ? '\0' : c;
		index++;

		// Salvataggio del campo separatamente
		if (field_end && index != 1) {
			// Restrizione della stringa alla dimensione attuale
			line = realloc(line, sizeof(char) * index);
			check_allocation(line);

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
	row->line_number = row->csv->line_counter;
	row->bytes = bytes_counter;

	// Aggiornamento CSV
	row->csv->line_counter = row->csv->line_counter + 1;
	row->csv->current_byte = row->csv->current_byte + bytes_counter;

	return 0;
}

char* csv_row_to_line(csv_row *row) {
	// Dimensione della stringa da allocare
	long length = (row->field_counter - 1) + 1; // Numero di separatori + 1 per la chiusura della stringa
	for (int i = 0; i < row->field_counter; i++) {
		length += strlen(*(row->contents + i));
	}

	char *contents = malloc(sizeof(char) * length);
	check_allocation(contents);

	for (int i = 0; i < row->field_counter; i++) {
		if (i != 0) {
			contents = strcat(contents, ";");
		}

		contents = strcat(contents, *(row->contents + i));
	}

	return contents;
}

char* csv_row_field(csv_row *row, char *name) {
	// Controllo sull'inizializzazione dell'header
	if (!row->csv->has_header) {
		return NULL;
	}

	char **header = row->csv->header;
	int field_counter = row->csv->field_counter;

	int index = -1;
	for (int i = 0; i < field_counter; i++) {
		if (strcmp(name, *(header + i)) == 0) {
			index = i;
		}
	}

	return csv_row_field_by_index(row, index);
}

char* csv_row_field_by_index(csv_row *row, int index) {
	int field_counter = row->field_counter;
	char **contents = row->contents;

	if (index >= field_counter || index < 0) {
		return NULL;
	}

	return *(contents + index);
}

void csv_row_free(csv_row *row) {
	for (int i = 0; i < row->field_counter; i++) {
		free(*(row->contents + i));
	}
	free(row->contents);
	free(row);
}
