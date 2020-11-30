everything:
	g++ -c main.cpp
	g++ *.o -lglut -lGL -lGLU
	./a.out
build:
	g++ -c main.cpp
	g++ *.o -lglut -lGL -lGLU
run:
	./a.out
