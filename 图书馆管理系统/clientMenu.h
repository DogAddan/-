#ifndef CLIENTMENU_H
#define CLIENTMENU_H

#include <iostream>
#include <cstdlib>
#include "tool.h"
#include "ctrlcur.h"
using namespace std;

class ClientMenu
{
    int line;
    int x[10];
    int y[20];
public:
    //设置标题
    void setTitle(const char* title);
    //设置选项框
    void setOptionBox(int num, const char* content);
    //设置输入框
    void setInputBox(const char* title);
    void setInputBox(const char* title,char type);
    //输入框输入
    void inInputBox(int num);
    //设置按钮
    void setButton(const char* title);

    //初始选择界面
    void workerClientStartMenu(void);
    //仓库管理员登录界面
    void stockAdminClientLoadMenu(void);
    //借书员登录界面
    void borrowerClientLoadMenu(void);
    //仓库管理员功能界面
    void stockAdminClientChoseMenu(void);
    //借书员功能界面
    void borrowerClientChoseMenu(void);

    //入库界面
    void purchaseBoookMenu(void);
    //出库界面
    void putoutBockMenu(void);
    //添加新书界面
    void addNewBookMenu(void);
    //删除书籍界面
    void deleteBookMenu(void);
    //仓库管理员查询书籍界面
    void stockBookQueryMenu(void);

    //创建用户界面
    void createUseMenu(void);
	//销户界面
	void destoryUseMenu(void);
    //借书界面
    void borrowBookMenu(void);
    //还书界面
    void returnBookMenu(void);
    //借书员查询界面
    void borrowQueryMenu(void);
    //书籍查询界面
    void bookQueryMenu(void);
};


#endif //CLIENTMENU_H
