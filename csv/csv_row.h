/**
 * @file csv_row.h
 * @brief Header per la definizione delle funzionalità di gestione delle righe di un file CSV.
 * 
 * Header che definisce tutte gli struct e le funzioni principali dedicate alla lettura, scrittura e navigazione delle singole righe di un file CSV.
 */

#ifndef CSV_ROW_H_
#define CSV_ROW_H_

#include "csv_file.h"
#include <stdio.h>

/**
 * Struct per la rappresentazione delle informazioni di una riga.
 */
typedef struct
{
	csv_file *csv;	   /**< Puntatore al file CSV di roginie. */
	int field_counter; /**< Numero di campi della riga (per facilitare la navigazione). */

	long line_number; /**< Numero della riga (a partire da 0). */
	long bytes;		  /**< Numero di byte occupati dalla riga. */
	char **contents;  /**< Puntatori ai campi contenuti dalla riga. */
} csv_row;

/**
 * @brief Legge una nuova riga dal file CSV indicato tramite uno struct csv_row.
 * 
 * L'ordine di lettura viene definito dal contenuto dei campi *current_byte* e *line_counter* del file CSV, che permettono di individuare la riga successiva da leggere per il file.
 * 
 * @param csv Puntatore al file CSV 
 * 
 * @return Puntatore allo struct riga creato, oppure a NULL se la riga è vuota.
 */
csv_row *csv_read_line(csv_file *csv);

/**
 * @brief Restituisce il contenuto del campo (idetificato tramite nome relativo) all'interno di una riga CSV.
 * 
 * Il nome del campo viene utilizzato per l'individuazione dell'indice relativo a partire dall'header del file CSV.
 * 
 * @param row Puntatore alla riga 
 * @param name Puntatore al nome del campo richiesto
 * 
 * @return Puntatore al contenuto del campo per la riga indicata, oppure a NULL se il campo non è presente.
 */
char *csv_row_field(csv_row *row, char *name);

/**
 * @brief Restituisce il contenuto del campo (idetificato tramite indice relativo) all'interno di una riga CSV.
 * 
 * @param row Puntatore alla riga 
 * @param index Posizione del campo richiesto
 * 
 * @return Puntatore al contenuto del campo per la riga indicata, oppure a NULL se il campo non è presente.
 */
char *csv_row_field_by_index(csv_row *row, int index);

/**
 * @brief Imposta il contenuto del campo (idetificato tramite nome relativo) all'interno di una riga CSV.
 * 
 * Il nome del campo viene utilizzato per l'individuazione dell'indice relativo a partire dall'header del file CSV.
 * @warning Attenzione: la memoria allocata per il contenuto precedente non viene liberata in automatico, e il nuovo contenuto deve essere stato creato tramite allocazione dinamica della memoria per permettere la corretta liberazione delle risorse.
 * 
 * @param row Puntatore alla riga 
 * @param name Puntatore al nome del campo richiesto
 * @param content Putantotre al nuovo contenuto
 * 
 * @return Puntatore al contenuto precedente del campo per la riga indicata, oppure a NULL se il campo non è presente.
 */
char *csv_row_field_set(csv_row *row, char *name, char *content);

/**
 * @brief Libera la memoria allocata dinamicamente dello struct della riga CSV.
 * @warning Attenzione: la funzione si aspetta uno struct instanziato tramite allocazione dinamica della memoria, e procede di conseguenza alla liberazione dello struct stesso.
 * 
 * @param row Puntatore alla riga
 */
void csv_row_free(csv_row *row);

/**
 * @brief Funzione dedicata a lettura e interpretazione della riga successiva di un file CSV in un relativo struct csv_row indicato.
 * 
 * Se il file viene aperto con successo, la procedura salva l'intera linea di testo in memoria separando dinamicamente i campi sulla base del carattere ";".
 * 
 * @warning Attenzione: la procedura di interpretazione non supporta perfettamente il formato CSV, in particolare in relazione alla procedura di *escaping* tramite virgolette.
 * 
 * @param row Puntatore alla riga 
 * @param fp Puntatore al file da cui leggere la riga
 * 
 * @return 0 nel caso in cui la lettura sia stata completata con successo, 1 altrimenti.
 */
int csv_row_wrap(csv_row *row, FILE *fp);

/**
 * @brief Funzione per la conversione della riga in una stringa di formato CSV.
 * In riferimento alla modalità di lettura e scrittura, questa funzione restituisce il carattere di invio a capo in automatico alla fine del contenuto.
 * 
 * @param row Puntatore alla riga da convertire
 * 
 * @return Puntatore alla stringa in formato CSV
 */
char *csv_row_to_line(csv_row *row);

/**
 * @brief Inizializza uno struct di riga vuota per il file CSV indicato.
 * 
 * I contenuti dei diversi campi sono impostati automaticamente a NULL.
 * 
 * @param file Puntatore al file CSV per cui creare la riga
 * 
 * @return Puntatore allo struct creato
 */
csv_row *csv_row_create(csv_file *file);

#endif /* CSV_ROW_H_ */
