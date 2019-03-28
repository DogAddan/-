#ifndef PERSON_H
#define PERSON_H
#include "struct.h"
class Person
{
public:
	char name[20];
	short age;
	char sex;
	char id[20];
	long tel;
	Person(const char* name,short age,char sex,const char* id,long tel);

	Person();

	virtual bool in(Pac* pac) = 0;

	virtual bool out(Pac* pac) = 0;
	
};
#endif // PERSON_H
