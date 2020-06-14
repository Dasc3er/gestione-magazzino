/**
 * @file utils.h
 * @brief Header per la definizione delle funzioni di utility per l'interazione con l'utente.
 * 
 * Header che definisce le funzioni ausiliarie per l'interazione con l'utente, con riferimento alla gestione degli input e alla formattazione delle date.
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <time.h>

// Colori per l'output
#define COLOR_RED() printf("\033[1;31m");
#define COLOR_GREEN() printf("\033[0;32m");
#define TEXT_RESET() printf("\033[0m");
#define TEXT_BOLD() printf("\033[1m");

// Macro per la gestione delle tabelle
#define TABLE_HEADER_LENTGH 100
#define TABLE_HEADER_SEP(length)    \
    do                              \
    {                               \
        for (int i = 0; i < (length); i++) \
        {                           \
            putchar('=');           \
        }                           \
        putchar('\n');              \
    } while (0)

/**
 * @brief Restituisce il percorso corrente di esecuzione.
 * La stringa contenente il percorso viene allocata in modo dinamico.
 * 
 * @return Puntatore al percorso di esecuzione corrente
 */
char *get_cwd();

/**
 * @brief Restituisce in formato di stringa il contenuto dell'intera riga inserita in input, allocata in modo dinamico.
 *
 * @return Puntatore al contenuto della riga 
 */
char *read_line();

/**
 * @brief Restituisce in formato di stringa il *primo contenuto non vuoto* inserito in una riga di input, tramite allocazione dinamica della memoria.
 *
 * @return Puntatore al contenuto
 */
char *read_content();

/**
 * @brief Restituisce in formato stringa "YYYY-MM-DD HH:mm:ss" la data attuale, in una stringa allocata in modo dinamico.
 *
 * @return Puntatore alla stringa
 */
char *get_date_string();

#endif /* UTILS_H_ */
