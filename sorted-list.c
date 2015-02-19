/*
 * sorted-list.c

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
	free(list);
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

void SLDestroyIterator(SortedListIteratorPtr iter){
	decrementreference(iter->Iterator);
	free(iter);
}
void *SLGetItem( SortedListIteratorPtr iter ){
	return iter->Iterator->data;
}
void *SLNextItem(SortedListIteratorPtr iter){
	decrementreference(iter->Iterator);
	iter->Iterator = iter->Iterator->next;
	incrementreference(iter->Iterator);
	return iter->Iterator->data;

}
int SLInsert(SortedListPtr list, void *newObj){

	SortedListIteratorPtr Iter = SLCreateIterator(list);
	NodePtr newNode;
	NodePtr prevNode;
	void *Comparator = SLGetItem(Iter);
	newNode = NodeCreate(newObj);
	if(list->Headptr == NULL)
		{
		list->Headptr = newNode;
		incrementreference(newNode);
		return 1;
		}
	else {
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
		SLDestroyIterator(Iter);
		return 1;
	}

}

int SLRemove(SortedListPtr list, void *newObj){
	SortedListIteratorPtr Iter = SLCreateIterator(list);
	NodePtr prevNode;
	void *Comparator = SLGetItem(Iter);
	while(list->Compare(Comparator, newObj) != 0){
				prevNode = Iter->Iterator;
				Comparator = SLNextItem(Iter);
				if(Comparator == NULL){
					return 0;
				}
			}

	prevNode->next = Iter->Iterator->next;
	decrementreference(Iter->Iterator);
	SLDestroyIterator(Iter);
	return 1;
}

