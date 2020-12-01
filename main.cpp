#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <chrono>
#include <thread>

struct Vector2i {
    uint16_t x;
    uint16_t y;
    Vector2i (uint16_t thisX, uint16_t thisY) {
        x = thisX;
        y = thisY;
    }
};

int width;
int height;

extern int boardWidth;
extern int boardHeight;

extern std::vector<std::vector<bool>> board;
extern std::vector<std::vector<bool>> boardCopy; //boardCopy is used to help with the manipulation of the game of life board

std::chrono::time_point<std::chrono::steady_clock> prevTime;
int delay;
bool shouldMove;
uint32_t generation;

float cameraOffset [2] = {0, 0};
float zoom = 1;

void render(void);

void getBoard();
void calculateRow(uint16_t y);
void calculateCell (uint16_t x, uint16_t y);

void moveMultithread();
void timer (int);
void keyboard (unsigned char c, int x, int y);

int main (int argc, char **argv) {
    boardHeight = 30;
    boardWidth = 30;
    width = 500;
    height = 500;

    delay = 1000;
    prevTime = std::chrono::steady_clock::now();


    getBoard();

    //glut window initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);

    glutCreateWindow("The game of Life");

    glutDisplayFunc(render);
    glutTimerFunc(0, timer, 0); //call the timer function to run at the start of the game
    glutKeyboardFunc(keyboard);

    glutMainLoop();
}

void render (void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(width/boardWidth * zoom);
    glBegin(GL_POINTS);
    int millisecondDifference = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()-prevTime).count();
    if (millisecondDifference > delay) {
        moveMultithread();
        generation++;
        std::cout << generation << std::endl;
        prevTime = std::chrono::steady_clock::now();
    }
    for (uint16_t y = 0; y < boardHeight; y++) {
        for (uint16_t x = 0; x < boardWidth; x++) {
            if (board[y][x]) {
                float thisX = 1.0 * x; //doing this to convert x to a float
                float thisY = 1.0 * y; //doing this to convert x to a float
                thisX = thisX / boardWidth * 2 * zoom - 0.9 + cameraOffset[0];
                thisY = thisY / boardHeight * 2 * zoom - 0.9 + cameraOffset[1];
                glVertex2f(thisX, thisY);
            }
        }
    }
    glEnd();
    glutSwapBuffers();
}

void keyboard (unsigned char c, int x, int y) {
    //moving around
    //inversed because the board moves the opposite direction of user
    if (c == 'd') {
        cameraOffset[0] -= 0.1;
    }
    if (c == 'a') {
        cameraOffset[0] += 0.1;
    }
    if (c == 'w') {
        cameraOffset[1] -= 0.1;
    }
    if (c == 's') {
        cameraOffset[1] += 0.1;
    }

    //zooming
    if (c == '-') {
        zoom -= 0.1;
    } else if (c == '=') {
        zoom += 0.1;
    }

    //chaging delay
    if (c == 'z') {
        delay -= 30;
    } else if (c == 'x') {
        delay += 30;
    }
}

void moveMultithread () {
    //enter move code here
    boardCopy = board;
    std::vector<std::thread> threads;
    for (uint16_t y = 0; y < boardHeight; y++) {
        threads.push_back(std::thread(calculateRow, y));
    }
    for (int i = 0; i < threads.size(); i++) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
    }
    board = boardCopy;
}

void timer (int) {
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}
