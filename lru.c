#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

unsigned long time;

/* Page to evict is chosen using the accurate LRU algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int lru_evict() {
	int i;
	int PFN;
	unsigned long minimum = time + 1;
	for (i = 0; i < memsize; i++) {
		// If its lower than minimum then that page is least recently used
		// so set minimum as that and keep looking
		if (coremap[i].time < minimum) {
			minimum = coremap[i].time;
		  	PFN = i;  
		}
	}
  	// return the page frame number of the least recently used page
	return PFN;
}

/* This function is called on each access to a page to update any information
 * needed by the lru algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void lru_ref(pgtbl_entry_t *p) {
	coremap[p->frame >> PAGE_SHIFT].time = time;
  	time = time + 1;
	return;
}


/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void lru_init() {
	time = 0;
	int i;
	for (i = 0; i < memsize; i++) {
		coremap[i].time = time;
		time++;
	}
}
