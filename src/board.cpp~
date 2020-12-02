#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

int boardWidth;
int boardHeight;

std::vector<std::vector<bool>> board;
std::vector<std::vector<bool>> boardCopy; //boardCopy is used to help with the manipulation of the game of life board

void calculateCell (uint16_t x, uint16_t y) {

    uint8_t surroundingCells = 0;
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

void calculateRows (uint16_t startingRow, uint16_t endingRow) {
    for (int y = startingRow; y < endingRow; y++) {
	for (int x = 0; x < boardWidth; x++) {
	    calculateCell(x, y);
	}
    }
}

void getBoard () {
    
    std::ifstream file("board.txt");

    std::string line;

    for (int y = 0; y < boardHeight; y++) {
	getline(file, line);
	board.push_back({}); //create a blank new vector

	for (int x = 0; x < boardWidth; x++) {
	    char thisChar = line.at(x);
	    if (thisChar == '1') {
		board[y].push_back(true);
	    } else {
		board[y].push_back(false);
	    }
	}
	std::cout << std::endl;
    }
    reverse(board.begin(), board.end());
}
