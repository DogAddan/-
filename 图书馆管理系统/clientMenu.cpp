#include "clientMenu.h"

void ClientMenu::setTitle(const char *title)
{
    cout << title << endl;
    for (int i = 0;i < 10;++i)
    {
        cout << "-" << endl;
    }
}

void ClientMenu::setOptionBox(int num, const char *content)
{
    cout << "[" << num << "]" << content << endl;
}

void ClientMenu::setInputBox(const char *title)
{
    cout << title << "：" << endl;
}

void ClientMenu::setInputBox(const char *title, char type)
{

}

void ClientMenu::inInputBox(int num)
{
    MOVETO(x[num],y[num]);
    //Tool::getStr()
}

void ClientMenu::setButton(const char *title)
{

}

void ClientMenu::workerClientStartMenu(void)
{
    system("clear");
    cout << "图书管理系统(员工端)" << endl;
    cout << "---------------------" << endl;
    cout << "[1]仓库管理员登录" << endl;
    cout << "[2]借书员登录" << endl;
    cout << "[3]退出" << endl;
}

void ClientMenu::stockAdminClientLoadMenu(void)
{
    system("clear");
    cout << "仓库管理员登录" << endl;
    cout << "---------------------" << endl;
    cout << "账号：" << endl;
    cout << "密码：" << endl;
}

void ClientMenu::borrowerClientLoadMenu(void)
{
    system("clear");
    cout << "借书员登录" << endl;
    cout << "---------------------" << endl;
    cout << "账号：" << endl;
    cout << "密码：" << endl;
}

void ClientMenu::stockAdminClientChoseMenu(void)
{
    system("clear");
    cout << "仓库管理员功能选择" << endl;
    cout << "---------------------" << endl;
    cout << "[1]入库" << endl;
    cout << "[2]出库" << endl;
    cout << "[3]增加新书" << endl;
    cout << "[4]删除书籍" << endl;
    cout << "[5]查询书籍" << endl;
    cout << "[6]退出" << endl;
}

void ClientMenu::borrowerClientChoseMenu(void)
{
    system("clear");
    cout << "借书员功能选择" << endl;
    cout << "---------------------" << endl;
    cout << "[1]借书" << endl;
    cout << "[2]还书" << endl;
    cout << "[3]添加用户" << endl;
	cout << "[4]销户" << endl;
    cout << "[5]查询用户信息" << endl;
    cout << "[6]查询书籍信息" << endl;
    cout << "[7]退出" << endl;
}

void ClientMenu::purchaseBoookMenu(void)
{
    system("clear");
    cout << "入库" << endl;
    cout << "---------------------" << endl;
    cout << "书编号：" << endl;
    cout << "数量：" << endl;
}

void ClientMenu::putoutBockMenu(void)
{
    system("clear");
    cout << "出库" << endl;
    cout << "---------------------" << endl;
    cout << "书编号：" << endl;
    cout << "数量：" << endl;
}

//添加新书界面
void ClientMenu::addNewBookMenu(void)
{
    system("clear");
    cout << "添加新书" << endl;
    cout << "---------------------" << endl;
    cout << "书名：" << endl;
    cout << "作者：" << endl;
    cout << "类型：" << endl;
    cout << "价格：" << endl;
    cout << "数量：" << endl;
}

void ClientMenu::deleteBookMenu(void)
{
    system("clear");
    cout << "删除书籍" << endl;
    cout << "---------------------" << endl;
    cout << "书编号：" << endl;
}

void ClientMenu::stockBookQueryMenu(void)
{
    system("clear");
    cout << "仓库管理员查询书籍" << endl;
    cout << "---------------------" << endl;

}

void ClientMenu::createUseMenu(void)
{
    system("clear");
    cout << "添加用户" << endl;
    cout << "---------------------" << endl;
    cout << "姓名：" << endl;
    cout << "性别：" << endl;
    cout << "年龄：" << endl;
    cout << "身份证:" << endl;
    cout << "电话：" << endl;
    cout << "押金：" << endl;
}

void ClientMenu::destoryUseMenu(void)
{
	system("clear");
    cout << "添加用户" << endl;
    cout << "---------------------" << endl;
	cout << "身份证:" << endl;
}

void ClientMenu::borrowBookMenu(void)
{
    system("clear");
    cout << "借书" << endl;
    cout << "---------------------" << endl;
    cout << "身份证：" << endl;
    cout << "书编号：" << endl;
}

void ClientMenu::returnBookMenu(void)
{
    system("clear");
    cout << "还书" << endl;
    cout << "---------------------" << endl;
    cout << "身份证：" << endl;
    cout << "书编号：" << endl;
}

void ClientMenu::borrowQueryMenu(void)
{
    system("clear");
    cout << "借书员查询" << endl;
    cout << "---------------------" << endl;
}

void ClientMenu::bookQueryMenu(void)
{
    system("clear");
    cout << "书籍查询" << endl;
    cout << "---------------------" << endl;
}
