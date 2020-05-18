#ifndef CSV_UTILS_H_
#define CSV_UTILS_H_

#include <stdio.h>

void check_allocation(void *pointer);

FILE* csv_file_open(char *filepath);

void csv_file_close(FILE *file);

#endif /* CSV_UTILS_H_ */
