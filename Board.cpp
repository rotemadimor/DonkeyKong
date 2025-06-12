#include <cstring>
#include <iostream>
#include <vector>
#include "Board.h"
#include "Ghost.h"
#include "Hammer.h"
#include "LadderGhost.h"

using std::vector;
using std::string;

void Board::reset() {
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], originalBoard[i], MAX_X + 1);
	}
}

void Board::print() const{
	system("cls");
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << currentBoard[i] << '\n';
	}
	std::cout << currentBoard[MAX_Y - 1];

}

void Board::printLivesLeft(int lives) {
	gotoxy(xLegend, yLegend); // 75, 1
	drawStringAndNumOnBoard(xLegend, yLegend, "Lives:", lives);
}

void Board::printHammerState(bool state){
	gotoxy(xLegend, yLegend + 1); // 75, 2
	std::string stringState;
	if (state) {
		stringState = "Hammer: ON ";
	}
	else stringState = "Hammer: OFF";
	drawStringOnBoard(xLegend, yLegend + 1, stringState);
}

void Board::printScore(int score) {
	gotoxy(xLegend, yLegend + 2); // 75, 3
	drawStringAndNumOnBoard(xLegend, yLegend + 2, "Score:", score);
}

int Board::load(const std::string& filename, Point& pPauline, Point& pMario, Point& pHammer,vector<Ghost*>& pGhostsVec,int lives, int score, long randomSeed) {
	std::ifstream screen_file(filename);
	bool marioExist = false, paulineExist = false, donkeyExist = false;

 	if (!screen_file.is_open()) {
		std::cout << "no board has found :( \n moving to the next board ";
		return -1;
	}
	int curr_row = 0;
	int curr_col = 0;                                                                                        
	char c;
	
	while (!screen_file.get(c).eof() && curr_row < MAX_Y) {

		if (c == '\n') {
			if (curr_col < MAX_X) {
				// add spaces for missing cols
				#pragma warning(suppress : 4996) // to allow strcpy
				strcpy(originalBoard[curr_row] + curr_col, string(MAX_X - 1 - curr_col, ' ').c_str());
			}
			++curr_row;
			curr_col = 0;
			continue;
		}

		if (curr_col < MAX_X) {
			// handle special chars
			if (c == '@') {
				pMario = Point(curr_col, curr_row,c,*this);
				drawOnBoard(pMario);
				originalBoard[curr_row][curr_col] = ' ';
				marioExist = true;
			}
			else if (c == '&') {
				xDonkey = curr_col;
				yDonkey = curr_row;
				originalBoard[curr_row][curr_col] = '&';
				donkeyExist = true;
			}
			else if (c == '$') {
				pPauline = Point(curr_col, curr_row, c, *this);
				originalBoard[curr_row][curr_col] = '$';
				paulineExist = true;
			}
			else if (c == 'L') {
				xLegend =  curr_col+ 1;
				yLegend = curr_row + 1;
				originalBoard[curr_row][curr_col] = ' ';
			}
			else if (c == 'p' || c == 'P') {
				pHammer = Point(curr_col, curr_row, c, *this);
				drawOnBoard(pHammer);
				originalBoard[curr_row][curr_col] = ' ';
			}
			else if (c == 'x') {
				pGhostsVec.emplace_back(new Ghost(Point(curr_col, curr_row,c, *this),randomSeed));
				originalBoard[curr_row][curr_col] = ' ';
			}
			else if (c == 'X') {
				pGhostsVec.emplace_back(new LadderGhost(Point(curr_col, curr_row, c, *this),randomSeed));
				originalBoard[curr_row][curr_col] = ' ';
			}
			else{
				originalBoard[curr_row][curr_col] = c;
			}
			curr_col++;
		}
	}
	if (!marioExist || !paulineExist || !donkeyExist) {
		return -1;
	}
	int last_row = (curr_row < MAX_Y ? curr_row : MAX_Y - 1);
	// add a closing frame
	// first line
	#pragma warning(suppress : 4996) // to allow strcpy
	strcpy(originalBoard[0], std::string(MAX_X, '=').c_str());
	// last line
	#pragma warning(suppress : 4996) // to allow strcpy
	strcpy(originalBoard[last_row], std::string(MAX_X, '=').c_str());
	// first col + last col
	for (int row = 1; row < last_row; ++row) {
		originalBoard[row][0] = 'Q';
		originalBoard[row][MAX_X - 1] = 'Q';
	}
	return 0;
}



