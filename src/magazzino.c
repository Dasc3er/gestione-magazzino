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

void articoli_esaurimento(csv_file *csv_magazzino, csv_file *csv_storico)
{
	int index_qta = csv_header_field_index(csv_magazzino, "Quantità");
	int index_qta_minima = csv_header_field_index(csv_magazzino, "Quantità minima");
	if (index_qta == -1 || index_qta_minima == -1)
	{
		printf("Impossibile individuare gli articoli in esaurimento a causa della mancanza dei campi Quantità e/o Quantià minima");

		return;
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

void ricerca_articolo(csv_file *csv_magazzino, csv_file *csv_storico)
{
	csv_row * row = cerca_articolo(csv_magazzino);
	free(row);
}

void inserisci_articolo(csv_file *csv_magazzino, csv_file *csv_storico)
{
	// Creazione riga CSV relativa all'articolo
	csv_row *articolo = csv_row_create(csv_magazzino);
	
	// Messaggio introduttivo
	printf("Inserisci di seguito i dati da associare al nuovo articolo.\n");
	printf("Attenzione: la registrazione di un articolo non prevede la relativa movimentazione della quantità iniziale!\n");

	// Inserimento automatico dei contenuti
	inserisci_dati(articolo);

	// Salvataggio
	char * line = csv_row_to_line(articolo);
	csv_write(csv_magazzino, articolo->line_number, line);
	free(line);

	// Messaggio finale
	COLOR_GREEN();
	printf("Articolo registrato con successo!");
	TEXT_RESET();
}

void modifica_articolo(csv_file *csv_magazzino, csv_file *csv_storico)
{
	// Ricerca articolo
	csv_row *articolo = cerca_articolo(csv_magazzino);
	if (articolo == NULL)
	{
		return;
	}

	// Messaggio introduttivo
	printf("Inserisci di seguito i nuovi dati da associare all'articolo individuato.\n");
	printf("Attenzione: le modifiche alle quantità effettuate tramite questa operazione non verranno registrate come movimenti!\n");

	// Inserimento automatico dei contenuti
	inserisci_dati(articolo);

	// Salvataggio
	char * line = csv_row_to_line(articolo);
	csv_write(csv_magazzino, articolo->line_number, line);
	free(line);

	// Messaggio finale
	COLOR_GREEN();
	printf("Articolo modificato con successo!");
	TEXT_RESET();
}

void rimuovi_articolo(csv_file *csv_magazzino, csv_file *csv_storico)
{
	// Ricerca articolo
	csv_row *row = cerca_articolo(csv_magazzino);
	if (row == NULL)
	{
		return; 
	}

	// Rimozione articolo
	csv_write(row->csv, row->line_number, "");
	csv_row_free(row);

	// Messaggio finake
	COLOR_GREEN();
	printf("Articolo rimosso!");
	TEXT_RESET();
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
		TEXT_BOLD();
		printf("\nArticolo individuato!\n");
		TEXT_RESET();
		printf("Codice: %s\n", csv_row_field(row, "Codice"));
		printf("Descrizione: %s\n", csv_row_field(row, "Descrizione"));
		printf("Quantità: %s\n", csv_row_field(row, "Quantità"));
	}
	else
	{
		printf("Impossibile trovare un articolo con il codice indicato\n");
	}

	return row;
}

void inserisci_dati(csv_row *row)
{
	char *string_fields[] = {
		"Codice",
		"Descrizione",
	};
	int string_length = sizeof(string_fields) / sizeof(string_fields[0]);

	// Operazioni di input per i campi di tipo stringa
	for (int i = 0; i < string_length; i++)
	{
		char *content = inserisci_campo(row, string_fields[i]);

		// Salvataggio del nuovo valore
		if (content != NULL)
		{
			csv_row_field_set(row, string_fields[i], content);
		}
	}

	char *float_fields[] = {
		"Quantità",
		"Quantità minima",
	};
	int float_length = sizeof(float_fields) / sizeof(float_fields[0]);

	// Operazioni di input per i campi di tipo stringa
	for (int i = 0; i < float_length; i++)
	{
		char *content = inserisci_campo(row, float_fields[i]);

		// Salvataggio del nuovo valore
		if (content != NULL)
		{
			float valore = atof(content);
			printf("Contento individuato: %f\n", valore);

			char *conversione = malloc(50 * sizeof(char)); // Limite a 50 caratteri
			sprintf(conversione, "%f", valore);

			csv_row_field_set(row, float_fields[i], conversione);
		}
	}
}

char *inserisci_campo(csv_row *row, char *field)
{
	// Richiesta del campo all'utente
	TEXT_BOLD();
	printf("\n%s\n", field);
	TEXT_RESET();

	// Visualizzazione del valore precedente
	char *valore_attuale = csv_row_field(row, field);
	if (valore_attuale != NULL)
	{
		printf("Valore attuale: %s\n", valore_attuale);
		printf("Nuovo valore [vuoto per mantente il contenuto corrente]: ");
	} else {
		printf("Valore: ");
	}

	// Richiesta del nuovo valore
	char *content = read_line();

	// Restituzione del nuovo valore
	if (strlen(content) == 0)
	{
		return NULL;
	}

	// Liberazione della memoria per il valore precedente
	free(valore_attuale);

	return content;
}
