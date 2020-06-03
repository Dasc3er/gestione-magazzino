#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "csv.h"
#include "utils.h"
#include "magazzino.h"
#include "storico.h"

/**
 * Funzione per la visualizzazione del menu principale del programma.
 * 
 * @param options Puntatore alle descrizioni delle opzioni
 * @param length Lunghezza dell'array options
 */
void menu(char *options[], int length);

/**
 * Funzione per l'inizializzazione dei file CSV.
 * 
 * @param path Percorso attuale
 * @param csv_magazzino Puntatore al puntatore per lo struct CSV di magazzino
 * @param csv_storico Puntatore al puntatore per lo struct CSV di storico
 */
void init(char *path, csv_file **csv_magazzino, csv_file **csv_storico);

/**
 * Funzione per l'uscita dal programma e la chiusura delle principali risorse in utilizzo.
 * 
 * @param csv_magazzino Puntatore allo struct CSV di magazzino
 * @param csv_storico Puntatore allo struct CSV di storico
 */
void esci(csv_file *csv_magazzino, csv_file *csv_storico);

int main()
{
	system("clear");

	// Individuazione percorso corrente
	char *path = get_cwd();
	if (path == NULL)
	{
		COLOR_RED();
		printf("Impossibile individuare il percorso corrente\n");
		TEXT_RESET();
		exit(EXIT_FAILURE);
	}

	// Inizializzazione dei file CSV
	csv_file *csv_magazzino, *csv_storico;
	init(path, &csv_magazzino, &csv_storico);

	// Inizializzazione opzioni del programma
	char *options[] = {
		"Esci",
		"Visualizza il magazzino",
		"Visualizza articoli a rischio esaurimento e/o esauriti",
		"Ricerca un articolo tramite codice",
		"Visualizza lo storico dei movimenti totale",
		"Visualizza lo storico dei movimenti per un articolo",
		"Movimenta un articolo del magazzino",
		"Registra un nuovo articolo nel magazzino",
		"Modifica un articolo esistente del magazzino",
		"Rimuovi un articolo dal magazzino",
	};
	int length = sizeof(options) / sizeof(options[0]);

	void (*functions[])(csv_file *, csv_file *) = {
		esci,
		visualizza_magazzino,
		articoli_esaurimento,
		ricerca_articolo,
		storico_totale,
		storico_articolo,
		movimenta_articolo,
		inserisci_articolo,
		modifica_articolo,
		rimuovi_articolo,
	};

	// Messaggio di benvenuto
	COLOR_GREEN();
	printf("Benvenuto nel sistema di gestione magazzino!\n");
	printf("Il programma è indirizzato a fornitore alcune funzionalità di base sulla gestione di un magazzino aziendale, con particolare interesse in relazione allo storico dei movimenti dei diversi articoli registrati.\n\n");
	printf("Percorso corrente: %s\n\n", path);
	TEXT_RESET();

	menu(options, length);

	while (1)
	{
		int selection = -1;
		printf("Opzione scelta: ");
		scanf("%d", &selection);

		// Cleanup del buffer
		int c;
		while ((c = getchar()) != '\n' && c != EOF)
			;

		if (selection >= 0 && selection < length)
		{
			TEXT_BOLD();
			printf("\nOpzione individuata: %s\n", options[selection]);
			TEXT_RESET();
			
			functions[selection](csv_magazzino, csv_storico);
			printf("\n\n");

			menu(options, length);
		}
		else
		{
			COLOR_RED();
			printf("\nAttenzione: sono accettate solo le opzioni sopra indicate\n");
			TEXT_RESET();
		}
	}
}

void menu(char *options[], int length)
{
	printf("Inserisci il numero di una delle seguenti opzioni per utilizzare le funzionalità del sistema:\n");

	for (int i = 0; i < length; i++)
	{
		printf(" %d. %s\n", i, options[i]);
	}
}

void init(char *path, csv_file **csv_magazzino, csv_file **csv_storico)
{
	// Individuazione percorso dei file CSV
	char *directory_name = "data";
	char *magazzino_filename = "magazzino.csv";
	char *storico_filename = "storico.csv";

	int directory_length = strlen(path) + strlen(directory_name) + 2;
	int char_size = sizeof(char);

	char *directory = malloc(char_size * directory_length);
	char *magazzino = malloc(char_size * (directory_length + strlen(magazzino_filename) + 1));
	char *storico = malloc(char_size * (directory_length + strlen(storico_filename) + 1));
	if (magazzino == NULL || storico == NULL)
	{
		fprintf(stderr, "Errore di allocazione dinamica\n");
		exit(EXIT_FAILURE);
	}
	sprintf(directory, "%s/%s", path, directory_name);
	sprintf(magazzino, "%s/%s", directory, magazzino_filename);
	sprintf(storico, "%s/%s", directory, storico_filename);

	// Creazione della cartella per i dati
	struct stat st = {0};
	if (stat(directory, &st) == -1)
	{
		mkdir(directory, 0777);
	}

	// Creazione dei file se non esistono
	if (access(magazzino, F_OK) == -1)
	{
		FILE *pointer = fopen(magazzino, "w");
		fputs("Codice,Descrizione,Quantità,Quantità minima", pointer);
		fclose(pointer);
	}

	if (access(storico, F_OK) == -1)
	{
		FILE *pointer = fopen(storico, "w");
		fputs("Data,Codice,Descrizione,Quantità", pointer);
		fclose(pointer);
	}

	// Inizializzazione dei file CSV
	*csv_magazzino = csv_init(magazzino, 1);
	*csv_storico = csv_init(storico, 1);
}

void esci(csv_file *csv_magazzino, csv_file *csv_storico)
{
	COLOR_GREEN();
	printf("Grazie per aver utilizzato questo programma!\n");
	TEXT_RESET();

	// Liberazione della memoria allocata per i file CSV
	csv_free(csv_magazzino);
	csv_free(csv_storico);

	exit(EXIT_SUCCESS);
}
