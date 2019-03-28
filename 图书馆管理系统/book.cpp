#include "book.h"

book::book(char name[50],char type[20],char author[50],int number,int id,float money)
{
    strcpy(this->name,name);
    strcpy(this->type,type);
    strcpy(this->author,author);
    this->number=number;
    this->money=money;
    this->id=id;
}

book::~book()
{
    ofstream file;
    file.open("./book/menu.dat",ios::out|ios::binary|ios::app);
    file.write((char*)(this),sizeof(book));
    file.close();
	printf("书析构\n");
}

