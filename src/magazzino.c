#include <string.h>
#include <stdlib.h>
#include "magazzino.h"
#include "utils.h"

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

		// Lettura quantità e conversione in float
		float quantita = atof(csv_row_field(line, "Quantità"));

		printf(" %-10s | %-40s | %8.1f \n", codice, descrizione, quantita);
	}
}

csv_row *cerca_articolo(csv_file *csv_magazzino)
{
	// Richiesta del codice all'utente
	printf("Codice dell'articolo da cercare: ");
	char *codice_articolo = read_content();

	// Ripristino inizio del file
	csv_reset(csv_magazzino);

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

	// Liberazione della memoria allocata per il codice articolo
	free(codice_articolo);

	// Messaggio di successo o fallimento ricerca
	if (row != NULL)
	{
		printf("Articolo individuato: %s\n", csv_row_field(row, "Descrizione"));
	}
	else
	{
		printf("Impossibile trovare un articolo con il codice indicato\n");
	}

	return row;
}

void articoli_esaurimento(csv_file *csv_magazzino, csv_file *csv_storico)
{
}

void inserisci_articolo(csv_file *csv_magazzino, csv_file *csv_storico)
{
}

void modifica_articolo(csv_file *csv_magazzino, csv_file *csv_storico)
{
}

void rimuovi_articolo(csv_file *csv_magazzino, csv_file *csv_storico)
{
	// Ricerca articolo
	csv_row *row = cerca_articolo(csv_magazzino);
	if (row != NULL)
	{
		// Rimozione articolo
		csv_write(row->csv, row->line_number, "");
		csv_row_free(row);

		printf("Articolo rimosso!");
	}
}