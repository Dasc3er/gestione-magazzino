#ifndef CSV_FILE_H_
#define CSV_FILE_H_

/**
 * Struct dedicato al salvataggio delle informazioni di base del file CSV.
 * Salva il percorso del file per le operazioni di lettura e scrittura, la struttura dell'header se presente e il numero di campi contenuti all'interno del file.
 * 
 * Per gestire la lettura separata delle singole righe, viene introdotto un contattore di byte che permette di lavorare in modo separato sulle righe.
 */
typedef struct {
	char *filepath; /**< Percorso del file. */  
	int field_counter; /**< Numero di campi per riga del file. */  

	int has_header; /**< Flag per indicare la presenza o meno di un header. */  
	char **header; /**< Contenuti dell'header separati per campo. */  
	long header_bytes; /**< Numero di bytes dell'header. */  

	long current_byte; /**< Byte corrente nella lettura in sequenza delle righe. */  
	long line_counter; /**< Riga corrente nella lettura in sequenza delle righe. */  
} csv_file;

/**
 * Inizializza lo struct dedicato alla gestione del file CSV.
 *
 * Lo struct contiene le informazioni di base relative al file CSV, quali la posizione del file relativo nel filesystem e i dettagli dell'header se presente.
 *
 * @param filename Percorso per il file CSV da leggere
 * @param has_header Flag per la lettura o meno della prima riga come header
 */
csv_file* csv_init(char *filename, int has_header);

/**
 * Funzione per la scrittura di un contenuto in una riga specifica del file CSV.
 * 
 * Attenzione: l'utilizzo di questa funzione può rendere invalido il contatore line_number delle righe del CSV salvate in memoria.
 * 
 * @param csv Puntatore al file CSV
 * @param line_number Numero di riga su cui effettuare la scrittura
 * @param content Contenuto da inserire nella riga indicata, deve contenere il carattere di invio a capo
 */
void csv_write(csv_file *file, int line_number, char *content);

/**
 * Libera la memoria dinamica utilizzata per lo struct CSV.
 * 
 * @param file Puntatore al file CSV
 */
void csv_free(csv_file *file);

#endif /* CSV_FILE_H_ */