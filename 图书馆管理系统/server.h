#ifndef SERVER_H
#define SERVER_H

#include "socket.h"
#include "struct.h"
#include "stockadmin.h"
#include "borrower.h"
#include <pthread.h>
#include <csignal>

class Server
{
	StockAdmin* stock;
	Borrower* borrower;
    Socket* socket;
	pthread_mutex_t lock;

	//初始化信号捕获
    void signalDel(void);
	//初始化互斥锁
	void initMutex(void);
    //初始化Socket
    void initSocket(void);
    //获取accept
    void getAccept(void);
    //库存管理登录
    void stockAdminLoad(int acceptFd,Message* msg);
    //借书员登录
    void borrowerLoad(int acceptFd,Message* msg);
    //用户登录
    void useQuery(int acceptFd,Package* pac);
	//用户评论
	void bookComment(int acceptFd,Package* pac);
	//显示评论
	void userBookQuery(int acceptFd,Package* pac);
    //入库
    void purchaseBook(int acceptFd,Package* pac);
    //出库
    void putoutBook(int acceptFd,Package* pac);
    //创建用户
    void createUse(int acceptFd,Message* msg);
	//销户
	void destoryUse(int acceptFd,Package* pac);
    //借书
    void borrowBook(int acceptFd,Package* pac);
    //还书
    void returnBook(int acceptFd,Package* pac);
    //借书员查询
    void borrowQuery(int acceptFd,Package* pac);
	//借书员模糊查询
	void findBookAccurately(int acceptFd,Package* pac);
    //添加书
    void addNewBook(int acceptFd,Message* msg);
    //查询书籍
    void bookQuery(int acceptFd,Package* pac);
	//仓库查看书籍
	void stockBookQuery(int acceptFd,Package* pac);
	//删除书籍
	void bookDestory(int acceptFd,Message* msg);
public:
    //
    Server(u_int16_t port,const char* ipAddr);
    //
    ~Server(void);
    //服务器启动
    void start(void);
    //线程
    void serverThread(int acceptFd);
};

struct ThreadMsg
{
    Server* server;
    int acceptFd;
};

extern Server* server;

#endif //SERVER_H
