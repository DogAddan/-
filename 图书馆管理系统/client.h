#ifndef CLIENT_H
#define CLIENT_H

#include <cstdlib>
#include "clientMenu.h"
#include "socket.h"
#include "ctrlcur.h"
#include "struct.h"
#include "tool.h"

using namespace std;

class Client
{
    Socket* socket;
    pthread_t pid;
    Package pac;
    char buf[1024];

    /******功能函数******/
    //初始化Socket
    void initSocket(void);
    //数据收发
    void msgSendRecv(void);
    //清空Package结构体
    void clearPackage(void);
    //清空buf字符串
    void clearBuf(void);

    /******用户客户端******/
    //用户客户端界面
    void userClientQueryMenu(void);
    //用户客户端功能选择界面
    void userClientChoseMenu(void);
    //用户客户端评论功能界面
    void userClientCommentMenu(void);
    //用户客户端查询书籍评论功能界面
    void userClientQueryCommentMenu(void);

    //用户客户端功能选择
    void userClientChose(void);
    //用户客户端查询功能
    void userClientQuery(void);
    //用户客户端评论功能
    void userClientComment(void);
    //用户客户端查询书籍评论功能
    void userClientQueryComment(void);

    /******员工客户端******/
    //初始选择功能
    void workerClientStart(void);
    //仓库仓库管理员登录
    void stockAdminClientLoad(void);
    //借书员登录
    void borrowerClientLoad(void);
    //仓库管理员功能
    void stockAdminClientChose(void);
    //借书员功能
    void borrowerClientChose(void);

    /*****仓库管理员功能*****/
    //入库
    void purchaseBook(void);
    //出库
    void putoutBook(void);
    //添加新书
    void addNewBook(void);
	//删除书籍
	void deleteBook(void);
	//仓库管理员查询书籍
	void stockBookQuery(void);

    /*****借书管理员功能*****/
    //创建用户
    void createUse(void);
	//销户
	void destoryUse(void);
    //借书
    void borrowBook(void);
    //还书
    void returnBook(void);
    //借书员查询
    void borrowQuery(void);
    //书籍查询
    void bookQuery(void);

public:
    //构造(端口号,"IP地址")
    Client(u_int16_t port,const char* ipAddr);
    //析构
    ~Client(void);
    //客户端启动
    void start(void);
};


#endif //CLIENT_H
