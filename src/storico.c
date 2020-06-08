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
	printf(" %-20s | %-40s | %10s \n", "Data", "Codice", "Quantità");
	TABLE_HEADER_SEP(TABLE_HEADER_LENTGH);

	for (int i = 0; i < records->length; i++)
	{
		csv_row *line = *(records->results + i);
		char *data = csv_row_field(line, "Data");
		char *codice = csv_row_field(line, "Codice");
		float quantita = atof(csv_row_field(line, "Quantità"));

		printf(" %-20s | %-40s | %9.1f \n", data, codice, quantita);
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
	printf(" %-20s | %-40s | %10s \n", "Data", "Codice", "Quantità");
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
		float quantita = atof(csv_row_field(line, "Quantità"));

		printf(" %-20s | %-40s | %9.1f \n", data, codice, quantita);
	}

	// Liberazione della memoria allocata
	csv_records_free(records);
	free(codice_articolo);
}

void movimenta_articolo(csv_file *csv_magazzino, csv_file *csv_storico)
{
	csv_row *articolo = cerca_articolo(csv_magazzino);
	// Controllo sull'individuazione della riga
	if (articolo == NULL)
	{
		return;
	}

	// Lettura della quantità dalla riga
	float quantita_attuale = atof(csv_row_field(articolo, "Quantità"));

	// Lettura della quantità come stringa, per liberare il buffer di input
	printf("Movimentazione [+ per carico in magazzino, - per scarico da magazzino]: ");
	char *movimentazione_inserita = read_line();

	float movimentazione = atof(movimentazione_inserita);
	// Operazioni per la movimentazione
	if (strlen(movimentazione_inserita) != 0 && movimentazione != 0)
	{
		//printf("\nMovimentazione effettiva: %.1f\n", movimentazione);
		//printf("\nMovimentazione effettiva: %.1f\n", movimentazione);

		// Creazione riga dello storico
		csv_row *riga = csv_row_create(csv_storico);

		// Salvataggio della data del movimento
		char *data = get_date_string(); // Lettura della data in formato stringa
		csv_row_field_set(riga, "Data", data);

		// Salvataggio della descrizione per il movimento
		const char *testo_descrizione = movimentazione > 0 ? "Carico in magazzino" : "Scarico da magazzino";
		char *descrizione = malloc(sizeof(char) * (strlen(testo_descrizione) + 1));
		strcpy(descrizione, testo_descrizione); // Allocazione dinamica per permettere csv_row_free
		csv_row_field_set(riga, "Descrizione", descrizione);

		// Salvataggio del codice per il movimento
		char *codice_articolo = csv_row_field(articolo, "Codice");
		char *codice = malloc(sizeof(char) * (strlen(codice_articolo) + 1));
		strcpy(codice, codice_articolo); // Allocazione dinamica per permettere csv_row_free
		csv_row_field_set(riga, "Codice", codice);

		// Salvataggio della quantità della movimentazione
		csv_row_field_set(riga, "Quantità", movimentazione_inserita);

		// Inserimento del movimento in modalità APPEND
		char *riga_line = csv_row_to_line(riga);
		csv_write(csv_storico, -2, riga_line);
		free(riga_line);

		// Liberazione della memoria dinamica per la riga
		csv_row_free(riga); // Liberazione automatica di "movimentazione_inserita", "codice", "descrizione" e "data"

		// Aggiornamento della quantità dell'articolo nel magazzino
		char *nuova_quantita = malloc(50 * sizeof(char)); // Limite a 50 caratteri
		sprintf(nuova_quantita, "%f", quantita_attuale + movimentazione);
		char * previous = csv_row_field_set(articolo, "Quantità", nuova_quantita);
		free(previous);

		char *articolo_line = csv_row_to_line(articolo);
		csv_write(csv_magazzino, articolo->line_number, articolo_line);
		free(articolo_line);

		// Messaggio informativo
		COLOR_GREEN();
		printf("\nMovimentazione effettuata con successo!\n");
		TEXT_RESET();
	}
	// Operazioni nel caso di non movimentazione
	else
	{
		COLOR_GREEN();
		printf("\nNessuna movimentazione effettuata!\n");
		TEXT_RESET();
	}

	// Liberazione della memoria allocata per la riga
	csv_row_free(articolo); // Liberazione automatica di "nuova_quantita"
}