#ifndef CSV_ROW_H_
#define CSV_ROW_H_

#include "csv_file.h"
#include <stdio.h>

/**
 * Struct per la rappresentazione delle informazioni di una riga.
 */
typedef struct {
	csv_file *csv;/**< Puntatore al file CSV di roginie. */  
	int field_counter; /**< Numero di campi della riga (per facilitare la navigazione). */  

	long line_number; /**< Numero della riga (a partire da 0). */  
	long bytes; /**< Numero di byte occupati dalla riga. */  
	char **contents; /**< Puntatori ai campi contenuti dalla riga. */  
} csv_row;

/**
 * Legge e instanzia una nuova riga dal file CSV indicato, seguendo l'ordine indicato dal campo *line_counter* del file.
 * 
 * @param csv Puntatore al file CSV 
 * 
 * @return Puntatore allo struct riga creato, oppure a NULL se la riga è vuota.
 */
csv_row* csv_read_line(csv_file *csv);

/**
 * Restituisce il contenuto del campo (idetificato tramite nome relativo) all'interno di una riga CSV.
 * 
 * Il nome del campo viene utilizzato per l'individuazione dell'indice relativo a partire dall'header del file CSV.
 * 
 * @param row Puntatore alla riga 
 * @param name Nome del campo richiesto
 * 
 * @return Puntatore al contenuto del campo per la riga indicata, oppure a NULL se il campo non è presente.
 */
char* csv_row_field(csv_row *row, char *name);

/**
 * Restituisce il contenuto del campo (idetificato tramite indice relativo) all'interno di una riga CSV.
 * 
 * @param row Puntatore alla riga 
 * @param index Posizione del campo richiesto
 * 
 * @return Puntatore al contenuto del campo per la riga indicata, oppure a NULL se il campo non è presente.
 */
char* csv_row_field_by_index(csv_row *row, int index);

/**
 * Libera la memoria dinamica utilizzata per lo struct della riga CSV.
 * Attenzione: la funzione si aspetta uno struct instanziato tramite allocazione dinamica della memoria, e procede di conseguenza alla liberazione dello struct stesso.
 * 
 * @param row Puntatore alla riga
 */
void csv_row_free(csv_row *row);

/**
 * Funzione che legge la riga successiva di un file CSV e ne  interpreta il formato CSV, compilando di conseguenza lo struct dedicato alla riga.
 * 
 * Se il file viene aperto con successo, la procedura salva l'intera linea di testo in memoria separando dinamicamente i campi sulla base del carattere ";".
 * 
 * @param row Puntatore alla riga 
 * @param fp Puntatore al file da cui leggere la riga
 * 
 * @return 0 nel caso in cui la lettura sia stata completata con successo, 1 altrimenti.
 */
int csv_row_wrap(csv_row *row, FILE *fp);

/**
 * Funzione per la conversione della riga in una stringa di formato CSV.
 * In riferimento alla modalità di lettura e scrittura, questa funzione restituisce il carattere di invio a capo in automatico alla fine del contenuto.
 * 
 * @param row Puntatore alla riga da convertire
 * 
 * @return Puntatore alla stringa in formato CSV
 */
char * csv_row_to_line(csv_row *row);

#endif /* CSV_ROW_H_ */
