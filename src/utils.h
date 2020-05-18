#ifndef UTILS_H_
#define UTILS_H_

// Colori per l'output
#define COLOR_RED() printf("\033[1;31m");
#define COLOR_GREEN() printf("\033[0;32m");
#define COLOR_RESET() printf("\033[0m");

char *get_cwd();

char *read_line();

char * read_content();

#endif /* UTILS_H_ */
