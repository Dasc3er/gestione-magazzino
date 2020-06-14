/**
 * @file utils.c
 * @brief Implementazione delle funzioni di utility per l'interazione con l'utente.
 * 
 * File contenente l'implementazione delle funzioni ausiliarie per l'interazione con l'utente, definite nell'header utils.h.
 * 
 * @see utils.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "utils.h"

char *get_cwd()
{
    char *cwd;
    char buff[PATH_MAX + 1];

    cwd = getcwd(buff, PATH_MAX + 1);
    return cwd;
}

char *read_line()
{
    // Inizializzazione della stringa
    long length = 100;
    int size = sizeof(char);
    char *result = malloc(size * length);

    long index = 0;
    int end = 0;
    while (!end)
    {
        // Allargamento dinamico dello spazio
        if (index >= length)
        {
            length = length * 2;
            result = realloc(result, size * length);

            if (result == NULL)
            {
                fprintf(stderr, "Errore di allocazione dinamica\n");
                exit(EXIT_FAILURE);
            }
        }

        // Controllo sui caratteri
        char c = getchar();
        end = (c == '\n' || c == EOF);

        // Salvataggio del carattere corrente
        *(result + index) = end ? '\0' : c;
        index++;
    }

    // Restrizione dello spazio
    result = realloc(result, size * index);

    return result;
}

char *read_content()
{
    char *content;
    int length = 0;
    while (length == 0)
    {
        content = read_line();
        length = strlen(content);
    }

    return content;
}

char *get_date_string()
{
    // Lettura data di modifica
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Conversione data in stringa
    char *data = malloc(20 * sizeof(char));
    sprintf(data, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    return data;
}