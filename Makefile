all: prog.o library.o
	g++ prog.o library.o -o prog -g

prog.o: prog.cpp
	g++ -c prog.cpp 

library.o: library.cpp
	g++ -c library.cpp

clean:
	rm -f *.o
	
