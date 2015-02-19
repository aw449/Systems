/*
 * Node.h
 *
 *  Created on: Feb 18, 2015
 *      Author: Anthony
 */

#ifndef NODE_H_
#define NODE_H_

struct Node{
	int *referencecount;
	struct Node *next;
	void *data;
};
typedef struct Node* NodePtr;

void setNext(NodePtr NextNode);

NodePtr NodeCreate(void * myObj);

void incrementreference(NodePtr Node);
void decrementreference(NodePtr Node);

#endif /* NODE_H_ */
