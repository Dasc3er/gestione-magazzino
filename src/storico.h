#ifndef STORICO_H_
#define STORICO_H_

#include "csv.h"

/**
 * Funzione per gestire la visualizzazione tabellare dello storico del magazzino.
 * 
 * @param csv_magazzino Puntatore allo struct per il magazzino CSV
 * @param csv_storico Puntatore allo struct per lo storico CSV
 */
void storico_totale(csv_file *csv_magazzino, csv_file *csv_storico);

/**
 * Funzione visualizzare lo storico a magazzino di un singolo articolo, individuato tramite il codice.
 * 
 * @param csv_magazzino Puntatore allo struct per il magazzino CSV
 * @param csv_storico Puntatore allo struct per lo storico CSV
 */
void storico_articolo(csv_file *csv_magazzino, csv_file *csv_storico);

/**
 * Funzione per movimentare un articolo esistente a magazzino, registrando la relativa movimentazione nello storico e modificando di conseguenza la quantità dell'articolo.
 * 
 * @param csv_magazzino Puntatore allo struct per il magazzino CSV
 * @param csv_storico Puntatore allo struct per lo storico CSV
 */
void movimenta_articolo(csv_file *csv_magazzino, csv_file *csv_storico);

#endif /* STORICO_H_ */
