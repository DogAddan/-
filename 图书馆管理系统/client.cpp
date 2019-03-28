#include "client.h"

//构造(端口号,"IP地址")
Client::Client(u_int16_t port, const char *ipAddr)
{
    socket = new Socket(port,ipAddr);
    pid = 0;
}

//析构
Client::~Client(void)
{
    delete socket;
}

//初始化Socket
void Client::initSocket(void)
{
	system("clear");
	//记录连接次数
	int count = 1;
	//隐藏光标
	HIDE_CURSOR();
	while(true)
	{
		try {
		    //创建socket对象
		    socket->createSocket();
		    //准备通信地址
		    socket->initSocket();
		    //连接
		    socket->connectSocket();
		}catch (const char* ex){
		    cout << ex << endl;
			cout << "10s后尝试重连..." << endl;
			MOVEUP(1);
			for(int i=9;i>=0;i--)
			{
				sleep(1);
				fflush(stdout);
				cout << "0" << i;
				MOVELEFT(2);
			}
			cout << "开始尝试第" << count++ << "重连..." << endl;
			sleep(1);
			if(4 == count)
            {
			    cout << "服务器连接失败，请重启系统再次尝试" << endl;
                exit(0);
            }
			continue;
		}
		break;
	}
	cout << "连接成功！" << endl;
	sleep(1);
}

void Client::msgSendRecv(void)
{
    while(true)
    {
        try{
            socket->msgSend(&pac);
            socket->msgRecv(buf);
			break;
        }catch(const char* ex){
            cout << "与服务器断开连接" << endl;
            sleep(1);
            try{
                initSocket();
            }catch(const char* ex){
                cout << ex << endl;
            }
        }
    }
}

void Client::clearPackage(void)
{
    memset(&pac,'\0', sizeof(Package));
}

void Client::clearBuf(void)
{
    memset(buf,'\0',1024);
}

//#define USER
//#define MANA
//客户端启动
void Client::start(void)
{

    initSocket();

#ifdef USER
    userClientChose();
#endif

#ifdef MANA
    workerClientStart();
#endif
}

void* threadCallBack(void*)
{
    char str[11][4] = {{"欢"},{"迎"},{"使"},{"用"},{"图"},{"书"},{"管"},{"理"},{"系"},{"统"},{"！"}};
    int start = 0;
	MOVETO(1,1);
    while(1)
    {
        printf("|\033[31m");
        for(int i=start;i<11;i++)cout << str[i];
        for(int i=0;i<start;i++)cout << str[i];
        start++;
        if(11 == start)start = 0;
        printf("\033[0m|\n");
        sleep(1);
        CLEAR_UP_LINE(1);
    }
}

void Client::userClientQueryMenu(void)
{
    system("clear");
	//HIDE_CURSOR();
    //MOVETO(2,1);
    cout << "用户登录" << endl;
    cout << "-------------" << endl;
    cout << "身份证号：";
	//创建线程
    //pthread_create(&pid,NULL,threadCallBack,0);
}

void Client::userClientCommentMenu(void)
{
    system("clear");
    //HIDE_CURSOR();
    //MOVETO(2,1);
    cout << "评论" << endl;
    cout << "-------------" << endl;
    cout << "书名：" << endl;
    cout << "评论：" << endl;
    //创建线程
    //pthread_create(&pid,NULL,threadCallBack,0);
}

void Client::userClientQueryCommentMenu(void)
{
    system("clear");
    //HIDE_CURSOR();
    //MOVETO(2,1);
    cout << "查询书籍" << endl;
    cout << "-------------" << endl;
    cout << "书名：" << endl;
    //创建线程
    //pthread_create(&pid,NULL,threadCallBack,0);
}

void Client::userClientChoseMenu(void)
{
    system("clear");
    HIDE_CURSOR();
    MOVETO(2,1);
    cout << "用户功能选择" << endl;
    cout << "---------------" << endl;
    cout << "[1]查询" << endl;
    cout << "[2]评论" << endl;
    cout << "[3]查询书籍" << endl;
    //创建线程
    pthread_create(&pid,NULL,threadCallBack,0);
}

void Client::userClientChose(void)
{
    while (true)
    {
        userClientChoseMenu();
        switch (Tool::get_cmd('1','3'))
        {
            case '1' :
                //查询
                userClientQuery();
                break;
            case '2' :
                //评论
                userClientComment();
                break;
            case '3' :
                //查看书籍评论
                userClientQueryComment();
                break;
            default:
                break;
        }
        //任意键退出
        Tool::rand_key_exit();
    }
}

