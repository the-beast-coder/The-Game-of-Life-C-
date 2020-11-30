#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <time.h>

int width;
int height;

int boardWidth;
int boardHeight;

clock_t prevTime;
int delay;

void render(void);
void getBoard();
void move();

std::vector<std::vector<bool>> board;

int main (int argc, char **argv) {
    boardHeight = 10;
    boardWidth = 10;

    width = 500;
    height = 500;
    delay = 1000; //1 second delay
    prevTime = clock();
    getBoard();

    //glut window initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);

    glutCreateWindow("The game of Life");

    glutDisplayFunc(render);
    glutMainLoop();

}

void render (void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPointSize(width/10);
    glBegin(GL_POINTS);
    
    if (clock() > prevTime + delay) {
        move();
        prevTime = clock();
    }
    for (int y = 0; y < boardHeight; y++) {
        for (int x = 0; x < boardWidth; x++) {
            if (board[y][x] == true) {
                glVertex2f(((float)x/boardWidth*2) - 0.9, ((float)y/boardHeight*2) - 0.9);
            }
        }
    }

    glEnd();
    glutSwapBuffers();
}

void getBoard () {

    std::ifstream file("board.txt");

    std::string line;

    for (int y = 0; y < boardHeight; y++) {
        getline(file, line);
        board.push_back({});

        for (int x = 0; x < boardWidth; x++) {
            char thisChar = line.at(x);
            if (thisChar == '1') {
                board[y].push_back(true);
                std::cout << "1";
            } else {
                board[y].push_back(false);
                std::cout << "0";
            }
        }
        std::cout << std::endl;
    }
    reverse(board.begin(), board.end());
}


void move () {

    for (int y = 0; y < boardHeight; y++) {
        for (int x = 0; x < boardWidth; x++) {
            uint16_t surroundingCells;
            if (x > 0 && board[y][x-1])
                surroundingCells++;
            if (x < boardWidth-1 && board[y][x+1])
                surroundingCells++;

            //vertical cells
            if (y > 0 && board[y-1][x])
                surroundingCells++;
            if (y < boardHeight-1 && board[y+1][x])
                surroundingCells++;

            //diagonal cells
            if (x > 0 && y > 0 && board[y-1][x-1])
                surroundingCells++;
            if (x > 0 && y < boardHeight-1 && board[y+1][x-1])
                surroundingCells++;
            if (x < boardWidth-1 && y > 0 && board[y-1][x+1])
                surroundingCells++;
            if (x < boardWidth-1 && y > boardHeight-1 && board[y+1][x+1])
                surroundingCells++;

            if (surroundingCells > 3 || surroundingCells < 2) {
                board[y][x] = false;
            } else if (surroundingCells == 3) {
                board[y][x] = true;
            }
        }
    }
}
