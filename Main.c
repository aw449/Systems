/*
 * Main.c
 *
 *  Created on: Feb 19, 2015
 *      Author: Anthony
 */

#include <stdio.h>
#include "sorted-list.h"

int CompareInts(void *a, void *b){
	int first = *((int *) a);
	int second = *((int *) b);
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

	//free(a);
	//a = NULL;
}

typedef int (*functiontype)(void*, void*);
typedef void (*function)(void*);

int main(){
	functiontype compare= &CompareInts;
	function dest = &Destruct;
	int *b;
	int myArray[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int i;
	void *obj;
	SortedListPtr List = SLCreate(compare, dest);
	for(i = 0; i < 10; i++){

		obj = &myArray[i];

		if(SLInsert(List, obj) == 1){
			printf("Insertion Success \n");
		}
	}

	SortedListIteratorPtr Iter = SLCreateIterator(List);

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
