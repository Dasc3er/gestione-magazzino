/**
 * @file storico.h
 * @brief Header per la definizione delle funzioni dedicate alla gestione dello storico del programma.
 */

#ifndef STORICO_H_
#define STORICO_H_

#include "csv.h"

/**
 * @brief Funzione per gestire la visualizzazione tabellare dello storico del magazzino.
 * 
 * @param csv_magazzino Puntatore allo struct per il magazzino CSV
 * @param csv_storico Puntatore allo struct per lo storico CSV
 */
void storico_totale(csv_file *csv_magazzino, csv_file *csv_storico);

/**
 * @brief Funzione per visualizzare lo storico a magazzino di un singolo articolo, individuato tramite il codice.
 * 
 * @param csv_magazzino Puntatore allo struct per il magazzino CSV
 * @param csv_storico Puntatore allo struct per lo storico CSV
 */
void storico_articolo(csv_file *csv_magazzino, csv_file *csv_storico);

/**
 * @brief Funzione per movimentare un articolo esistente a magazzino.
 * 
 * La movimentazione di un articolo prevede la registrazione della relativa variazione di quantità nello storico e la modifica (di conseguenza) della quantità dell'articolo.
 * 
 * @param csv_magazzino Puntatore allo struct per il magazzino CSV
 * @param csv_storico Puntatore allo struct per lo storico CSV
 */
void movimenta_articolo(csv_file *csv_magazzino, csv_file *csv_storico);

#endif /* STORICO_H_ */
