#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

//Need a clock hand to keep track of pages
int clock_hand;

/* Page to evict is chosen using the clock algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int clock_evict() {
	int evict_page = -1;
	  // loop around the pages like a clock
  	while(evict_page == -1) {
    	// if the bit is 0 then we need to replace this page
    	if (coremap[clock_hand].used == 0) {
      		evict_page = clock_hand;
    	} else {
      		// we know bit is 1 so rest it to 0
      		coremap[clock_hand].used = 0;
      		// continue forward
      		clock_hand = (clock_hand + 1) % memsize;
    	}
  	}
  return evict_page;
}

/* This function is called on each access to a page to update any information
 * needed by the clock algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void clock_ref(pgtbl_entry_t *p) {
	// if PTE for the page was accessed that means we have to set used bit to 1
  	int page_frame;
  	page_frame = (p->frame) >> PAGE_SHIFT;
  	coremap[page_frame].used = 1;

	return;
}

/* Initialize any data structures needed for this replacement
 * algorithm. 
 */
void clock_init() {
	clock_hand = 0;
	//initally the bit is set to 0 for every new page read into memory
	int i;
  	for (i = 0 ; i < memsize; i++) {
    	coremap[i].used =  0;
  	}
}
