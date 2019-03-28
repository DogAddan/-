#ifndef USE_H
#define USE_H
#include "person.h"
#include "struct.h"
#include "timer.h"
#include "book.h"
#include "list.h"
#include "list_book.h"
class Use:public Person
{
	int booknum[7];
	char book_name[7][50];
	char time[7][30];
	int times[7];
	float money;
public:
	Use(const char* name,short age,char sex,const char* id,long tel);

	Use();

	// 借书
	bool in(Pac* pac);

	// 还书
	bool out(Pac* pac);
	
	// 添加用户
	void add(Msg* msg);

	// 删除用户
	bool dec(Pac* pac);

	// 返回时间信息
	const char* get_time(int index);

	// 返回书本信息
	int get_booknum(int index);

	// 返回书籍名称
	const char* get_book_name(int index);

	int get_times(int index);

	// 推荐
	//void recommend(Paa* pac);
};
#endif // USE_H
