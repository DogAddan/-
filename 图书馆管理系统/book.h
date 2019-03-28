#ifndef BOOK_H
#define BOOK_H
#include<iostream>
#include<cstring>
#include<fstream>
#include <stdlib.h>
using namespace std;
class book
{
    public:
        book(){};
        book(char name[50],char type[20],char author[50],int number,int id,float money);
        ~book();

        char* Getname() { return name; }
        char* Gettype() { return type; }
        char* Getauthor() { return author; }
        int Getnumber() { return number; }
        void Setnumber(int val) { number = val; }
        int Getid() { return id; }
        float Getmoney() { return money; }


    protected:

    private:
        char name[50];
        char type[20];
        char author[50];
        int number;
        int id;
        float money;
        string message[10];
};

#endif // BOOK_H
