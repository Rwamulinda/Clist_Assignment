# Clist_Assignment

Over view of the implementation

Implementation
The project consists of the following key files:

clist.c: Contains the implementation of the circular linked list, including functions for adding, removing, and accessing elements.
clist.h: The header file that defines the CList structure and declares the associated functions.
clist_test.c: This file includes a series of automated test cases designed to validate the functionality of the circular linked list.
Key Features of the Circular Linked List
Dynamic memory management to allow for flexible size.
Functions to push, pop, append, insert, and remove elements.
Support for accessing elements at specific indices.
Memory management functions to ensure proper cleanup.
Testing Strategy
The testing strategy involved the following steps:

Test Case Development:

Created test cases for each function of the circular linked list, covering normal and edge cases.
Included tests for boundary conditions, such as operations on an empty list, inserting at various indices, and handling duplicates.
Memory Leak Testing:

Implemented a dedicated test for memory leaks by creating and freeing multiple lists in succession. This utilized AddressSanitizer to detect any memory allocation issues.
Scottycheck Integration:

After passing the initial set of self-created tests, the implementation was verified using scottycheck, a tool for automated testing in the course.
Addressed any issues reported by scottycheck by enhancing the test cases and ensuring all edge cases were covered.
Key Tests Included
test_cl_push_pop: Tests the basic push and pop functionality.
test_cl_append: Validates appending elements to the list.
test_cl_nth: Ensures correct retrieval of elements at specific indices.
test_memory_leak: Checks for memory leaks by creating and freeing multiple lists.
test_duplicate_entries: Tests the handling of duplicate entries.
test_cl_insert: Validates inserting elements at various positions.
Conclusion
Through the implementation of the circular linked list and the development of comprehensive test cases, this project demonstrates a solid understanding of data structures and the importance of testing.
