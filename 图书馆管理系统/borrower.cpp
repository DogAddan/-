#include "borrower.h"
#include <cstdlib>
#include <cstring>
#include <fstream>
using namespace std;

Borrower::Borrower(const char* name,short age,char sex,const char* id,long tel):Person(name,age,sex,id,tel)
{
	Use u;
	cnt = -1;
	ifstream file("./Msg/use.dat",ios::in);
	while(1)
	{
		file.read((char*)&u,sizeof(Use));
		if(!file)
			break;
		cnt++;
		use[cnt] = u;
	}
	file.close();
}

// 还书
bool Borrower::in(Pac* pac)
{
	bool flag = false;
	Use* use;
	use = query_id(pac->msg.id,use);
	if(NULL == use)
		return flag;
	else
	{
		flag = use->out(pac);
		save();
	}
	return flag;
	
}

// 借书
bool Borrower::out(Pac* pac)
{
	bool flag = false;
	Use* use;
	use = query_id(pac->msg.id,use);
	if(NULL == use)
		return flag;
	else
	{
		flag = use->in(pac);
		save();
	}
	return flag;
}

// 添加用户
bool Borrower::adduse(Msg* msg)
{
	Use* newuse;
	newuse = query_id(msg->id,newuse);
	if(NULL == newuse)
	{
		for(int i = 0;i < 100;i++)
		{
			if(0 == atoi(use[i].id))
			{
				use[i].add(msg);
				cnt++;
				save();
				return true;
			}
		}
	}
	return false;
}
	
// 删除用户
bool Borrower::decuse(Pac* pac)
{
	bool flag = false;
	Use* olduse;
	olduse = query_id(pac->msg.id,olduse);
	if(NULL != olduse)
	{
		for(int i = 0;i < 100;i++)
		{
			if(0 == strcmp(olduse->id,use[i].id))
			{
				for(int j = 0;j < 7;j++)
				{
					if(use[i].get_booknum(j) != 0)
					{
						strcpy(pac->res,"\n还有书籍未归还,请归还后注销\n");
						return flag;
					}
				}
				flag = use[i].dec(pac);
				cnt--;
				save();
				return flag;
			}
		}
	}
	strcpy(pac->res,"\n用户不存在\n");
	return flag;
}

bool Borrower::fuzzyquery(Pac* pac)
{
	return list_book::Get_list_book()->fuzzy_query_book(pac->msg.bookname,pac->res);
}

bool Borrower::book_comment(Pac* pac)
{
//	return list_book::Get_list_book()->write_message(pac->msg.bookname,pac->res);
}

bool Borrower::show_comment(Pac* pac)
{
//	return list_book::Get_list_book()->show_message(pac->msg.bookname,pac->res);
}

// 根据身份证查找用户
Use* Borrower::query_id(const char* id,Use* backuse)
{
	for(int i = 0;i < 100;i++)
	{
		if(0 == strcmp(id,use[i].id))
		{
			backuse = &use[i];
			return backuse;
		}
	}
	return NULL;
}

// 根据姓名查找用户
Use* Borrower::query_name(const char* name,Use* backuse)
{
	for(int i = 0;i < 100;i++)
	{
		if(0 == strcmp(use[i].name,name))
		{
			backuse = &use[i];
			return backuse;
		}
	}
	return NULL;
}

// 借书员登录
bool Borrower::load(Msg* msg)
{
	if(0 != strcmp(this->id,msg->id) || 0 != strcmp("admin",msg->password))
		return false;
	return true;
}

// 用户登录
bool Borrower::use_query(Pac* pac)
{
	Use* use;
	use = query_id(pac->msg.id,use);
	if(NULL == use)
		return false;
	sprintf(pac->res,"\t%s\t%s\t%s\n","借书时间","书籍名称","书籍编号","是否逾期");
	for(int i = 0;i < 7;i++)
	{
		if(0 != use->get_booknum(i))
		{
			if(Timer::timers() - use->get_times(i) > 5)
			{
				sprintf(pac->res,"%s%s\t%s\t%d\t%c\n",pac->res,use->get_time(i),use->get_book_name(i),use->get_booknum(i),'*');
			}
			else
			{
				sprintf(pac->res,"%s%s\t%s\t%d\n",pac->res,use->get_time(i),use->get_book_name(i),use->get_booknum(i));
			}
		}
	}
	//use->recommend(pac);
	return true;
}

void Borrower::book_query(Pac* pac)
{
	list_book::Get_list_book()->find_book(pac->res);
}

bool Borrower::query(Pac* pac)
{
	memset(pac->res,0,sizeof(pac->res));
	sprintf(pac->res,"%s\t%s\t%s\t%s\n","姓名"," 身份证"," 性别","电话");
	for(int i = 0;i < 100;i++)
	{
		if(0 != atoi(use[i].id))
		{
			sprintf(pac->res,"%s%s\t%s\t%c\t%lu\n",pac->res,use[i].name,use[i].id,use[i].sex,use[i].tel);
		}
	}
	return true;
}

void Borrower::save()
{
	ofstream file("./Msg/use.dat",ios::out);
	for(int i = 0;i < 100;i++)
	{
		if(0 != atoi(use[i].id))
		{
			file.write((char*)&use,sizeof(use[i]));
		}
	}
	file.close();
}

