all:
	g++ -g -std=c++11 -o server ../common/common.cpp ../DBManager/DBManager.cpp ../login/login.cpp ../register/register.cpp ../download/download.cpp ../upload/upload.cpp ../share/share.cpp ../sync/sync.cpp server.cpp -L/usr/lib -lssl -lcrypto -lpthread -ldl -lsqlite3

run:
	./server ${port}
