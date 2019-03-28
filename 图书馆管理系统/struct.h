#ifndef STRUCT_H
#define STRUCT_H

#define STOCKADMIN_LOAD			1
#define BORROWER_LOAD			2
#define USE_QUERY				3
#define PURCHASE_BOOK			4
#define PUTOUT_BOOK				5
#define CREATE_UES				6
#define BORROW_BOOK				7
#define RETURN_BOOK				8
#define BORROW_QUERY			9
#define ADD_NEW_BOOK			10
#define BOOK_QUERY				11
#define BOOK_DESTORY			12
#define STOCK_BOOK_QUERY		13
#define FIND_BOOK_ACCURATELY	14
#define COMMENT					15
#define USER_BOOK_QUERY			16
#define USE_DESTORY				17
typedef struct Message
{
	char name[20];			// 人名
	char id[20];			// 身份证
	char password[20];		// 密码
	char sex;				// 性别
	short age;				// 年龄
	long tel;				// 电话
	char bookname[50];		// 书名
	int bookid;				// 书编号
	char author[50];		// 作者
	char type[20];			// 书籍类型
	float money;			// 价钱
	int cnt;				// 数量	
}Msg;

typedef struct Package
{
	int flag;				// 操作方式
	Msg msg;
	char res[1024];			// 结果
}Pac;

#endif // STRUCT_H
