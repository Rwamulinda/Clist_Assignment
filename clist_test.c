/*
 * clist_test.c
 * 
 * Automated test code for CLists
 * 
 * Author: Pauline Uwase
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "clist.h"


// Some known testdata, for testing
const char *testdata[] = {"Zero", "One", "Two", "Three", "Four", "Five",
  "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen",
  "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen",
  "Twenty"};

const char *testdata_sorted[] = {"Eight", "Eighteen", "Eleven", "Fifteen",
  "Five", "Four", "Fourteen", "Nine", "Nineteen", "One", "Seven",
  "Seventeen", "Six", "Sixteen", "Ten", "Thirteen", "Three", "Twelve",
  "Twenty", "Two", "Zero"};

static const int num_testdata = sizeof(testdata) / sizeof(testdata[0]);


// Checks that value is true; if not, prints a failure message and
// returns 0 from this function
#define test_assert(value) {                                            \
    if (!(value)) {                                                     \
      printf("FAIL %s[%d]: %s\n", __FUNCTION__, __LINE__, #value);      \
      goto test_error;                                                  \
    }                                                                   \
  }

// Checks that value == INVALID_RETURN; if not, prints a failure
// message and returns 0 from this function
#define test_invalid(value) {                                           \
    if (value != INVALID_RETURN) {                                      \
      printf("FAIL %s[%d]: %s\n", __FUNCTION__, __LINE__, #value);      \
      goto test_error;                                                  \
    }                                                                   \
  }

// Checks that value == expected; if not, prints a failure message and
// returns 0 from this function
#define test_compare(value, expected) {                           \
    const char *v = (value);                                      \
    const char *e = (expected);                                   \
    if (strcmp(v, e) != 0) {                                      \
      printf("FAIL %s[%d] %s: expected '%s', got '%s'\n",         \
          __FUNCTION__, __LINE__, #value, e, v);                  \
      goto test_error;                                            \
    }                                                             \
  }


/*
 * Tests the CL_new, CL_push, CL_pop, and CL_free functions
 *
 * Returns: 1 if all tests pass, 0 otherwise
 */
int test_cl_push_pop()
{
  int ret = 0;
  CList list = CL_new();

  test_assert( CL_length(list) == 0 );
  test_invalid( CL_pop(list) );

  CL_push(list, testdata[0]);

  test_assert( CL_length(list) == 1 );
  test_compare( CL_pop(list), testdata[0] );
  test_assert( CL_length(list) == 0 );
  test_invalid( CL_pop(list) );

  for (int i=0; i < num_testdata; i++) {
    CL_push(list, testdata[i]);
    test_assert( CL_length(list) == i+1 );
  }

  for (int i=num_testdata-1; i >= 0; i--) {
    test_compare( CL_pop(list), testdata[i] );
    test_assert( CL_length(list) == i );
  }

  ret = 1;

 test_error:
  CL_free(list);
  return ret;
}

int test_cl_append()
{
  int ret = 0;
  CList list = CL_new();
  
  // Append all the items
  for (int i=0; i < num_testdata; i++) {
    CL_append(list, testdata[i]);
    test_assert( CL_length(list) == i+1 );
  }

  // ensure that the list is in the right order
  for (int i=0; i < num_testdata; i++)
    test_compare( CL_nth(list, i), testdata[i] );

  ret = 1;

 test_error:
  CL_free(list);
  return ret;
}


/*
 * Tests the CL_nth function
 *
 * Returns: 1 if all tests pass, 0 otherwise
 */
int test_cl_nth()
{
  int ret = 0;
  CList list = CL_new();
  
  // Empty list -- ensure that CL_nth returns NULL for -2, -1, 0, 1, and 2
  test_invalid( CL_nth(list, -2) );
  test_invalid( CL_nth(list, -1) );
  test_invalid( CL_nth(list, 0) );
  test_invalid( CL_nth(list, 1) );
  test_invalid( CL_nth(list, 2) );

  // Add one item, then perform same tests
  CL_push(list, testdata[2]);
  test_assert( CL_length(list) == 1 );
  test_invalid( CL_nth(list, -3) );
  test_invalid( CL_nth(list, -2) );
  test_compare( CL_nth(list, -1), testdata[2]);
  test_compare( CL_nth(list, 0), testdata[2]);
  test_invalid( CL_nth(list, 1) );
  test_invalid( CL_nth(list, 2) );

  // Push two more items, perform similar tests 
  CL_push(list, testdata[1]);
  CL_push(list, testdata[0]);
  test_assert( CL_length(list) == 3 );
  test_invalid( CL_nth(list, -5) );
  test_invalid( CL_nth(list, -4) );
  test_compare( CL_nth(list, -3), testdata[0]);
  test_compare( CL_nth(list, -2), testdata[1]);
  test_compare( CL_nth(list, -1), testdata[2]);
  test_compare( CL_nth(list, 0), testdata[0]);
  test_compare( CL_nth(list, 1), testdata[1]);
  test_compare( CL_nth(list, 2), testdata[2]);
  test_invalid( CL_nth(list, 3) );
  test_invalid( CL_nth(list, 4) );

  ret = 1;

 test_error:
  CL_free(list);
  return ret;
}

