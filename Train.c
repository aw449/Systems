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

typedef int (*functiontype)(void*, void*);
typedef void (*function)(void*);

int main(){
	int *b;
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
		//Print First Value
	b = (int*) SLGetItem(Iter);
	printf("%d ", *b);

	//Move to second Node 9 but do not print out
	b = (int*) SLNextItem(Iter);

	//Remove Node 9 but keep iterator pointing to it
	int k = 9;
	obj = &k;
	SLRemove(List,obj);

	//Can the iterator still access the list?
	while( *b > 1){
		b = (int*) SLNextItem(Iter);
		printf("%d ", *b);
	}
	//Success if Output is 10 8 7 6...
	SLDestroy(List);
	return 0;
}

