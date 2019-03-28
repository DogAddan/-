#include "server.h"

Server::Server(u_int16_t port, const char *ipAddr)
{
    socket = new Socket(port,ipAddr);
    stock = new StockAdmin("计佳诚",21,'m',"1996",123);
    borrower = new Borrower("谢申",21,'m',"1997",456);
    list_book::Get_list_book();
}

Server::~Server(void)
{
	pthread_mutex_destroy(&lock);
    delete socket;
	list_book::delete_list_book();
	printf("删除书籍链表------------------------\n");
    delete stock;
    delete borrower;
}

void Server::initSocket(void) {
    try {
        //创建socket对象
        socket->createSocket();
        //准备通信地址
        socket->initSocket();
        //绑定
        socket->bindSocket();
    }catch (const char* ex){
        cout << ex << endl;
		return;
    }
    //监听
    socket->listenSocket(5);
}

static void* threadCallBack(void* arg)
{
    ThreadMsg threadMsg = *(ThreadMsg*)arg;
    threadMsg.server->serverThread(threadMsg.acceptFd);
}

void Server::getAccept(void)
{
    while (true)
    {
        int acc = 0;
        cout << "等待连接！" << endl;
        try {
            acc = socket->acceptSocket();
        }catch (const char* ex){
            cout << ex << endl;
            break;
        }
        cout << "连接成功！" << endl;
        ThreadMsg threadMsg = {this,acc};

        //创建线程
        pthread_t pid;
        pthread_create(&pid,NULL,threadCallBack,&threadMsg);
    }
}

void sigint(int signum)
{
	delete server;
    puts("服务端关闭!");
    exit(signum);
}

void Server::signalDel(void)
{
    signal(SIGINT,sigint);
    signal(SIGQUIT,sigint);
}

void Server::initMutex(void)
{
	pthread_mutex_init(&lock,NULL);
}

void Server::start(void)
{
	signalDel();
    initSocket();
    getAccept();
}

void Server::serverThread(int acceptFd)
{

    while (true)
    {
        Package pac = {};
        try {
            socket->msgRecv(acceptFd,&pac);
        }catch (const char* ex){
            cout << ex << endl;
            break;
        }
        cout << pac.flag << endl;
        switch (pac.flag)
        {
            case STOCKADMIN_LOAD:
                stockAdminLoad(acceptFd,&pac.msg);
                break;
            case BORROWER_LOAD:
                borrowerLoad(acceptFd,&pac.msg);
                break;
            case USE_QUERY:
                useQuery(acceptFd,&pac);
                break;
            case PURCHASE_BOOK:
                purchaseBook(acceptFd,&pac);
                break;
            case PUTOUT_BOOK:
                putoutBook(acceptFd,&pac);
                break;
            case CREATE_UES:
                createUse(acceptFd,&pac.msg);
                break;
            case BORROW_BOOK:
                borrowBook(acceptFd,&pac);
                break;
            case RETURN_BOOK:
                returnBook(acceptFd,&pac);
                break;
            case BORROW_QUERY:
                borrowQuery(acceptFd,&pac);
                break;
            case ADD_NEW_BOOK:
                addNewBook(acceptFd,&pac.msg);
                break;
            case BOOK_QUERY:
                bookQuery(acceptFd,&pac);
                break;
			case STOCK_BOOK_QUERY:
				stockBookQuery(acceptFd,&pac);
				break;
			case BOOK_DESTORY:
				bookDestory(acceptFd,&pac.msg);
				break;
			case FIND_BOOK_ACCURATELY:
				findBookAccurately(acceptFd,&pac);
				break;
			case COMMENT:
				bookComment(acceptFd,&pac);
				break;
			case USER_BOOK_QUERY:
				userBookQuery(acceptFd,&pac);
				break;
			case USE_DESTORY:
				destoryUse(acceptFd,&pac);
				break;
            default:break;
        }
    }
}

void Server::stockAdminLoad(int acceptFd,Message* msg)
{
	pthread_mutex_lock(&lock);
    //库存管理员登录
    if(stock->load(msg))
    {
        socket->msgSend(acceptFd,"登录成功");
    }
    else
    {
		socket->msgSend(acceptFd,"库存管理员失败");
    }
	pthread_mutex_unlock(&lock);
}

void Server::borrowerLoad(int acceptFd,Message* msg)
{
	pthread_mutex_lock(&lock);
    //借书员登录
    if(borrower->load(msg))
    {
        socket->msgSend(acceptFd,"登录成功");
    }
    else
    {
        socket->msgSend(acceptFd,"借书员登录失败");
    }
	pthread_mutex_unlock(&lock);
}

