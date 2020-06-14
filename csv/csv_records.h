/**
 * @file csv_records.h
 * @brief Header per la definizione delle funzionalità di lettura sequenziale da un file CSV.
 * 
 * Header che definisce tutte gli struct e le funzioni principali dedicate alla lettura di più righe in sequenza a partire da uno stesso file CSV.
 */

#ifndef CSV_RECORDS_H_
#define CSV_RECORDS_H_

#include <stdarg.h>
#include "csv_file.h"
#include "csv_row.h"

/**
 * Struct per aggregare una sequenza di righe.
 */
typedef struct
{
	long length;	   /**< Numero di elementi nell'elenco. */
	csv_row **results; /**< Puntatori alle righe. */
} csv_records;

/**
 * @brief Funzione dedicata alla lettura in sequenza di tutte le righe di un file CSV.
 * 
 * Le righe del file vengono salvate in memoria come csv_row e raggruppate all'interno di uno struct csv_records per facilitarne l'utilizzo.
 * 
 * @param file Puntatore allo struct del file CSV da leggere
 * 
 * @return Puntatore allo struct contenete le righe del file.
 */
csv_records *csv_read(csv_file *file);

/**
 * @brief Libera la memoria allocata dinamicamente dello struct csv_record per i record CSV.
 * @warning Attenzione: la funzione si aspetta uno struct instanziato tramite allocazione dinamica della memoria, e procede di conseguenza alla liberazione dello struct stesso e di tutti i contenuti relativi.
 * 
 * @param records Puntatore allo struct da liberare
 */
void csv_records_free(csv_records *records);

/**
 * Struct per indicare i filtri da applicare nella lettura delle righe (per sviluppi futuri).
 * 
 * @todo Esempio di una possibile struttura per l'applicazione di filtri alla lettura dal file
 */
typedef struct
{
	char *field;
	int field_number;

	char *content;
} csv_filter;

#endif /* CSV_RECORDS_H_ */
