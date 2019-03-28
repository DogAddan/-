#include "list.h"

void mList::showList(void)
{
    if(emptyList())
    {
        printf("*************\n");
        return;
    }

    for(Node* node=head;node;node=node->next)
	{
	    if(node->next==0)
            return;
		cout <<" name:"<< node->getData()->Getname() << "  author:"<<node->getData()->Getauthor() << "  type:"<<node->getData()->Gettype() << "  id:"<<node->getData()->Getid() << "  number:"<<node->getData()->Getnumber() << "   price:"<<node->getData()->Getmoney() << endl;
    }
	cout << endl;
}

bool mList::modifyIndexList(size_t index,TYPE data)
{
    if(index >= count)
		return false;
	Node* node = head;
	for(int i=0;i<(int)index-1;i++)
	{
		node = node->next;
	}
	node->setData(data);
	return true;
}

bool mList::modifyValueList(TYPE oid_data,TYPE new_data)
{
    if(emptyList())
		return false;
	Node* node = head;
	for(int i=0;i<(int)count;i++)
	{
		if(node->getData() == oid_data)
		{
			node->setData(new_data);
			return true;
		}
		node = node->next;
	}
	return false;
}

TYPE mList::getData(int index)
{
    Node* node = head;
    for(int i=0; i < index; i++)
    {
        node = node->next;
    }
    return node->getData();
}

int mList::findData(TYPE data)
{
    Node* node = head;
	for(int i=0;i<(int)count;i++)
	{
		if(node->getData() == data)
			return i;
		node = node->next;
	}
	return -1;
}

bool mList::deleteIndexList(size_t index)
{
    if(index >= count)
		return false;
	Node* temp = head;
	if(0 == index)
	{
		head = temp->next;
	}
	else
	{
		Node* node = head;
		for(int i=0;i<(int)index-1;i++)
		{
			node = node->next;
		}
		temp = node->next;
		node->next = temp->next;
	}
	count--;
	free(temp);
	return true;
}

bool mList::deleteValueList(TYPE data)
{
    if(emptyList())
		return false;
	Node* node = head;
	for(int i=0;i<(int)count;i++)
	{
		if(data == node->next->getData())
		{
			Node* temp = node->next;
			node->next = temp->next;
			count--;
			delete temp;
		}
		else
		{
			node = node->next;
		}
	}
	if(data == head->getData())
	{
		Node* temp = head;
		head = temp->next;
		count--;
        free(temp);
	}
	return true;
}

//删除头
bool mList::deleteHead(void)
{
    printf("--------------------1\n");
    if(emptyList())
		return false;
    printf("--------------------2\n");
    Node* temp = head;
    head = temp->next;
    printf("--------------------%p3\n",temp);
    delete temp;
    count--;
    printf("--------------------4\n");
    return true;
}

//删除尾
bool mList::deleteTail(void)
{
    if(emptyList())
		return false;
    Node* node = head;
    for(int i=0;i<(int)count-2;i++)
	{
		node = node->next;
	}
	Node* temp = tail;
	tail = node;
	tail->next = NULL;
	delete temp;
	count--;
    return true;
}

bool mList::insertData(size_t index,TYPE data)
{
    if(index >= count)
		return false;
	Node* newn = new Node(data);
	if(0 == index)
	{
		newn->next = head;
		head = newn;
	}
	else
	{
		Node* node = head;
		for(int i=0;i<(int)index-1;i++)
			node = node->next;
		newn->next = node->next;
		node->next = newn;
	}
	count++;
    return true;
}

void mList::addendData(TYPE data)
{
    Node* node = new Node(data);
    //判断链表是否为空
	if(emptyList())
	{
		head = node;
		tail = node;
	}
	else
	{
		tail->next = node;
		tail = node;
	}
	count++;
}

bool mList::emptyList(void)
{
    return !count;
}

 mList::~mList(void)
{
   /* Node* node = head;
    do
	{
		Node* temp = node;
		if(node->next!=NULL)
		{
			node = node->next;
		}
		else
			break;
		delete temp;
	}while(1);*/
	while(!emptyList())
	{
		printf("链表析构\n");
		deleteHead();
		printf("1111111111\n");
	}
}

 mList::mList(void)
{
    head = NULL;
    tail = NULL;
    count = 0;
}

