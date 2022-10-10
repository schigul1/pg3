#include "functions.h"
#include "solutions.h"
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void print_table(unsigned int** table, size_t sz);

int main(int argc, char **argv) {
  size_t sz;

  // Read input table of distances
  unsigned int **table = _read_table("mileages.txt", &sz);

  // Print table of distances
  print_table(table, sz);

  // Run Dijkstra's algorithm on table, between src and dst
  if (argc == 3) {
    unsigned int src = atoi(argv[1]);
    unsigned int dst = atoi(argv[2]);
    printf("Dijkstra %u to %u: %u\n", src, dst, _dijkstra(src, dst, table, sz));
  } else {
    unsigned int src = 2;
    for (unsigned int dst = 0; dst < sz; dst++) {
      printf("Dijkstra %u to %u: %u\n", src, dst,
             _dijkstra(src, dst, table, sz));
    }
  }

  // Clean up allocations from read_table()
  for (int i = 0; i < sz; i++) {
    free(table[i]);
    table[i] = NULL;
  }
  free(table);
  table = NULL;

  return 0;
}