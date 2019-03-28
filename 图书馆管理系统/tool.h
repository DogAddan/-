#ifndef TOOL_H
#define TOOL_H

#include <cstdio>
#include <cstring>
#include <getch.h>

class Tool
{
public:
    //输入控制
    static char get_cmd(char start,char end);
    //限制输入
    static char* getStr(char* str,size_t size);
    //限制输入,上限删除
    static char* getStr(char* str,size_t size,char type);
    //清除输入输出缓冲区
    static void clear_stdin(void);
    //按任意键退出
    static void rand_key_exit(void);
};


#endif // TOOL_H

