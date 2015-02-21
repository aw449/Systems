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
		//NodePtr NodetoDelete = malloc(sizeof(NodePtr));
		NodePtr NodetoDelete;
		NodetoDelete = list->Headptr;
		list->Headptr = list->Headptr->next;
	
		//NodetoDelete->next = NULL;//Necessary?
		list->Destruct(NodetoDelete->data);
		free(NodetoDelete);
	}
	free(list);
}

SortedListIteratorPtr SLCreateIterator(SortedListPtr list){
	SortedListIteratorPtr newIterator = malloc(sizeof(SortedListIteratorPtr));
	//Check it
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
	//decrementreference(iter->Iterator);
	free(iter);
}
void *SLGetItem( SortedListIteratorPtr iter ){
	return iter->Iterator->data;
}
void *SLNextItem(SortedListIteratorPtr iter){
	if(decrementreference(iter->Iterator)==0){
		SortedListIteratorPtr temp = iter;
	}
	iter->Iterator = iter->Iterator->next;
	incrementreference(iter->Iterator);
	free(temp);
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
	SortedListIteratorPtr temp = NULL;
	if((SortedListIteratorPtr Iter = SLCreateIterator(list))!= NULL){
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
		if(decrementreference(Iter->Iterator) == 0){
			list->Destruct(Iter->Iterator);
			//What does the Destruct function do, exactly?
			temp = Iter->Iterator;
		}
		SLDestroyIterator(Iter);
		if(temp!=NULL){
			free(temp);
		}
		
		return 1;
	}
	else
		return 0;
}

