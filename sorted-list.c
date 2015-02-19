/*
 * sorted-list.c
 *
 *  Created on: Feb 18, 2015
 *      Author: Anthony
 */

#include "sorted-list.h"

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df){
	SortedListPtr newList = malloc(sizeof(SortedListPtr));
	newList->Compare = cf;
	newList->Destruct = df;
	newList->Headptr = NULL;

	return newList;
}

void SLDestroy(SortedListPtr list){
	while(list->Headptr != NULL){
	NodePtr NodetoDelete = malloc(sizeof(NodePtr));
	NodetoDelete = list->Headptr;
	list->Headptr = list->Headptr->next;

	NodetoDelete->next = NULL;
	list->Destruct(NodetoDelete->data);
	free(NodetoDelete);
	}
}

SortedListIteratorPtr SLCreateIterator(SortedListPtr list){
	SortedListIteratorPtr newIterator = malloc(sizeof(SortedListIteratorPtr));
	if(list->Headptr != NULL)
	{
	newIterator->Iterator = list->Headptr;
	incrementreference(list->Headptr);
	return newIterator;
	}
	else
		return NULL;
}
void * SLGetItem( SortedListIteratorPtr iter ){

}
void * SLNextItem(SortedListIteratorPtr iter){

}
int SLInsert(SortedListPtr list, void *newObj){
	SortedListIteratorPtr Iter = SLCreateIterator(list);
	NodePtr newNode;
	NodePtr prevNode;
	void *Comparator = SLGetItem(Iter);
	newNode = NodeCreate(newObj);
	while(list->Compare(Comparator, newObj) > 0){
		prevNode = Iter->Iterator;
		Comparator = SLNextItem(Iter);
	}
	if (list->Compare(Comparator, newObj) == 0){
		return 0;
	}
	else {
		prevNode->next = newNode;
		newNode->next = Iter->Iterator;
		incrementreference(newNode);
	}
	return 1;

}

