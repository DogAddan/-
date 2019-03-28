#ifndef STOCKADMIN_H
#define STOCKADMIN_H
#include "person.h"
#include "book.h"
#include "struct.h"
#include "list_book.h"
class StockAdmin:public Person
{
public:
	StockAdmin(const char* name,short age,char sex,const char* id,long tel);
	
	StockAdmin();
	
	// 添加新书籍
	bool newbook(Msg* msg);

	// 删除书籍
	bool deletebook(Msg* msg);

	// 书籍入库
	bool in(Pac* pac);

	// 书籍报销
	bool out(Pac* pac);

	// 查询书籍
	bool bookquery(Pac* pac);
	
	// 仓库员登录
	bool load(Msg* msg);
	
};

#endif // STOCKADMIN_H
