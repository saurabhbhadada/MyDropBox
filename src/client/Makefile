all:
	g++ -g -std=c++11 -o client ../common/common.cpp client.cpp -L/usr/lib -lssl -lcrypto -lpthread -ldl

run:
	./client 127.0.0.1 ${port}
