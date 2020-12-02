A program that runs the game of life :) - coded in C++

RIP John Conway.

Rules:
1) If a cell is next to more than 3 neighbours it dies because of overpopulation 
2) If a cell is next to less than 2 neighbours it dies because of underpopulation
3) If a spot on the board is next to exactly 3 cells it gets revived

These simple rules can create vast universes of simulations, if you want to see a really cool one, search for Bill Gosper's Glider Gun,

I used OpenGl to display the graphics and used C++ to code the project. I tried including multithreading into the calculations for the cells in the game to make it as efficient as possible, and by adding it into the project I did indeed make it approximately 1 and 1/3 faster than without singlethreading. In the future I might try using the GPU to help out with the calculations (by using CUDA or OpenCL). Currently it can run over 1000 generations of a 30 by 30 board in under 10 seconds. These results were recorded on a 6 core i7 9750H Cpu running at 2.40 GHZl. If you want to run the program and try it out for yourself feel free to run it yourself :). The dependencies used are GLEW, a basic OPENGL library that comes preinstalled with Linux (or you can install it yourself in other platforms). run the make file (which uses C++) or just run the built app, made for Linux.

Edit the board.txt file in rsrc to change the way the simulation will start of. (A quick way of filling the file with a board of 0s is by using the python file in the repo. If you want a cell to be alive at the start of the simulation, simply change the 0 to a 1

Edit the variables in the main.cpp function to change the desired board width and height.

Controls:
WASD for movement
Z for increasing simulation delay by 50 ms
X for decreasing simulation delay by 50 ms
EQUALS KEY to zoom in
SUBTRACT KEY to zoom out

Have fun!