void Client::userClientQuery(void)
{
    userClientQueryMenu();
    //取消线程
    pthread_cancel(pid);
    //移动光标
    MOVETO(3,11);
    //显示光标
    SHOW_CURSOR();
    //清空
    clearPackage();
    clearBuf();
    //输入身份证
    Tool::getStr(pac.msg.id,20,0);
    //改变标志位为用户查询
    pac.flag = USE_QUERY;
    //收发数据
    msgSendRecv();
    //显示接收的数据
    cout << buf << endl;
}

void Client::userClientComment(void)
{
    userClientCommentMenu();
    //取消线程
    pthread_cancel(pid);
    //显示光标
    SHOW_CURSOR();
    //清空
    clearPackage();
    clearBuf();
    //输入书名
    do{
        MOVETO(3,7);
        Tool::getStr(pac.msg.bookname,20);
    }while(0 == strcmp(pac.msg.bookname,"\0"));
    //输入评论
    do{
        MOVETO(4,7);
        Tool::getStr(pac.res,1024);
    }while(0 == strcmp(pac.res,"\0"));
    //改变标志位为评论
    pac.flag = COMMENT;
    //收发数据
    msgSendRecv();
    //显示接收的数据
    cout << buf << endl;
}

void Client::userClientQueryComment(void)
{
    userClientQueryCommentMenu();
    //取消线程
    pthread_cancel(pid);
    //显示光标
    SHOW_CURSOR();
    //清空
    clearPackage();
    clearBuf();
    //输入书名
    do{
        MOVETO(3,7);
        Tool::getStr(pac.msg.bookname,20);
    }while(0 == strcmp(pac.msg.bookname,"\0"));
    //改变标志位为用户查询书籍
    pac.flag = USER_BOOK_QUERY;
    //收发数据
    msgSendRecv();
    //显示接收的数据
    cout << buf << endl;
}

void Client::workerClientStart(void)
{
    while(true)
    {
        ClientMenu clientMenu;
        clientMenu.workerClientStartMenu();

		SHOW_CURSOR();

        switch (Tool::get_cmd('1','3'))
        {
            case '1' :
                stockAdminClientLoad();
                break;
            case '2' :
                borrowerClientLoad();
                break;
            case '3' :
                return;
            default:break;
        }
    }
}

void Client::stockAdminClientLoad(void)
{
    ClientMenu clientMenu;
    clientMenu.stockAdminClientLoadMenu();
	//清空
    clearPackage();
    clearBuf();
	//输入账号
    MOVETO(3,7);
    Tool::getStr(pac.msg.id,20,0);
	//输入密码
    MOVETO(4,7);
    Tool::getStr(pac.msg.password,20,'*');
	//改变标志位为仓库管理员登录
    pac.flag = STOCKADMIN_LOAD;
	//收发数据
    msgSendRecv();
	//显示接收的数据
    cout << buf << endl;
    sleep(1);
    if(0 == strcmp(buf,"登录成功"))
    {
        stockAdminClientChose();
    }
}

void Client::borrowerClientLoad(void)
{
    ClientMenu clientMenu;
    clientMenu.borrowerClientLoadMenu();
	//清空
    clearPackage();
    clearBuf();
	//输入账号
    MOVETO(3,7);
    Tool::getStr(pac.msg.id,20,0);
	//输入密码
    MOVETO(4,7);
    Tool::getStr(pac.msg.password,20,'*');
	//改变标志位为借书员登录
    pac.flag = BORROWER_LOAD;
    //收发数据
    msgSendRecv();
	//显示接收的数据
    cout << buf << endl;
    sleep(1);
    if(0 == strcmp(buf,"登录成功"))
    {
        borrowerClientChose();
    }
}

void Client::stockAdminClientChose(void)
{
    while(true)
    {
        ClientMenu clientMenu;
        clientMenu.stockAdminClientChoseMenu();
        switch (Tool::get_cmd('1','6'))
        {
            case '1' :
                purchaseBook();
                break;
            case '2' :
                putoutBook();
                break;
            case '3' :
                addNewBook();
                break;
			case '4':
				deleteBook();
				break;
			case '5':
				stockBookQuery();
				break;
            case '6' :
                return;
            default:break;
        }
		Tool::rand_key_exit();
    }
}

