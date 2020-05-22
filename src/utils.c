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
    int length = 100;
    int size = sizeof(char);
    char *result = malloc(size * length);

    int i = 0;
    int end = 0;
    while (!end)
    {
        // Allargamento dinamico dello spazio
        if (i >= length)
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
        *(result + i) = end ? '\0' : c;
        i++;
    }

    // Restrizione dello spazio
    length = i;
    result = realloc(result, size * length);

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
    sprintf(data, "%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    return data;
}