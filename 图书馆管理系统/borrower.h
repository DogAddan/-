#ifndef BORROWER_H
#define BORROWER_H
#include "person.h"
#include "struct.h"
#include "use.h"
#include "list_book.h"
class Borrower:public Person
{
	int cnt;
	Use use[100];
public:
	Borrower(const char* name,short age,char sex,const char* id,long tel);

	// 还书
	bool in(Pac* pac);
	
	// 借书
	bool out(Pac* pac);
	
	// 添加用户
	bool adduse(Msg* msg);

	// 删除用户	
	bool decuse(Pac* pac);

	// 模糊查询
	bool fuzzyquery(Pac* pac);

	// 书籍评论
	bool book_comment(Pac* pac);

	// 显示评论
	bool show_comment(Pac* pac);
	
	// 根据身份证查找用户
	Use* query_id(const char* id,Use* backuse);
	
	// 根据姓名查找用户
	Use* query_name(const char* name,Use* backuse);

	// 借书员登录
	bool load(Msg* msg);
	
	// 用户自己查询
	bool use_query(Pac* pac);
	
	// 查询书籍信息
	void book_query(Pac* pac);

	// 查询用户信息
	bool query(Pac* pac);

	// 存储
 	void save(void);
};
#endif // BORROWER_H
