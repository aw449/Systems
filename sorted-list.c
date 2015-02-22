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
	//Destroy the list
	while(list->Headptr != NULL){
	//NodePtr NodetoDelete = malloc(sizeof(NodePtr));
	NodePtr NodetoDelete;
	NodetoDelete = list->Headptr;
	list->Headptr = list->Headptr->next;

	NodeSeppuku(NodetoDelete);
	}
	free(list);
}

SortedListIteratorPtr SLCreateIterator(SortedListPtr list){
	SortedListIteratorPtr newIterator = malloc(sizeof(SortedListIteratorPtr));
	//Create a new iterator if list is empty iterator points to NULL
	if(list->Headptr != NULL)
	{
		newIterator->Node = list->Headptr;
		newIterator->Node->Seppuku = list->Destruct;
		incrementreference(list->Headptr);
		return newIterator;
	}
	else
		return NULL;
}

void SLDestroyIterator(SortedListIteratorPtr iter){
	//The node that the iterator is pointing to loses a referencecount when iterator is removed
	if(decrementreference(iter->Node) == 0){
		NodeSeppuku(iter->Node);
	}
	free(iter);
}
void *SLGetItem( SortedListIteratorPtr iter ){
	return iter->Node->data;
}
void *SLNextItem(SortedListIteratorPtr iter){

	if(decrementreference(iter->Node)== 0){
		//NO ACCESS TO DESTRUCT FUNCTION CANNOT DESTROY
		//MUST DESTROY MUST DESTORY MUST DESTROY
		NodeSeppuku(iter->Node);
	}
	iter->Node = iter->Node->next;
	incrementreference(iter->Node);
	return iter->Node->data;

}
int SLInsert(SortedListPtr list, void *newObj){
	SortedListIteratorPtr Iter = SLCreateIterator(list); 	//Create a temporary iterator
	NodePtr newNode;	//newNode object
	NodePtr prevNode;
	void *Comparator = SLGetItem(Iter); //Comparator is data from the list to compare; starts from data in headptr
	newNode = NodeCreate(newObj);  //Create a Node containing given data
	if(list->Headptr == NULL)  //if the list is empty just make headptr point to the newNode
		{
		list->Headptr = newNode;
		incrementreference(newNode);
		return 1;
		}
	else {
		while(list->Compare(Comparator, newObj) > 0){ //If the compare function returns >0 means if newObj is less than or equal to compared object (List is ordered from largest to smallest
			prevNode = Iter->Node;
			Comparator = SLNextItem(Iter);
		}
		if (list->Compare(Comparator, newObj) == 0){ //Throw out if duplicate is found
			return 0;
		}
		else {
			prevNode->next = newNode;
			newNode->next = Iter->Node;
			incrementreference(newNode);
		}
		SLDestroyIterator(Iter);
		return 1;
	}

}

int SLRemove(SortedListPtr list, void *newObj){
	SortedListIteratorPtr Iter = SLCreateIterator(list); //Temp iterator
	NodePtr prevNode;
	void *Comparator = SLGetItem(Iter); //Samething as in Slinsert
	while(list->Compare(Comparator, newObj) != 0){
				prevNode = Iter->Node;
				Comparator = SLNextItem(Iter);
				if(Comparator == NULL){ //if object not found and comparator has reached the end of the list....end and return failure
					return 0;
				}
			}

	prevNode->next = Iter->Node->next;
	if(decrementreference(Iter->Node) == 0){ //Decrement the reference count & if refcount == 0 delete the node and data
		NodeSeppuku(Iter->Node);

	}
	SLDestroyIterator(Iter); // Destroy temp iterator
	return 1;
}

