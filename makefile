all: pr

pr: main.o
	g++ main.o -o pr

main.o: main.cpp
	g++ -c main.cpp

