#include <cstring>
#include <iostream>

#include "Board.h"

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
	gotoxy(79, 1);
	std::cout << lives;
}