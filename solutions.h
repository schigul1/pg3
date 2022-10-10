#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <stddef.h>

void print_table(unsigned int** table, size_t sz);

unsigned int _safe_add(unsigned int n1, unsigned int n2);
unsigned int _min(unsigned int x, unsigned int y);
unsigned int **_read_table(const char *filename, size_t *sz);
unsigned int _dijkstra(unsigned int src, unsigned int dst, unsigned int **table,
                      size_t sz);

#endif // SOLUTIONS_H