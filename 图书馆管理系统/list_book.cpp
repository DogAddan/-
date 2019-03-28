#include "list_book.h"

class list_book* list_book::get_list_book;
list_book::list_book()
{
    this->List=new mList();
    ifstream file;
    file.open("./book/menu.dat",ios::in|ios::binary);
    while(1)
    {
        book* b_data = new book;
        file.read((char*)(b_data),sizeof(book));
        if(file.eof()==1)
            break;
        this->List->addendData(b_data);
    }
    this->List->showList();
    file.close();
}

list_book::~list_book()
{
	ofstream file;
	file.open("./book/menu.dat",ios::out|ios::binary);
	for(Node* node=this->List->head;node;node=node->next)
	{
 		file.write((char*)(node->getData()),sizeof(book));
	}
	file.close();
}

void list_book::create_book(char* name,char* author,char* type,int number,float money)
{
    int id=0;
    if(this->List->tail!=NULL)
    {
        id=this->List->tail->getData()->Getid()+1;
    }
    else
		id=1;
    book* book_one=new book(name,author,type,number,id,money);
    this->List->addendData(book_one);
}

bool list_book::addend_book(int number,int id)
{
    Node* node=this->List->head;
    for(;node;node=node->next)
    {
        if(node->getData()->Getid()==id)
        {
            node->getData()->Setnumber(node->getData()->Getnumber()+number);
            return true;
        }
    }
    return false;
}
bool list_book::addend_book(int number,char* name)
{
    Node* node=this->List->head;
    for(;node;node=node->next)
    {
        if(strcmp(node->getData()->Getname(),name)==0)
        {
            node->getData()->Setnumber(node->getData()->Getnumber()+number);
            return true;
        }
    }
    return false;
}

bool list_book::dec_book(int number,int id)
{
    Node* node = List->head;
    for(;node;node=node->next)
	{
		if(node->getData()->Getid()==id)
        {
			if(node->getData()->Getnumber()>=number)
			{
            	node->getData()->Setnumber(node->getData()->Getnumber()-number);
            	return true;
			}
			else
			{
				return false;
			}
        }
	}
	return false;
}

bool list_book::dec_book(int number,char* name)
{
    Node* node = List->head;
    for(;node;node=node->next)
	{
		if(strcmp(node->getData()->Getname(),name)==0)
        {
			if(node->getData()->Getnumber()>=number)
			{
            	node->getData()->Setnumber(node->getData()->Getnumber()-number);
            	return true;
			}
			else
			{
				return false;
			}
        }
	}
	return false;
}

int list_book::name_to_id(char* name)
{
    Node* node = this->List->head;
	for(;node;node=node->next)
	{
		if(strcmp(node->getData()->Getname(),name)==0)
			return node->getData()->Getid();
	}
	return -1;
}

char* list_book::id_to_name(int id)
{
    Node* node = this->List->head;
	for(;node;node=node->next)
	{
		if(id == node->getData()->Getid())
			return node->getData()->Getname();
	}
	return NULL;
}

bool list_book::find_book(int id,char* book)
{
    Node* node = this->List->head;
	for(;node;node=node->next)
	{
		if(node->getData()->Getid()==id)
        {
            sprintf(book,"书名\t\t作者\t类型\t数量\t编号\t价格\n%s\t%s\t%s\t%d\t%d\t%.2f",node->getData()->Getname(),node->getData()->Getauthor(),node->getData()->Gettype(),node->getData()->Getnumber(),node->getData()->Getid(),node->getData()->Getmoney());
            return true;
        }
	}
	strcpy(book,"未找到该书。");
	return false;
}

bool list_book::find_book(const char* name,char* book)
{
    Node* node = this->List->head;
	for(;node;node=node->next)
	{
		if(strcmp(node->getData()->Getname(),name)==0)
        {
            sprintf(book,"书名\t\t作者\t类型\t数量\t编号\t价格\n%s\t%s\t%s\t%d\t%d\t%.2f",node->getData()->Getname(),node->getData()->Getauthor(),node->getData()->Gettype(),node->getData()->Getnumber(),node->getData()->Getid(),node->getData()->Getmoney());
            return true;
        }
	}
	strcpy(book,"未找到该书。");
	return false;
}

char* list_book::find_book(char* book)
{
    strcpy(book,"书名\t\t作者\t类型\t数量\t编号\t价格\n");
    for(Node* node = this->List->head;node;node=node->next)
    {
        sprintf(book,"%s%s\t%s\t%s\t%d\t%d\t%.2f\n",book,node->getData()->Getname(),node->getData()->Getauthor(),node->getData()->Gettype(),node->getData()->Getnumber(),node->getData()->Getid(),node->getData()->Getmoney());
    }
	return book;
}

bool list_book::delete_book(int id)
{
	size_t count=0;
	for(Node* node=this->List->head;node;node=node->next)
	{
		if(node->getData()->Getid()==id)
		{
			if(List->deleteIndexList(count)==1)
			{
				return true;
			}
			else
				return false;
		}
		count++;
	}
	return false;
}

char* list_book::fuzzy_query_book(const char* name,char* book)
{
    strcpy(book,"书名\t\t作者\t类型\t数量\t编号\t价格\n");
    Node* node=this->List->head;
    while(node)
    {
		string str=node->getData()->Getname();
		if(str.find(name)!=string::npos)
		{
        sprintf(book,"%s%s\t%s\t%s\t%d\t%d\t%.2f\n",book,node->getData()->Getname(),node->getData()->Getauthor(),node->getData()->Gettype(),node->getData()->Getnumber(),node->getData()->Getid(),node->getData()->Getmoney());
    	}
		node=node->next;
	}
	return book;
}
