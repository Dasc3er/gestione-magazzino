#ifndef MAGAZZINO_H_
#define MAGAZZINO_H_

#include "csv.h"

void visualizza_magazzino(csv_file *csv_magazzino, csv_file *csv_storico);

void articoli_esaurimento(csv_file *csv_magazzino, csv_file *csv_storico);

csv_row *cerca_articolo(csv_file *csv_magazzino);

void inserisci_articolo(csv_file *csv_magazzino, csv_file *csv_storico);

void modifica_articolo(csv_file *csv_magazzino, csv_file *csv_storico);

void rimuovi_articolo(csv_file *csv_magazzino, csv_file *csv_storico);

void inserisci_dati(csv_row *row);

char *inserisci_campo(csv_row *row, char *field);
#endif /* MAGAZZINO_H_ */
