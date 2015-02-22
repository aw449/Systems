/*
 * Node.h

 */

#ifndef NODE_H_
#define NODE_H_

#include <stdlib.h>

struct Node{
	int referencecount;
	struct Node *next;
	void *data;
};
typedef struct Node* NodePtr;


NodePtr NodeCreate(void * myObj);

void NodeDestroy(NodePtr Node);

void incrementreference(NodePtr Node);

int decrementreference(NodePtr Node);

#endif /* NODE_H_ */
