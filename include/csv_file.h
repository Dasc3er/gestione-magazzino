#ifndef CSV_FILE_H_
#define CSV_FILE_H_

/**
 * Struct dedicato al salvataggio delle informazioni di base del file CSV.
 * Viene salvato il percorso del file per le operazioni di lettura e scrittura, la struttura dell'header se presente e il numero di campi presente all'interno.
 * Per gestire la lettura separata delle singole righe, viene introdotto un contattore di byte che permette di lavorare in modo separato sulle righe.
 *
 * @param filepath Percorso del file
 * @param field_counter Numero di campi per riga del file
 *
 * @param has_header Flag per indicare la presenza o meno di un header
 * @param header Contenuti dell'header separati per campo
 * @param header_bytes Numero di bytes dell'header
 *
 * @param current_byte Byte corrente nella lettura in sequenza delle righe
 * @param line_counter Riga corrente nella lettura in sequenza delle righe
 */
typedef struct {
	char *filepath;
	int field_counter;

	int has_header;
	char **header;
	long header_bytes;

	long current_byte;
	long line_counter;
} csv_file;

/**
 * Inizializza lo struct dedicato alla gestione del file CSV.
 *
 * Lo struct contiene le informazioni di base relative al file CSV, quali la posizione del file relativo nel filesystem e i dettagli dell'header se presente.
 *
 * @param filename
 * @param has_header
 */
csv_file* csv_init(char *filename, int has_header);

/**
 * Funzione per la scrittura di un contenuto in una riga specifica del file CSV.
 * 
 * Attenzione: l'utilizzo di questa funzione può rendere invalido il contatore line_number delle righe del CSV salvate in memoria.
 */
void csv_write(csv_file *file, int line_number, char *content);

/**
 * Libera la memoria dinamica utilizzata per lo struct CSV.
 */
void csv_free(csv_file *csv);

#endif /* CSV_FILE_H_ */
