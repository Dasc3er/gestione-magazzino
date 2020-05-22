#include <string.h>
#include <stdlib.h>
#include "storico.h"
#include "magazzino.h"
#include "utils.h"

void storico_totale(csv_file *csv_magazzino, csv_file *csv_storico)
{
	// Richiesta di tutte le righe in memoria
	csv_records *records = csv_read(csv_storico);

	// Visualizzazione grafica
	TABLE_HEADER_SEP(TABLE_HEADER_LENTGH);
	printf(" %-10s | %-40s | %-10s \n", "Data", "Codice", "Quantità");
	TABLE_HEADER_SEP(TABLE_HEADER_LENTGH);

	for (int i = 0; i < records->length; i++)
	{
		csv_row *line = *(records->results + i);
		char *data = csv_row_field(line, "Data");
		char *codice = csv_row_field(line, "Codice");
		char *quantita = csv_row_field(line, "Quantità");

		printf(" %-10s | %-40s | %-10s \n", data, codice, quantita);
	}

	// Liberazione della memoria allocata
	csv_records_free(records);
}

void storico_articolo(csv_file *csv_magazzino, csv_file *csv_storico)
{
	char *codice_articolo;
	int length = 0;
	while (length == 0)
	{
		printf("Codice dell'articolo da filtrare: ");
		codice_articolo = read_line();
		length = strlen(codice_articolo);
	}

	// Richiesta di tutte le righe in memoria
	csv_records *records = csv_read(csv_storico);

	// Visualizzazione grafica
	TABLE_HEADER_SEP(TABLE_HEADER_LENTGH);
	printf(" %-10s | %-40s | %-10s \n", "Data", "Codice", "Quantità");
	TABLE_HEADER_SEP(TABLE_HEADER_LENTGH);

	for (int i = 0; i < records->length; i++)
	{
		csv_row *line = *(records->results + i);
		char *codice = csv_row_field(line, "Codice");

		// Filtro sulla base del codice dell'articolo
		if (strcmp(codice_articolo, codice) != 0)
		{
			continue;
		}

		char *data = csv_row_field(line, "Data");
		char *quantita = csv_row_field(line, "Quantità");

		printf(" %-10s | %-40s | %-10s \n", data, codice, quantita);
	}

	// Liberazione della memoria allocata
	csv_records_free(records);
	free(codice_articolo);
}

void movimenta_articolo(csv_file *csv_magazzino, csv_file *csv_storico)
{
	csv_row *row = cerca_articolo(csv_magazzino);
	if (row != NULL)
	{
		float qta_attuale = atof(csv_row_field(row, "Quantità"));
		printf("Quantità attuale: %f\n", qta_attuale);

		printf("Nuova quantità [vuoto per lasciare invariato]: ");

		// Lettura della quantità come stringa, per liberare il buffer di input
		char *quantita = read_line();
		float qta = atof(quantita);

		float diff = qta - qta_attuale;
		printf("\nMovimentazione effettiva: %f\n", diff);

		// Liberazione della memoria allocata per la riga
		csv_row_free(row);
	}
}