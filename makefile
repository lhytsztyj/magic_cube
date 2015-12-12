main: main.cpp
	g++ main.cpp -o main -O2

debug: main.cpp
	g++ main.cpp -o main -ggdb -Wall

test: main.cpp
	g++ main.cpp -o test -O2 -DTEST
