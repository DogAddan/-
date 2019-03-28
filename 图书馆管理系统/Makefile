all:
	g++ book.cpp -c
	g++ list_book.cpp -c
	g++ borrower.cpp -c
	g++ list.cpp -c
	g++ node.cpp -c
	g++ person.cpp -c
	g++ stockadmin.cpp -c
	g++ timer.cpp -c
	g++ use.cpp -c
	g++ clientMenu.cpp -c
	g++ client.cpp -c -o client_user.o -D USER
	g++ client.cpp -c -o client_admin.o -D MANA
	g++ main.cpp -c -o main_client.o -D CLIENT
	g++ main.cpp -c -o main_server.o -D SERVER
	g++ server.cpp -c
	g++ socket.cpp -c
	g++ tool.cpp -c
	g++ book.o list_book.o borrower.o list.o node.o person.o stockadmin.o timer.o use.o server.o main_server.o socket.o -o Server -D SERVER -lpthread
	g++ clientMenu.o main_client.o socket.o client_user.o tool.o -o Client_USER -lpthread
	g++ clientMenu.o main_client.o socket.o client_admin.o tool.o -o Client_ADMIN -lpthread
