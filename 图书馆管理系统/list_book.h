#ifndef LIST_BOOK_H
#define LIST_BOOK_H
#include"book.h"
#include"list.h"
class list_book
{
    public:
        list_book();
        ~list_book();

        mList* Getlist() { return List; }
        void Setlist(mList* val) { List = val; }
        static list_book* Get_list_book(void)
        {
            if(NULL==get_list_book)
            {
                get_list_book=new list_book;
            }
            return get_list_book;
        }
		static void delete_list_book(void)
		{
			delete get_list_book;
		}

        bool create_book(char* name,char* author,char* type,int number,int id,float money);
        char* fuzzy_query_book(const char* name,char* book);
        bool delete_book(int id);
        char* find_book(char* book);
        bool find_book(const char* name,char* book);
        bool find_book(int id,char* book);
        char* id_to_name(int id);
        int name_to_id(char* name);
        bool dec_book(int number,int id);
        bool dec_book(int number,char* name);
        bool addend_book(int number,char* name);
        bool addend_book(int number,int id);
        void create_book(char* name,char* author,char* type,int number,float money);
    protected:

    private:
        static class list_book* get_list_book;
        mList* List;
};

#endif // LIST_BOOK_H
