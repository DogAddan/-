#include <cstdio>
#include "stockadmin.h"

StockAdmin::StockAdmin(const char* name,short age,char sex,const char* id,long tel):Person(name,age,sex,id,tel)
{
	
}

StockAdmin::StockAdmin()
{
	
}

bool StockAdmin::newbook(Msg* msg)
{
	list_book::Get_list_book()->create_book(msg->bookname,msg->type,msg->author,msg->cnt,msg->money);
	return true;
}

bool StockAdmin::deletebook(Msg* msg)
{

	return list_book::Get_list_book()->delete_book(msg->bookid);
}

bool StockAdmin::in(Pac* pac)
{
	bool flag = false;
	if(0 != pac->msg.bookid)
		flag = list_book::Get_list_book()->addend_book(pac->msg.cnt,pac->msg.bookid);
	else
		flag = list_book::Get_list_book()->addend_book(pac->msg.cnt,pac->msg.bookname);
	return flag;
}

bool StockAdmin::out(Pac* pac)
{
	bool flag = false;
	if(0 != pac->msg.bookid)
		flag = list_book::Get_list_book()->dec_book(pac->msg.cnt,pac->msg.bookid);
	else
		flag = list_book::Get_list_book()->dec_book(pac->msg.cnt,pac->msg.bookname);
	return flag;
}

bool StockAdmin::bookquery(Pac* pac)
{
	return list_book::Get_list_book()->find_book(pac->res);
}

bool StockAdmin::load(Msg* msg)
{
	if(0 != strcmp(this->id,msg->id) || 0 != strcmp("admin",msg->password))
		return false;
	return true;
}