void Server::useQuery(int acceptFd,Package* pac)
{
	pthread_mutex_lock(&lock);
    //用户登录
    if(borrower->use_query(pac))
    {
        socket->msgSend(acceptFd,pac->res);
    }
    else
    {
        socket->msgSend(acceptFd,"用户登录失败");
    }
	pthread_mutex_unlock(&lock);
}

void Server::purchaseBook(int acceptFd,Package* pac)
{
	pthread_mutex_lock(&lock);
    if(stock->in(pac))
    {
        socket->msgSend(acceptFd,"入库成功");
    }
    else
    {
        socket->msgSend(acceptFd,"入库失败");
    }
	pthread_mutex_unlock(&lock);
}

void Server::putoutBook(int acceptFd,Package* pac)
{
	pthread_mutex_lock(&lock);
    if(stock->out(pac))
    {
        socket->msgSend(acceptFd,"出库成功");
    }
    else
    {
        socket->msgSend(acceptFd,"出库失败");
    }
	pthread_mutex_unlock(&lock);
}

void Server::createUse(int acceptFd,Message* msg)
{
	pthread_mutex_lock(&lock);
    if(borrower->adduse(msg))
    {
        socket->msgSend(acceptFd,"创建用户成功");
    }
    else
    {
        socket->msgSend(acceptFd,"创建用户失败");
    }
	pthread_mutex_unlock(&lock);
}

void Server::borrowBook(int acceptFd,Package* pac)
{
	pthread_mutex_lock(&lock);
    if(borrower->out(pac))
    {
        socket->msgSend(acceptFd,"借书成功");
    }
    else
    {
       socket->msgSend(acceptFd,"借书失败");
    }
	pthread_mutex_unlock(&lock);
}

void Server::returnBook(int acceptFd,Package* pac)
{
	pthread_mutex_lock(&lock);
    if(borrower->in(pac))
    {
        socket->msgSend(acceptFd,pac->res);
    }
    else
    {
    	socket->msgSend(acceptFd,"还书失败");
    }
	pthread_mutex_unlock(&lock);
}

void Server::borrowQuery(int acceptFd,Package* pac)
{
	pthread_mutex_lock(&lock);
    if(borrower->query(pac))
    {
        socket->msgSend(acceptFd,pac->res);
    }
    else
    {
   	   socket->msgSend(acceptFd,"查询失败");
    }
	pthread_mutex_unlock(&lock);
}

void Server::addNewBook(int acceptFd,Message* msg)
{	
	pthread_mutex_lock(&lock);
    if(stock->newbook(msg))
    {
        socket->msgSend(acceptFd,"成功");
    }
    else
    {
        socket->msgSend(acceptFd,"失败");
    }
	pthread_mutex_unlock(&lock);
}

void Server::bookQuery(int acceptFd, Package* pac)
{
	pthread_mutex_lock(&lock);
    borrower->book_query(pac);
    socket->msgSend(acceptFd,pac->res);
	pthread_mutex_unlock(&lock);
}
void Server::stockBookQuery(int acceptFd,Package* pac)
{
	pthread_mutex_lock(&lock);
	stock->bookquery(pac);
	socket->msgSend(acceptFd,pac->res);
	pthread_mutex_unlock(&lock);
}

void Server::bookDestory(int acceptFd,Message* msg)
{
	pthread_mutex_lock(&lock);
	if(stock->deletebook(msg))
	{	
		socket->msgSend(acceptFd,"删除成功");
	}
	else
	{
		socket->msgSend(acceptFd,"删除失败");
	}
	pthread_mutex_unlock(&lock);
}

void Server::findBookAccurately(int acceptFd,Package* pac)
{
	pthread_mutex_lock(&lock);
	borrower->fuzzyquery(pac);
	socket->msgSend(acceptFd,pac->res);
	pthread_mutex_unlock(&lock);
}

void Server::bookComment(int acceptFd,Package* pac)
{
	pthread_mutex_lock(&lock);
	if(borrower->book_comment(pac))
	{
		socket->msgSend(acceptFd,"评论成功");
	}
	else
	{
		socket->msgSend(acceptFd,"评论失败");
	}
	pthread_mutex_unlock(&lock);
}

void Server::userBookQuery(int acceptFd,Package*pac)
{
	pthread_mutex_lock(&lock);
	if(borrower->show_comment(pac))
	{
		socket->msgSend(acceptFd,pac->res);
	}
	else
	{
		socket->msgSend(acceptFd,"查询失败");
	}
	pthread_mutex_unlock(&lock);
}

void Server::destoryUse(int acceptFd,Package* pac)
{
	pthread_mutex_lock(&lock);
	borrower->decuse(pac);
	socket->msgSend(acceptFd,pac->res);
	pthread_mutex_unlock(&lock);
	
}
