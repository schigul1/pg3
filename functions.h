#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stddef.h>

unsigned int safe_add(unsigned int n1, unsigned int n2);
unsigned int min(unsigned int x, unsigned int y);
unsigned int **read_table(const char *filename, size_t *sz);
unsigned int dijkstra(unsigned int src, unsigned int dst, unsigned int **table,
                      size_t sz);

#endif // FUNCTIONS_H