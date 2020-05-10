#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>

void check_allocation(void *pointer);

FILE* file_open(char *filepath);

void file_close(FILE *file);

#endif /* UTILS_H_ */
