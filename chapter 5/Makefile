all: a.o a1.o a2.o
	g++ -o all a.o a1.o a2.o

a.o: a1.h a2.h
	g++ -c -g -std=c++11 a.cpp

a1.o: a1.h
	g++ -c -g -std=c++11 a1.cpp

a2.o: a2.h
	g++ -c -g -std=c++11 a2.cpp
