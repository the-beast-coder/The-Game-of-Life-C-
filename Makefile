everything:
	g++ -c src/*.cpp
	g++ *.o -lglut -lGL -lGLU -lpthread -o bin/a.out
	cd bin; ./a.out
build:
	g++ -c src/*.cpp
	g++ *.o -lglut -lGL -lGLU -lpthread -o bin/a.out
run:
	cd bin; ./a.out
