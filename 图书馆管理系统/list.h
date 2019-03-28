#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "node.h"


using namespace std;


class mList
{
private:
	//Node* head;


public:size_t count;
    //构造
    Node* tail;
    Node* head;
	mList(void);
    //析构
	~mList(void);
	//判断是否为空
	bool emptyList(void);
	//添加数据
    void addendData(TYPE data);
    //插入数据
    bool insertData(size_t index,TYPE data);
    //删除头
    bool deleteHead(void);
    //删除尾
    bool deleteTail(void);
    //删除数据(按值)
    bool deleteValueList(TYPE data);
    //删除数据(按位置)
    bool deleteIndexList(size_t index);
    //查找
    int findData(TYPE data);
    //取数
    TYPE getData(int index);
    //修改(按值)
    bool modifyValueList(TYPE oid_data,TYPE new_data);
    //修改(按位置)
    bool modifyIndexList(size_t index,TYPE data);
    //遍历
    void showList(void);
    //+data

};


#endif // LIST_H

