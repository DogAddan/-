#include "node.h"

 Node::Node(TYPE data)
{
    this->data = data;
    this->next = NULL;
}

Node::~Node()
{
	printf("node释放\n");
	delete this->data;
}

TYPE Node::getData(void)
{
    return data;
}

void Node::setData(TYPE data)
{
    this->data = data;
}
