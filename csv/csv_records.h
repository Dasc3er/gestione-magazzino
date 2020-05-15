#ifndef CSV_RECORDS_H_
#define CSV_RECORDS_H_

#include <stdarg.h>
#include "csv_file.h"
#include "csv_row.h"

/**
 * Struct per aggregare una sequenza di righe.
 */
typedef struct {
	int length; /**< Numero di elementi nell'elenco. */  
	csv_row **results; /**< Puntatori alle righe. */  
} csv_records;

/**
 * Funzione dedicata alla lettura di una serie di righe in memoria.
 */
csv_records* csv_read(csv_file *file);

/**
 * Libera la memoria dinamica utilizzata per lo struct dei record CSV.
 * 
 * @param records Puntatore allo struct da liberare
 */
void csv_records_free(csv_records *records);

/**
 * Struct per indicare i filtri da applicare nella lettura delle righe.
 */
typedef struct {
	char *field;
	int field_number;

	char *content;
} csv_filter;

#endif /* CSV_RECORDS_H_ */
