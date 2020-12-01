everything:
	g++ -c main.cpp board.cpp
	g++ *.o -lglut -lGL -lGLU -lpthread
	./a.out
build:
	g++ -c main.cpp board.cpp
	g++ *.o -lglut -lGL -lGLU -lpthread
run:
	./a.out
