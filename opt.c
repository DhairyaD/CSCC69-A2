#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"
#include "sim.h"

// note: refer to "sim.c" (coremap)

extern unsigned memsize;

extern int debug;

extern struct frame *coremap;

//int *nextPageAccess;
//int timer;

// Using a binary search tree to keep track of when page is accessed
typedef struct BinarySearchTree {

	int currentTime;
	int page;
	struct Bst *right;
	struct Bst *left;

} Bst;

/* Page to evict is chosen using the optimal (aka MIN) algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int opt_evict() {

	//int i, evictIndex, current = 0;

	/*

	for (i = 0; i < memsize; i++) {

		if (coremap[i].nextPageAccess > current) {
			current = coremap[i].nextPageAccess;
			evictIndex = i;
		}

		if (coremap[i].nextPageAccess < 0){
			return i;
		}
	}

	return evictIndex;
	*/
	return 0;
}

/* This function is called on each access to a page to update any information
 * needed by the opt algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void opt_ref(pgtbl_entry_t *p) {


	// coremap[p -> frame >> PAGE_SHIFT].nextPageAccess = nextPageAccess[timer];
	return;
}

/* Initializes any data structures needed for this
 * replacement algorithm.
 */
void opt_init() {

}
