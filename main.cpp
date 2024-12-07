#include <iostream>
#include <windows.h>
#include <conio.h>

#include "Board.h"
#include "utils.h"
#include "Mario.h"

// Better put this is a proper class
constexpr int ESC = 27;

int main() {
	ShowConsoleCursor(false);
	Board board;
	board.reset();
	board.print();
	Mario p;
	p.mario.setBoard(board);

	while (true) {
		p.mario.draw();
		/*HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
		FlushConsoleInputBuffer(hInput);*/
			if (_kbhit()) {
				
				char key = _getch();
				
				if (key == ESC) break;
				p.keyPressed(key);
				
			}
			Sleep(90);
		p.mario.erase();
		p.moveMario();
	}
	//board.print();
}
