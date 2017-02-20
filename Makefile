all: main.cpp iostream.h
	g++ -o test.bin main.cpp -std=c++11
clean: 
	rm -rf test.bin
