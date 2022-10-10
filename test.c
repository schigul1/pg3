#include "functions.h"
#include "solutions.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <limits.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

unsigned int **table = NULL;
unsigned int **exptable = NULL;
size_t sz;
size_t expsz;

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite3(void) {
  // Initialize random integers for tests
  srand(time(NULL));

  // Initialize mileage table
  exptable = _read_table("mileages.txt", &expsz);

  return !exptable;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite3(void) {
  if (exptable){
    // Free table rows
    for (int i = 0; i < sz; i++) {
      free(exptable[i]);
      free(table[i]);
      exptable[i] = NULL;
      table[i] = NULL;
    }
    // Free table
    free(exptable);
    free(table);
    exptable = NULL;
    table = NULL;
  }
  return 0;
}

void testSAFEADD(void) {
  int randnums [4] = {rand(), rand(), rand(), rand()};
  CU_ASSERT_EQUAL(safe_add(UINT_MAX,1), _safe_add(UINT_MAX,1));
  CU_ASSERT_EQUAL(safe_add(2100000001,2194967295), _safe_add(2100000001,2194967295));
  CU_ASSERT_EQUAL(safe_add(2100000001,2194967293), _safe_add(2100000001,2194967293));
  CU_ASSERT_EQUAL(safe_add(randnums[0],randnums[1]), _safe_add(randnums[0],randnums[1]));
  CU_ASSERT_EQUAL(safe_add(randnums[2],randnums[3]), _safe_add(randnums[2],randnums[3]));
}

void testMIN(void){
  int randnums [5] = {rand(), rand(), rand(), rand(), rand()};
  CU_ASSERT_EQUAL(min(randnums[0],randnums[1]),_min(randnums[0],randnums[1]));
  CU_ASSERT_EQUAL(min(randnums[1],randnums[2]),_min(randnums[1],randnums[2]));
  CU_ASSERT_EQUAL(min(randnums[2],randnums[3]),_min(randnums[2],randnums[3]));
  CU_ASSERT_EQUAL(min(randnums[3],randnums[4]),_min(randnums[3],randnums[4]));
  CU_ASSERT_EQUAL(min(UINT_MAX,randnums[0]),_min(UINT_MAX,randnums[0]));
}

void testREADTABLE(void) {
  table = read_table("mileages.txt", &sz);

  // Assert proper read of the size variable
  CU_ASSERT_EQUAL_FATAL(sz, expsz);

  for (int row = 0; row < expsz; row++){
    for (int col = 0; col < expsz; col++){
      if (table[row][col] != exptable[row][col]){
        char msg [256] = {'\0'};
        snprintf(msg, 255, "Table mismatch at row %i, col %i: actual: %u, expected: %u", 
          row, col, table[row][col], exptable[row][col]) ;
        CU_FAIL_FATAL(msg);
      }
    }
  } CU_PASS("Actual table equals expected table");
}

void testDIJKSTRA(void){
  unsigned int src = 2;
  for (unsigned int dst = 0; dst < expsz; dst++) {
    CU_ASSERT_EQUAL(dijkstra(src, dst, exptable, expsz), _dijkstra(src, dst, exptable, expsz));
  }
}

int main(int argc, char *argv[]) {
  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suite to the registry */
  pSuite = CU_add_suite("Suite_3", init_suite3, clean_suite3);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if ((NULL == CU_add_test(pSuite, "test of safe_add", testSAFEADD)) ||
      (NULL == CU_add_test(pSuite, "test of min", testMIN)) ||
      (NULL == CU_add_test(pSuite, "test of read_table", testREADTABLE)) ||
      (NULL == CU_add_test(pSuite, "test of dijkstra", testDIJKSTRA))) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}