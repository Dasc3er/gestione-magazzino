#ifndef UTILS_H_
#define UTILS_H_

#include <time.h>

// Colori per l'output
#define COLOR_RED() printf("\033[1;31m");
#define COLOR_GREEN() printf("\033[0;32m");
#define TEXT_RESET() printf("\033[0m");
#define TEXT_BOLD() printf("\033[1m");

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
 * Restituisce il percorso corrente di esecuzione in una stringa allocata in modo dinamico.
 */
char *get_cwd();

/**
 * Restituisce in formato di stringa il contenuto dell'intera riga inserita in input, allocata in modo dinamico.
 *
 * @return Puntatore al contenuto della riga 
 */
char *read_line();

/**
 * Restituisce in formato di stringa il **primo contenuto non vuoto** inserito in una riga di input, tramite allocazione dinamica della memoria.
 *
 * @return Puntatore al contenuto
 */
char *read_content();

/**
 * Restituisce in formato stringa "YYYY-MM-DD HH:mm:ss" la data attuale, in una strina allocata in modo dinamico.
 *
 * @return Puntatore alla stringa
 */
char *get_date_string();

#endif /* UTILS_H_ */
