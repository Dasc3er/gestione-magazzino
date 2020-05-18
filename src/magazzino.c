#include <string.h>
#include "magazzino.h"

void visualizza_magazzino(csv_file *csv_magazzino, csv_file *csv_storico)
{
	csv_records *records = csv_read(csv_magazzino);

	// Visualizzazione grafica
	printf("======================================================================\n");
	printf(" %-10s | %-40s | %-10s \n", "Codice", "Descrizione", "Quantità");
	printf("======================================================================\n");

	for (int i = 0; i < records->length; i++)
	{
		csv_row *line = *(records->results + i);
		char *codice = csv_row_field(line, "Codice");
		char *descrizione = csv_row_field(line, "Descrizione");
		char *quantita = csv_row_field(line, "Quantità");

		printf(" %-10s | %-40s | %-10s \n", codice, descrizione, quantita);
	}
}

csv_row *cerca_articolo(csv_file *csv_magazzino, char *codice_articolo)
{
	csv_magazzino->current_byte = csv_magazzino->header_bytes;

	int found = 0;
	csv_row *row = csv_read_line(csv_magazzino);
	while (!found && row != NULL)
	{
		// Ricerca del codice dell'articolo
		char *codice = csv_row_field(row, "Codice");
		if (strcmp(codice_articolo, codice) == 0)
		{
			found = 1;
		}
		else
		{
			// Liberazione memoria allocata
			csv_row_free(row);

			// Lettura riga successiva
			row = csv_read_line(csv_magazzino);
		}
	}

	return row;
}

void inserisci_articolo(csv_file *csv_magazzino, csv_file *csv_storico)
{
}

void modifica_articolo(csv_file *csv_magazzino, csv_file *csv_storico)
{
}

void rimuovi_articolo(csv_file *csv_magazzino, csv_file *csv_storico)
{
}