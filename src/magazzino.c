#include <string.h>
#include <stdlib.h>
#include "magazzino.h"
#include "utils.h"

void visualizza_magazzino(csv_file *csv_magazzino, csv_file *csv_storico)
{
	// Richiesta di tutte le righe in memoria
	csv_records *records = csv_read(csv_magazzino);

	// Visualizzazione grafica
	TABLE_HEADER_SEP(TABLE_HEADER_LENTGH);
	printf(" %-10s | %-40s | %10s \n", "Codice", "Descrizione", "Quantità");
	TABLE_HEADER_SEP(TABLE_HEADER_LENTGH);

	for (int i = 0; i < records->length; i++)
	{
		csv_row *line = *(records->results + i);
		char *codice = csv_row_field(line, "Codice");
		char *descrizione = csv_row_field(line, "Descrizione");

		// Lettura quantità e conversione in float
		float quantita = atof(csv_row_field(line, "Quantità"));

		printf(" %-10s | %-40s | %9.1f \n", codice, descrizione, quantita);
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

	// Ripristino del file CSV
	csv_reset(csv_magazzino);

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
	int index_qta = csv_header_field_index(csv_magazzino, "Quantità");
	int index_qta_minima = csv_header_field_index(csv_magazzino, "Quantità minima");
	if (index_qta == -1 || index_qta_minima == -1)
	{
		printf("Impossibile individuare gli articoli in esaurimento a causa della mancanza dei campi Quantità e/o Quantià minima");
	}

	// Visualizzazione grafica
	TABLE_HEADER_SEP(TABLE_HEADER_LENTGH);
	printf(" %-10s | %-40s | %10s | %20s \n", "Codice", "Descrizione", "Quantità", "Quantità minima");
	TABLE_HEADER_SEP(TABLE_HEADER_LENTGH);

	// Ripristino del file CSV
	csv_reset(csv_magazzino);

	// Ciclo riga per riga
	csv_row *row = csv_read_line(csv_magazzino);
	while (row != NULL)
	{
		// Lettura quantità e confronto diretto
		float quantita = atof(csv_row_field_by_index(row, index_qta));
		float quantita_minima = atof(csv_row_field_by_index(row, index_qta_minima));

		if (quantita <= quantita_minima)
		{
			char *codice = csv_row_field(row, "Codice");
			char *descrizione = csv_row_field(row, "Descrizione");

			printf(" %-10s | %-40s | %9.1f | %19.1f \n", codice, descrizione, quantita, quantita_minima);
		}

		// Liberazione memoria allocata
		csv_row_free(row);

		// Lettura riga successiva
		row = csv_read_line(csv_magazzino);
	}

	// Ripristino del file CSV
	csv_reset(csv_magazzino);
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