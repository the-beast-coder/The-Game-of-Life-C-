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

int delay;

void render(void);
void getBoard();
void move();
void timer (int);

std::vector<std::vector<bool>> board;

int main (int argc, char **argv) {
    boardHeight = 10;
    boardWidth = 10;
    width = 500;
    height = 500;
    delay = 1000; //1 second delay
    getBoard();

    //glut window initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);

    glutCreateWindow("The game of Life");

    glutDisplayFunc(render);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();

}

void render (void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(width/boardWidth);
    glBegin(GL_POINTS);
    move();
    for (uint16_t y = 0; y < boardHeight; y++) {
        for (uint16_t x = 0; x < boardWidth; x++) {
            if (board[y][x]) {
                float thisX = 1.0 * x; //doing this to convert x to a float
                float thisY = 1.0 * y; //doing this to convert x to a float
                glVertex2f(thisX / boardWidth * 2 - 0.9, thisY / boardHeight * 2 - 0.9);
            }
        }
    }
    glEnd();
    glutSwapBuffers();
}

void move () {
    //enter move code here
    std::vector<std::vector<bool>> boardCopy = board;
    std::cout << "Hello" << std::endl;
    for (int y = 0; y < boardHeight; y++) {
        for (int x = 0; x < boardWidth; x++) {
            uint16_t surroundingCells = 0;
            //check for horizontal cells
            if (x > 0 && board[y][x-1]) {
               surroundingCells++;
            }
            if (x < boardWidth-1 && board[y][x+1]) {
               surroundingCells++;
            }

            //check for vertical cells
            if (y > 0 && board[y-1][x]) {
               surroundingCells++;
            }
            if (y < boardHeight-1 && board[y+1][x]) {
                surroundingCells++;
            }

            //check for diagonal cells
            if (y > 0 && x > 0 && board[y-1][x-1]) {
                surroundingCells++;
            }
            if (y > 0 && x < boardWidth-1 && board[y-1][x+1]) {
                surroundingCells++;
            }
            if (y < boardHeight-1 && x > 0 && board[y+1][x-1]) {
                surroundingCells++;
            }
            if (y < boardHeight-1 && x < boardWidth-1 && board[y+1][x+1]) {
                surroundingCells++;
            }


            if ((surroundingCells > 3 || surroundingCells < 2) && board[y][x])
                boardCopy[y][x] = false;
            else if (surroundingCells == 3 && !board[y][x])
                boardCopy[y][x] = true;
        }
    }
    board = boardCopy;
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

void timer (int) {
    glutPostRedisplay();
    glutTimerFunc(delay, timer, 0); //call the display func every x seconds
}