void Client::borrowerClientChose(void)
{
    while(true)
    {
        ClientMenu clientMenu;
        clientMenu.borrowerClientChoseMenu();
        switch (Tool::get_cmd('1','7'))
        {
            case '1' :
                borrowBook();
                break;
            case '2' :
                returnBook();
                break;
            case '3' :
                createUse();
                break;
			case '4' :
                destoryUse();
                break;
            case '5' :
                borrowQuery();
                break;
            case '6' :
                bookQuery();
                break;
            case '7' :
                return;
            default:break;
        }
		Tool::rand_key_exit();
    }
}

void Client::purchaseBook(void)
{
	//显示
    ClientMenu clientMenu;
    clientMenu.purchaseBoookMenu();
    //清空
    clearPackage();
    clearBuf();
	//输入书籍ID	
    MOVETO(3,9);
    char str[20] = {};
    Tool::getStr(str,20,0);
	pac.msg.bookid = atoi(str);
	//输入数量
    MOVETO(4,7);
    Tool::getStr(str,10,0);
    pac.msg.cnt = atoi(str);
	//改变标志位为入库
    pac.flag = PURCHASE_BOOK;
    //收发数据
    msgSendRecv();
	//显示接收的数据
    cout << buf << endl;
}

void Client::putoutBook(void)
{
    ClientMenu clientMenu;
    clientMenu.putoutBockMenu();
	//清空
    clearPackage();
    clearBuf();
	//输入书籍ID
    MOVETO(3,9);
    char str[20] = {};
    Tool::getStr(str,20,0);
	pac.msg.bookid = atoi(str);
	//输入数量
    MOVETO(4,7);
    Tool::getStr(str,10,0);
    pac.msg.cnt = atoi(str);
	//改变标志位为出库
    pac.flag = PUTOUT_BOOK;
    //收发数据
    msgSendRecv();
	//显示接收的数据
    cout << buf << endl;
}

//添加新书
void Client::addNewBook(void)
{
    ClientMenu clientMenu;
    clientMenu.addNewBookMenu();
	//清空
    clearPackage();
    clearBuf();
	//输入书名
    do{
        MOVETO(3,7);
        Tool::getStr(pac.msg.bookname,20);
    }while(0 == strcmp(pac.msg.bookname,"\0"));
	//输入作者
    do{
        MOVETO(4,7);
        Tool::getStr(pac.msg.author,20);
    }while(0 == strcmp(pac.msg.author,"\0"));
	//输入类型
	do{
    	MOVETO(5,7);
    	Tool::getStr(pac.msg.type,20);
	}while(0 == strcmp(pac.msg.type,"\0"));
	//输入金额
    MOVETO(6,7);
	char str[20];
    Tool::getStr(str,10,0);
    pac.msg.money = atof(str);
	//输入数量
    MOVETO(7,7);
    Tool::getStr(str,10,0);
    pac.msg.cnt = atoi(str);
	//改变标志位为添加书籍
    pac.flag = ADD_NEW_BOOK;
    //收发数据
    msgSendRecv();
	//显示接收的数据
    cout << buf << endl;
}

void Client::deleteBook(void)
{
    ClientMenu clientMenu;
    clientMenu.deleteBookMenu();
	//清空
    clearPackage();
    clearBuf();
	//输入书籍ID
    MOVETO(3,9);
    char str[20] = {};
    Tool::getStr(str,10,0);
    pac.msg.bookid = atoi(str);
	//改变标志位为删除书籍
    pac.flag = BOOK_DESTORY;
    //收发数据
    msgSendRecv();
	//显示接收的数据
    cout << buf << endl;
}

