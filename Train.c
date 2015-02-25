#include <stdio.h>
#include "sorted-list.h"
#include <string.h>

struct fool{
	int comparator;
	float **what;
	char *b;
};
typedef struct fool foolptr;

 foolptr make(int a){
	 int coo;
	 foolptr tony = malloc(sizeof(foolptr));
	 tony->comparator = a;
	 tony-> what = malloc(comparator*sizeof(float*));
	 for(coo = 0; coo < a; coo++){
		what[coo] = (float)a; 
	 }
	 tony->b = "A string";
 }


/*take fools, pull the int out and compare em.*/
int CompareInts(void *a, void *b){
	int first = (a->comparator);
	int second = (b->comparator);
	if(first > second){
		return 1;

	}
	else if(first < second){
		return -1;
	}
	else
		return 0;
}

void Destruct(void *a){
	/*the void *a is a fool struct. */
	/*We're assured that the strings are null terminated. But we'll use strnlen for good practice.*/
	int len;
	free(a->what);
	free(a);
}



