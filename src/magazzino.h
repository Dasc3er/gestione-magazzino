#ifndef MAGAZZINO_H_
#define MAGAZZINO_H_

#include "csv.h"

void visualizza_magazzino(csv_file *csv_magazzino, csv_file *csv_storico);

csv_row *cerca_articolo(csv_file *csv_magazzino, char *codice_articolo);

void inserisci_articolo(csv_file *csv_magazzino, csv_file *csv_storico);

void modifica_articolo(csv_file *csv_magazzino, csv_file *csv_storico);

void rimuovi_articolo(csv_file *csv_magazzino, csv_file *csv_storico);
#endif /* MAGAZZINO_H_ */
