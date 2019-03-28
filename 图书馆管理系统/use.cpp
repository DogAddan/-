#include "use.h"
#include <cstring>

Use::Use(const char* name,short age,char sex,const char* id,long tel):Person(name,age,sex,id,tel)
{
	memset(booknum,0,sizeof(booknum));
	memset(time,0,sizeof(time));
}

Use::Use()
{

}

bool Use::in(Pac* pac)
{
	bool flag = false;
	if(0 == pac->msg.bookid)
	{
		for(int i = 0;i < 7;i++)
		{
			if(0 == booknum[i])
			{
				booknum[i] = list_book::Get_list_book()->name_to_id(name);
				strcpy(book_name[i],name);
				Timer::timers(time[i]);
				times[i] = Timer::timers();
				flag = list_book::Get_list_book()->dec_book(1,booknum[i]);
				return flag;
			}
		}
	}
	else
	{
		for(int i = 0;i < 7;i++)
		{
			if(0 == booknum[i])
			{
				booknum[i] = pac->msg.bookid;
				strcpy(book_name[i],list_book::Get_list_book()->id_to_name(pac->msg.bookid));
				Timer::timers(time[i]);
				times[i] = Timer::timers();
				flag = list_book::Get_list_book()->dec_book(1,booknum[i]);
				return flag;
			}
		}
	}
	return flag;
}

bool Use::out(Pac* pac)
{
	bool flag = false;
	for(int i = 0;i < 7;i++)
	{
		if(pac->msg.bookid == booknum[i])
		{
			int day;
			char str[30];
			Timer::timers(str);
			sprintf(pac->res,"\n借书时间:%s\n\n还书时间:%s\n\n",time[i],str);
			flag = list_book::Get_list_book()->addend_book(1,booknum[i]);
			memset(time[i],0,sizeof(time[0]));
			memset(book_name[i],0,sizeof(book_name[0]));
			day = Timer::timers() - times[i];
			day /= 86400;
			day += 10;
			if(day > 7)
			{
				sprintf(pac->res,"%s逾期%d天归还,请缴纳%.2f￥\n",pac->res,day - 7,(day - 7)*1.0);
			}
			else
			{
				sprintf(pac->res,"\n%s按时归还,还书成功\n",pac->res);
			}
			booknum[i] = 0;
			return flag;
		}
	}
	return flag;
}

void Use::add(Msg* msg)
{
	strcpy(this->id,msg->id);
	strcpy(this->name,msg->name);
	this->sex = msg->sex;
	this->age = msg->age;
	this->tel = msg->tel;
	memset(booknum,0,sizeof(booknum));
	memset(time,0,sizeof(time));
	memset(book_name,0,sizeof(book_name));
	this->money = msg->money;
}

bool Use::dec(Pac* pac)
{
	sprintf(pac->res,"\n销户成功\n\n退还押金:%.2f￥",this->money);
	this->money = 0;
	memset(this->id,0,sizeof(this->id));
	memset(this->name,0,sizeof(this->name));
	this->sex = 0;
	this->age = 0;
	this->tel = 0;
	memset(booknum,0,sizeof(booknum));
	memset(time,0,sizeof(time));
	return true;
	memset(book_name,0,sizeof(book_name));
}

const char* Use::get_time(int index)
{
	return this->time[index];
}

int Use::get_booknum(int index)
{
	return this->booknum[index];
}

const char* Use::get_book_name(int index)
{
	return this->book_name[index];
}

int Use::get_times(int index)
{
	return this->times[index];
}
/*
void Use::recommend(Pac* pac)
{
	int max = 0;
	for(int i = 0;i < 7;i++)
	{
		if(times[i] > 0)
			max = i;
	}
}*/
