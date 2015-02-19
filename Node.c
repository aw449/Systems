/*
 * Node.c
 *
 *  Created on: Feb 18, 2015
 *      Author: Anthony
 */


#include "Node.h"
NodePtr NodeCreate(void * myObj){
	return 0;
}
void incrementreference(NodePtr Node){
	Node->referencecount++;
}

void decrementreference(NodePtr Node){
	Node->referencecount--;
}
