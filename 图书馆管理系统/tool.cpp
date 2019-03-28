#include "tool.h"

//输入控制
char Tool::get_cmd(char start,char end)
{
    while(true)
    {
        char key = 0;
        key = getch();
        if(start <= key && key <= end)return key;
    }
}

//限制输入
char* Tool::getStr(char* str,size_t size)
{
    if(NULL == str) return str;

    clear_stdin();
    fgets(str,size,stdin);
    if(size-1 == strlen(str))
    {
        if('\n' == str[size-2])
            str[size-2] = '\0';
        else
            clear_stdin();
    }
    else
        str[strlen(str)-1] = '\0';

    return str;
}

//限制输入,上限删除
char* Tool::getStr(char* str,size_t size,char type)
{
    if(NULL == str) return str;

    clear_stdin();
    for(int i=0;i<size;i++)
    {
        str[i] =getch();
        if('\n' == str[i])
        {
            if(0 == i)
            {
                i--;
                continue;
            }
            str[i] = '\0';
            printf("\n");
            break;
        }
        else if(127 == str[i])
        {
            str[i] = '\0';
            if(0 == i)
            {
                i--;
                continue;
            }
            printf("\b \b");
            i-=2;
            continue;
        }
        else
        {
            if(0 == type)
            {
                printf("%c",str[i]);
            }
            else
            {
                printf("%c",type);
            }
        }
        if(i == size-1)
        {
            printf("\b \b");
            i--;
        }
    }
    return str;
}

//清除输入输出缓冲区
void Tool::clear_stdin(void)
{
    stdin->_IO_read_ptr = stdin->_IO_read_end;
}

//按任意键退出
void Tool::rand_key_exit()
{
    clear_stdin();
    printf("按任意键退出！");
    getch();
}
