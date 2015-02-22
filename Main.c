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

	free((int *)a);
}

typedef int (*functiontype)(void*, void*);
typedef void (*function)(void*);

int main(){
	functiontype compare= &CompareInts;
	function dest = &Destruct;

	//int *b;
	int *a;
	int i;
	void *obj;
	SortedListPtr List = SLCreate(compare, dest);
	for(i = 0; i < 10; i++){
		a = &i;
		obj = a;

		if(SLInsert(List, obj) == 1){
			printf("Insertion Success \n");
		}
	}

	//SortedListIteratorPtr Iter = SLCreateIterator(List);

	//b = (int*) SLGetItem(Iter);
	//printf("%d ", *b);
	//while( *b > 6){
	//b = (int*) SLNextItem(Iter);
	//printf("%d ", *b);
	//}
	//SLDestroy(List);
	return 0;
}