void Client::stockBookQuery(void)
{
    ClientMenu clientMenu;
    clientMenu.stockBookQueryMenu();
	//清空
    clearPackage();
    clearBuf();
	//改变标志位为仓管书籍查询
    pac.flag = STOCK_BOOK_QUERY;
    //收发数据
    msgSendRecv();
	//显示接收的数据
    cout << buf << endl;
}
void Client::createUse(void)
{
    ClientMenu clientMenu;
    clientMenu.createUseMenu();
	//清空
    clearPackage();
    clearBuf();
	//输入姓名
    do{
        MOVETO(3,7);
        Tool::getStr(pac.msg.name,20);
    }while(0 == strcmp(pac.msg.name,"\0"));
	//输入性别
    MOVETO(4,7);
    char str[20] = {};
    Tool::getStr(str,2,0);
    pac.msg.sex = str[0];
	//输入年龄
    MOVETO(5,7);
    Tool::getStr(str,4,0);
    pac.msg.age = (short)atoi(str);
	//输入身份证
    MOVETO(6,9);
    Tool::getStr(pac.msg.id,20,0);
	//输入电话号码
    MOVETO(7,7);
    Tool::getStr(str,11,0);
    pac.msg.tel = atol(str);
	//输入金额
    MOVETO(8,7);
    Tool::getStr(str,10,0);
    pac.msg.money = atof(str);
	//改变标志位为创建用户
    pac.flag = CREATE_UES;
    //收发数据
    msgSendRecv();
	//显示接收的数据
    cout << buf << endl;
}

void Client::destoryUse(void)
{
	ClientMenu clientMenu;
    clientMenu.destoryUseMenu();
	//清空
    clearPackage();
    clearBuf();
	//输入身份证
    MOVETO(3,9);
    Tool::getStr(pac.msg.id,20,0);
	//改变标志位为创建用户
    pac.flag = USE_DESTORY;
    //收发数据
    msgSendRecv();
	//显示接收的数据
    cout << buf << endl;
}

void Client::borrowBook(void)
{
    ClientMenu clientMenu;
    clientMenu.borrowBookMenu();
	//清空
    clearPackage();
    clearBuf();
	//输入身份证
    MOVETO(3,9);
    Tool::getStr(pac.msg.id,20,0);
	//书籍ID
    MOVETO(4,9);
	char str[20] = {};
    Tool::getStr(str,20,0);
	pac.msg.bookid = atoi(str);
	//改变标志位为借书
    pac.flag = BORROW_BOOK;
    //收发数据
    msgSendRecv();
	//显示接收的数据
    cout << buf << endl;
}

void Client::returnBook(void)
{
    ClientMenu clientMenu;
    clientMenu.returnBookMenu();
	//清空
    clearPackage();
    clearBuf();
	//输入身份证
    MOVETO(3,9);
    Tool::getStr(pac.msg.id,20,0);
	//输入书籍ID
    MOVETO(4,9);
    char str[20] = {};
    Tool::getStr(str,20);
	pac.msg.bookid = atoi(str);
	//改变标志位为还书
    pac.flag = RETURN_BOOK;
    //收发数据
    msgSendRecv();
	//显示接收的数据
    cout << buf << endl;
}

void Client::borrowQuery(void)
{
    ClientMenu clientMenu;
    clientMenu.borrowQueryMenu();
	//清空
    clearPackage();
    clearBuf();
	//改变标志位为借书员用户信息查询
    pac.flag = BORROW_QUERY;
    //收发数据
    msgSendRecv();
	//显示接收的数据
    cout << buf << endl;
	//
    cout << "是否查询详细信息(y/n)" << endl;
	//
    char ch = 0;
    cin >> ch;
	//
    if('y' == ch)
    {
		//清空
        clearPackage();
        clearBuf();
		//输入身份证
        cout << "输入身份证:" << endl;
        Tool::getStr(pac.msg.id,20,0);
		//改变标志位为用户信息查询
        pac.flag = USE_QUERY;
        //收发数据
        msgSendRecv();
		//显示接收的数据
        cout << buf << endl;
    }
}

void Client::bookQuery(void)
{
    ClientMenu clientMenu;
    clientMenu.bookQueryMenu();
	//清空
    clearPackage();
    clearBuf();
	//改变标志位为借书员书籍信息查询
    pac.flag = BOOK_QUERY;
    //收发数据
    msgSendRecv();
	//显示接收的数据
	cout << buf << endl;
	//
	cout << "是否查询详细信息(y/n)" << endl;
	//
    char ch = 0;
    cin >> ch;
	//
    if('y' == ch)
    {
		//清空
        clearPackage();
        clearBuf();
		//
        cout << "输入书名(支持模糊查询):";
		//输入书名(支持模糊查询)
        do{
        	Tool::getStr(pac.msg.bookname,20);
    	}while(0 == strcmp(pac.msg.bookname,"\0"));
		//改变标志位为书籍详细信息查询
        pac.flag = FIND_BOOK_ACCURATELY;
        //收发数据
        msgSendRecv();
		//显示接收的数据
        cout << buf << endl;
    }
}