int test_cl_insert() {
    int ret = 0;
    CList list = CL_new();
    CL_push(list, "first");
    CL_insert(list, "second", 1); // Insert at end
    CL_insert(list, "zero", 0); // Insert at start
    test_compare(CL_nth(list, 0), "zero");
    test_compare(CL_nth(list, 1), "first");
    test_compare(CL_nth(list, 2), "second");
    ret = 1;

test_error:
    CL_free(list);
    return ret;
}


int test_duplicate_entries() {
    int ret = 0;
    CList list = CL_new();
    CL_push(list, "alpha");
    CL_push(list, "alpha");  // Push duplicate
    test_assert(CL_length(list) == 2);
    test_compare(CL_pop(list), "alpha");
    test_compare(CL_pop(list), "alpha"); // Should be able to pop both
    ret = 1;

test_error:
    CL_free(list);
    return ret;
}

/*
 * Test for memory leaks by creating and freeing multiple lists
 *
 * Returns: 1 if all tests pass, 0 otherwise
 */
int test_memory_leak() {
    const int num_lists = 100; // Number of lists to create and free
    for (int i = 0; i < num_lists; i++) {
        CList list = CL_new(); // Create a new list
        for (int j = 0; j < num_testdata; j++) {
            CL_append(list, testdata[j]); // Append some data
        }
        CL_free(list); // Free the list
    }
    return 1; // If all iterations complete without issue, return success
}




  //
  // TODO: Add your code here
  //


/*
 * A demonstration of how to use a CList, which also doubles as a
 * test case.
 *
 * Returns: 1 if all tests pass, 0 otherwise.
 */
int sample_clist_usage()
{
  int ret = 0;
  CList list = CL_new();

  // new lists have length 0
  test_assert( CL_length(list) == 0 );

  CL_push(list, "alpha");       // push 'alpha' onto front of list
  CL_push(list, "bravo");       // push 'bravo' onto front of list
  CL_push(list, "charlie");     // push 'charlie' onto front of list

  // list is now charlie, bravo, alpha

  CL_print(list);               // print out the list: charlie, bravo, alpha

  test_assert( CL_length(list) == 3 );

  // pop the element off the front of the list, which should be 'charlie'
  test_compare( CL_pop(list), "charlie" );
  test_assert( CL_length(list) == 2 );

  CL_insert(list, "delta", 2);    // insert 'delta' at position 2
  CL_append(list, "echo");        // append 'echo' at end of list
  CL_insert(list, "foxtrot", -2); // insert 'foxtrot' one before end

  // list is now: bravo, alpha, delta, foxtrot, echo
  test_assert( CL_length(list) == 5 );

  // retrieve the 3rd element, numbering from 0, so it should be foxtrot
  test_compare( CL_nth(list, 3), "foxtrot" );
  
  // list hasn't changed
  test_assert( CL_length(list) == 5 );

  // now REMOVE the third element
  test_compare( CL_remove(list, 3), "foxtrot" );
  test_assert( CL_length(list) == 4 );

  // list is now: bravo, alpha, delta, echo

  // make a copy of the list
  CList list_copy = CL_copy(list);

  test_assert( CL_length(list_copy) == 4 );

  // reverse the copy, so it is now echo, delta, alpha, bravo
  CL_reverse(list_copy);

  // remove the first item from the copy
  test_compare( CL_remove(list_copy, 0), "echo" );
  test_assert( CL_length(list_copy) == 3 );
  
  // original list should be unchanged
  test_assert( CL_length(list) == 4 );
  
  // join the two lists; note this operation empties list_copy
  CL_join(list, list_copy);

  // list is now: bravo, alpha, delta, echo, delta, alpha, bravo
  // list_copy should be empty
  test_assert( CL_length(list) == 7 );
  test_compare( CL_nth(list, 3), "echo" );
  test_assert( CL_length(list_copy) == 0);

  ret = 1;

 test_error:
  // Lists must be destroyed
  CL_free(list);
  CL_free(list_copy);
  return ret;
}


int main()
{
  int passed = 0;
  int num_tests = 0;

  num_tests++; passed += test_cl_push_pop(); 
  num_tests++; passed += test_cl_append();
  num_tests++; passed += test_cl_nth();
  num_tests++; passed += test_memory_leak(); // Add memory leak test here
  num_tests++; passed += test_duplicate_entries();
  num_tests++; passed += test_cl_insert();

  //
  // TODO: Add your code here
  //

  num_tests++; passed += sample_clist_usage();

  printf("Passed %d/%d test cases\n", passed, num_tests);
  fflush(stdout);
  return 0;
}
