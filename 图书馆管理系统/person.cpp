#include "person.h"
#include <cstring>

Person::Person(const char* name,short age,char sex,const char* id,long tel)
{
	strcpy(this->name,name);
	this->age = age;
	this->sex = sex;
	strcpy(this->id,id);
	this->tel = tel;
}

Person::Person()
{

}
