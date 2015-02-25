#include <stdio.h>
#include "sorted-list.h"
#include <string.h>

struct fool{
	int comparator;
	float **what;

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
	free(lol->what);
	free(a);
}

typedef int (*functiontype)(void*, void*);
typedef void (*function)(void*);

int main(){
	foolptr b;
	foolptr k;
	int i;
	void* obj;
	functiontype compare= &CompareInts;
	function dest = &Destruct;
	SortedListPtr List;
	SortedListIteratorPtr Iter;
	SortedListIteratorPtr it;
	List = SLCreate(compare, dest);
	for(i = 0; i < 10; i++){

		obj = make(i);

		if(SLInsert(List, obj) == 1){
			printf("Insertion Success \n");
		}
	}
	Iter = SLCreateIterator(List);
	it = SLCreateIterator(List);
	printf("Printing out all of the items in the list \n");

	b = (foolptr) SLGetItem(Iter);
	printf("%d ", b->comparator);
	b = (foolptr) SLNextItem(Iter);

	while (b !=NULL){
	printf("%d ", b->comparator);
	b = (foolptr) SLNextItem(Iter);

	}



	b = (foolptr) SLGetItem(it);
	printf("\nThe iterator is currently pointing to: %d \n", b->comparator);

	printf("Remove struct with value of 8 while an iterator is pointing to it\n");

	//Move to second Node
	b = (foolptr) SLNextItem(it);
	printf("The iterator is currently pointing to: %d \n", b->comparator);
	//Remove Node 8 but keep iterator pointing to it

	printf("Removing... \n");
	k = make(8);
	obj = k;
	SLRemove(List,obj);

	printf("Can the iterator still access the list?(If output is 7 6 5 4 3 2 1 0 Success) \n");
	while (b !=NULL){

		b = (foolptr) SLNextItem(it);
		if(b != NULL){
			printf("%d ", b->comparator);
			}
		}
	printf("\nYes! Success!");

	SLDestroyIterator(it);
	SLDestroyIterator(Iter);
	SLDestroy(List);
	printf("\n Checking if fully destroyed \n");
	it = SLCreateIterator(List);
	if(it == NULL){
		printf ("There is nothing to point to...the list has been removed");
	}
	else
		printf("Failed to destroy");
	return 0;
}

