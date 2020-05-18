#ifndef STORICO_H_
#define STORICO_H_

#include "csv.h"

void storico_totale(csv_file *csv_magazzino, csv_file *csv_storico);

void storico_articolo(csv_file *csv_magazzino, csv_file *csv_storico);

void movimenta_articolo(csv_file *csv_magazzino, csv_file *csv_storico);

#endif /* STORICO_H_ */
