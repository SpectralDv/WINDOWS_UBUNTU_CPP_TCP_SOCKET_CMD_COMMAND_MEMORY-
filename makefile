
all: main

main: main.o 
	g++ main.o -o main -lws2_32 -lpthread

main.o: main.cpp 
	g++ -c main.cpp -o main.o 

