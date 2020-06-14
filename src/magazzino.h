/**
 * @file magazzino.h
 * @brief Header per la definizione delle funzioni dedicate alla gestione del magazzino del programma.
 */

#ifndef MAGAZZINO_H_
#define MAGAZZINO_H_

#include "csv.h"

/**
 * @brief Funzione per gestire la visualizzazione tabellare del magazzino.
 * 
 * @param csv_magazzino Puntatore allo struct per il magazzino CSV
 * @param csv_storico Puntatore allo struct per lo storico CSV
 */
void visualizza_magazzino(csv_file *csv_magazzino, csv_file *csv_storico);

/**
 * @brief  Funzione per visualizzare l'elenco di articoli in esaurimento nel magazzino, ovvero il cui campo "Quantità" è minore o uguale al campo "Quantità minima".
 * 
 * Ciò permette di inviduare gli articoli per cui è necessario effettuare un ordine al fornitore per avere un numero adeguato di elementi in scorta a magazzino.
 * 
 * @param csv_magazzino Puntatore allo struct per il magazzino CSV
 * @param csv_storico Puntatore allo struct per lo storico CSV
 */
void articoli_esaurimento(csv_file *csv_magazzino, csv_file *csv_storico);

/**
 * @brief Funzione per gestire la ricerca di un articolo a magazzino sulla base del codice.
 * 
 * @param csv_magazzino Puntatore allo struct per il magazzino CSV
 * @param csv_storico Puntatore allo struct per lo storico CSV
 */
void ricerca_articolo(csv_file *csv_magazzino, csv_file *csv_storico);

/**
 * @brief Funzione per gestire l'inserimento di un nuovo articolo nel magazzino.
 * 
 * @param csv_magazzino Puntatore allo struct per il magazzino CSV
 * @param csv_storico Puntatore allo struct per lo storico CSV
 */
void inserisci_articolo(csv_file *csv_magazzino, csv_file *csv_storico);

/**
 * @brief Funzione per gestire la modifica di un articolo esistente nel magazzino.
 * @warning Attenzione: modificare la quantità di un articolo attraverso questa operazione non modifica lo storico del magazzino.
 * 
 * @param csv_magazzino Puntatore allo struct per il magazzino CSV
 * @param csv_storico Puntatore allo struct per lo storico CSV
 */
void modifica_articolo(csv_file *csv_magazzino, csv_file *csv_storico);

/**
 * @brief Funzione per gestire la rimozione di un articolo esistente dal magazzino.
 * @warning Attenzione: questa operazione non rimuove lo storico del magazzino relativo all'articolo rimosso.
 * 
 * @param csv_magazzino Puntatore allo struct per il magazzino CSV
 * @param csv_storico Puntatore allo struct per lo storico CSV
 */
void rimuovi_articolo(csv_file *csv_magazzino, csv_file *csv_storico);

/**
 * @brief Funzione per la ricerca (lineare) di un articolo nel magazzino sulla base del relativo codice.
 * 
 * La funzione richiede in input un codice all'utente, e restituisce un puntatore al primo articolo del magazzino con il codice indicato.
 * 
 * @param csv_magazzino Puntatore allo struct per il magazzino CSV
 * @param csv_storico Puntatore allo struct per lo storico CSV
 * 
 * @return Puntatore al primo articolo con il codice indicato se esiste, altrimenti a NULL
 */
csv_row *cerca_articolo(csv_file *csv_magazzino);

/**
 * @brief Funzione per la richiesta dell'input riguardo le caratteristiche di un articolo.
 * 
 * La funzione sovrascrive i contenuti della riga indicata come parametro, liberando la memoria allocata per i singoli campi modificati.
 * 
 * @param row Puntatore allo struct della riga CSV
 */
void inserisci_dati(csv_row *row);

/**
 * @brief Funzione per la gestione dell'input per un singolo campo di un articolo.
 * 
 * La funzione richiede le informazioni all'utente dopo aver mostrato i contenuti correnti del campo, e restituisce un puntatore al nuovo contenuto.
 * 
 * @param row Puntatore allo struct della riga CSV
 * 
 * @return Puntatore al nuovo contenuto indicato in input, oppure a NULL se il contenuto è vuoto
 */
char *inserisci_campo(csv_row *row, char *field);

#endif /* MAGAZZINO_H_ */
