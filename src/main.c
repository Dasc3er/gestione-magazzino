#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "csv.h"

// Colori per l'output
#define COLOR_RED() printf("\033[1;31m");
#define COLOR_GREEN() printf("\033[0;32m");
#define COLOR_RESET() printf("\033[0m");

void menu(char *options[], int length);
void init(char *path, csv_file **csv_magazzino, csv_file **csv_storico);
char *get_cwd();
char *read_line();
void input_cleanup();

int esci(csv_file *csv_magazzino, csv_file *csv_storico);
int visualizza_magazzino(csv_file *csv_magazzino, csv_file *csv_storico);
int storico_totale(csv_file *csv_magazzino, csv_file *csv_storico);
int storico_articolo(csv_file *csv_magazzino, csv_file *csv_storico);

int main()
{
	system("clear");

	// Individuazione percorso corrente
	char *path = get_cwd();
	if (path == NULL)
	{
		COLOR_RED();
		printf("Impossibile individuare il percorso corrente\n");
		COLOR_RESET();
		exit(EXIT_FAILURE);
	}

	// Inizializzazione dei file CSV
	csv_file *csv_magazzino, *csv_storico;
	init(path, &csv_magazzino, &csv_storico);

	// Inizializzazione opzioni del programma
	char *options[] = {
		"Esci",
		"Visualizza il magazzino",
		"Visualizza lo storico dei movimenti totale",
		"Visualizza lo storico dei movimenti per un articolo",
		"Inserisci un nuovo articolo nel magazzino",
		"Modifica un articolo del magazzino",
		"Movimenta un articolo del magazzino",
		"Rimuovi un articolo dal magazzino",
	};
	int length = sizeof(options) / sizeof(options[0]);

	int (*functions[])(csv_file *, csv_file *) = {
		esci,
		visualizza_magazzino,
		storico_totale,
		storico_articolo,
	};

	// Messaggio di benvenuto
	COLOR_GREEN();
	printf("Benvenuto nel programma di gestione magazzino!\n");
	printf("Percorso corrente: %s\n\n", path);
	COLOR_RESET();

	menu(options, length);

	while (1)
	{
		int selection = -1;
		printf("Opzione selezionata: ");
		scanf("%d", &selection);
		input_cleanup();

		if (selection >= 0 && selection < length)
		{
			printf("\n\n");
			functions[selection](csv_magazzino, csv_storico);
			printf("\n\n");

			menu(options, length);
		}
		else
		{
			COLOR_RED();
			printf("\nAttenzione: sono accettate solo le opzioni sopra indicate\n");
			COLOR_RESET();
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
	char *magazzino = malloc(char_size * (directory_length + strlen(magazzino_filename) + 2));
	char *storico = malloc(char_size * (directory_length + strlen(magazzino_filename) + 2));
	if (magazzino == NULL || storico == NULL)
	{
		COLOR_RED();
		printf("Errore di allocazione dinamica\n");
		COLOR_RESET();
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
		fputs("Codice;Descrizione;Quantità", pointer);
		fclose(pointer);

		pointer = fopen(storico, "w");
		fputs("Data;Codice;Quantità", pointer);
		fclose(pointer);
	}

	// Inizializzazione dei file CSV
	*csv_magazzino = csv_init(magazzino, 1);
	*csv_storico = csv_init(storico, 1);
}

int esci(csv_file *csv_magazzino, csv_file *csv_storico)
{
	COLOR_GREEN();
	printf("Grazie per aver utilizzato questo programma!\n");
	COLOR_RESET();

	csv_free(csv_magazzino);
	csv_free(csv_storico);

	exit(EXIT_SUCCESS);
}

char *get_cwd()
{
	char *cwd;
	char buff[PATH_MAX + 1];

	cwd = getcwd(buff, PATH_MAX + 1);
	return cwd;
}

int visualizza_magazzino(csv_file *csv_magazzino, csv_file *csv_storico)
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

int storico_totale(csv_file *csv_magazzino, csv_file *csv_storico)
{
	csv_records *records = csv_read(csv_storico);

	// Visualizzazione grafica
	printf("======================================================================\n");
	printf(" %-10s | %-40s | %-10s \n", "Data", "Codice", "Quantità");
	printf("======================================================================\n");

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

int storico_articolo(csv_file *csv_magazzino, csv_file *csv_storico)
{
	char *codice_articolo;
	int i = 0;
	while (i == 0)
	{
		printf("Codice dell'articolo da filtrare: ");
		codice_articolo = read_line();
		i = strlen(codice_articolo);
	}

	csv_records *records = csv_read(csv_storico);

	// Visualizzazione grafica
	printf("======================================================================\n");
	printf(" %-10s | %-40s | %-10s \n", "Data", "Codice", "Quantità");
	printf("======================================================================\n");

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
}

char *read_line()
{
	// Inizializzazione della stringa
	int length = 100;
	int size = sizeof(char);
	char *result = malloc(size * length);

	int i = 0;
	int end = 0;
	while (!end)
	{
		// Allargamento dinamico dello spazio
		if (i >= length)
		{
			length = length * 2;
			result = realloc(result, size * length);
			check_allocation(result);
		}

		// Controllo sui caratteri
		char c = getchar();
		end = (c == '\n' || c == EOF);

		// Salvataggio del carattere corrente
		*(result + i) = end ? '\0' : c;
		i++;
	}

	// Restrizione dello spazio
	length = i;
	result = realloc(result, size * length);
	check_allocation(result);

	return result;
}

void input_cleanup()
{
	// Cleanup del buffer
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}
