/**
 * @file utils.h
 * @brief Header per la definizione delle funzionalità di utility della libreria.
 * 
 * Header che definisce le funzioni di utility della liberia CSV, in particolare in relazione ai controlli sull'allocazione dinamica della memoria.
 */

#ifndef CSV_UTILS_H_
#define CSV_UTILS_H_

/**
 * @brief Funzione per il controllo sulla corretta allocazione dinamica di un puntatore.
 * 
 * Se il puntatore non è definito (puntatore a NULL) viene visualizzato un errore relativo e bloccata l'esecuzione del programma.
 * 
 * @param pointer Puntatore generico
 */
void check_allocation(void *pointer);

#endif /* CSV_UTILS_H_ */
