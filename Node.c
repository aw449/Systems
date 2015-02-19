/*
 * Node.c
 *
 */


#include "Node.h"
NodePtr NodeCreate(void * myObj){
	NodePtr newNode = malloc(sizeof(NodePtr));
	newNode->data = myObj;
	newNode->next = NULL;
	newNode->referencecount = 0;
	return newNode;
}


void NodeDestroy(NodePtr Node){
	free((Node->data));
	Node->data = NULL;
	Node->next = NULL;
	Node->referencecount = 0;
	free(Node);
}

void incrementreference(NodePtr Node){
	Node->referencecount++;
}

void decrementreference(NodePtr Node){
	if(Node->referencecount == 0){
		NodeDestroy(Node);
	}
	else
	Node->referencecount--;
}
