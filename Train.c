#include <stdio.h>
#include "sorted-list.h"
#include <string.h>

struct fool{
	int comparator;
	float **what;
	char *b;
};
typedef struct fool* foolptr;

 foolptr make(int a){
	 int coo;
	 foolptr tony = malloc(sizeof(foolptr));
	 tony->comparator = a;
	 tony-> what = malloc(tony->comparator*sizeof(float*));
	 for(coo = 0; coo < a; coo++){
		 tony->what[coo] = (float*)a;
	 }
	 tony->b = "A string";

	 return tony;
 }


/*take fools, pull the int out and compare em.*/
int CompareInts(void *a, void *b){
	foolptr lol = (struct fool*) a;
	foolptr nein = (struct fool*)b;
	int first = (lol->comparator);
	int second = (nein->comparator);
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
	foolptr lol = (struct fool*) a;
	//int len;
	free(lol->what);
	free(a);
}

typedef int (*functiontype)(void*, void*);
typedef void (*function)(void*);

int main(){
	foolptr b;
	int i;
	void* obj;
	functiontype compare= &CompareInts;
	function dest = &Destruct;
	SortedListPtr List;
	List = SLCreate(compare, dest);
	for(i = 0; i < 10; i++){

		obj = make(i);

		if(SLInsert(List, obj) == 1){
			printf("Insertion Success \n");
		}
	}
	SortedListIteratorPtr Iter = SLCreateIterator(List);
	b = (foolptr) SLGetItem(Iter);
	printf("%d ", b->comparator);
	b = (foolptr) SLNextItem(Iter);

	while (b !=NULL){
	printf("%d ", b->comparator);
	b = (foolptr) SLNextItem(Iter);

	}
	return 0;
}

