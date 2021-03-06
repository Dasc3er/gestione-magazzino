/**
 * @file csv_file.h
 * @brief Header per la definizione delle funzionalità su file CSV.
 * 
 * Header che definisce tutte gli struct e le funzioni principali applicabili sui file CSV nel loro complessivo.
 */

#ifndef CSV_FILE_H_
#define CSV_FILE_H_

/**
 * Struct dedicato al salvataggio delle informazioni di base del file CSV.
 * Salva il percorso del file per le operazioni di lettura e scrittura, la struttura dell'header se presente e il numero di campi contenuti all'interno del file.
 * 
 * Per gestire la lettura separata delle singole righe, viene introdotto un contattore di byte che permette di lavorare in modo separato sulle righe.
 */
typedef struct
{
	char *filepath;		  /**< Percorso del file. */
	int field_counter;	  /**< Numero di campi per riga del file. */
	char field_separator; /**< Carattere dedicato alla separazione dei campi per le righe. */

	int has_header;	   /**< Flag per indicare la presenza o meno di un header. */
	char **header;	   /**< Contenuti dell'header separati per campo. */
	long header_bytes; /**< Numero di bytes dell'header. */

	long current_byte; /**< Byte corrente nella lettura in sequenza delle righe. */
	long line_counter; /**< Riga corrente nella lettura in sequenza delle righe. */
} csv_file;

/**
 * @brief Inizializza lo struct dedicato alla gestione del file CSV.
 *
 * Lo struct contiene le informazioni di base relative al file CSV, quali la posizione del file relativo nel filesystem e i dettagli dell'header (se presente).
 * 
 * @param filepath Percorso per il file CSV da leggere
 * @param has_header Flag per la lettura o meno della prima riga come header
 * 
 * @return Puntatore allo struct CSV inizializzato di conseguenza
 */
csv_file *csv_init(char *filepath, int has_header);

/**
 * @brief Funzione per la scrittura di un contenuto in una riga specifica del file CSV.
 * 
 * Il nuovo contenuto non deve contenere il carattere di invio a capo, che viene inserito automaticamente in base al numero di riga indicato.
 * Se il numero di riga inserito è eccessivamente elevato oppure non presente nel file originale, il contenuto verrà inserito in modalità APPEND. Il numero di riga "-1" assume il significato di inserimento in modalità PREPEND.
 * 
 * @warning Attenzione: l'utilizzo di questa funzione può rendere non valido il contatore line_number delle righe del file CSV presenti in memoria.
 * 
 * @param csv Puntatore al file CSV
 * @param line_number Numero di riga su cui effettuare la scrittura
 * @param content Contenuto da inserire nella riga indicata
 */
void csv_write(csv_file *file, int line_number, char *content);

/**
 * @brief Libera la memoria allocata dinamicamente dello struct CSV.
 * @warning Attenzione: la funzione si aspetta uno struct instanziato tramite allocazione dinamica della memoria, e procede di conseguenza alla liberazione dello struct stesso e di tutti i contenuti relativi.
 * 
 * @param file Puntatore al file CSV
 */
void csv_free(csv_file *file);

/**
 * @brief Resetta i contatori del file CSV alla prima riga disponibile.
 * 
 * @param file Puntatore al file CSV
 */
void csv_reset(csv_file *file);

/**
 * @brief Restituisce un puntatore alla stringa contenente il nome del campo indicato tramite indice.
 * 
 * @param file Puntatore al file CSV
 * @param index Indice del campo richiesto
 * 
 * @return Puntatore al contenuto del campo se esiste, altrimenti a NULL
 */
char *csv_header_field(csv_file *file, int index);

/**
 * @brief Restituisce l'indice del campo che corrisponde alla stringa indicata.
 * 
 * @param file Puntatore al file CSV
 * @param field Puntatore alla stringa da ricercare nell'header
 * 
 * @return Indice del campo se esiste, altrimenti -1
 */
int csv_header_field_index(csv_file *file, char *field);

#endif /* CSV_FILE_H_ */
