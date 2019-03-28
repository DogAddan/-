#ifndef NODE_H
#define NODE_H

#include "book.h"
#include <iostream>

typedef book* TYPE;



class Node
{
private:
	TYPE data;
public:
    Node* next;
	Node(TYPE data);
	~Node(void);
	TYPE getData(void);
	void setData(TYPE data);
};


#endif // NODE_H

