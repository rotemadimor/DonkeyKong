#pragma once

#include <iostream>
#include "Board.h"
#include "utils.h"

class Point {
public:
	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	struct Direction { int x, y; };
	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	int x = 0, y = 23;
	Direction dir{ 0 , 0 };
	Direction prevDir{ 0 , 0 };
	/*bool operator==(struct Direction dir) const{
		return ((this->x == dir.x) && (this->y == dir.y));
	}*/
	Board* pBoard = nullptr;
	char ch = '*';
	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}
	void draw() const { 
		draw(ch);
	}
	void erase() {
		draw(' ');
	}
	void setChar(char c) {
		ch = c;
	}

	void keyPressed(char key);
	char move();
	bool IsOnFloor();
	void jumpUp();
	void jumpRight();
	void jumpLeft();
	void fall();
	bool IsNextToLadder();
	void climb();

	void moveOneUp();
	void moveOneDown();
	void moveOneUpRight();
	
	bool IsNextDirectionUp() {
		return(dir.x == directions[0].x && dir.y == directions[0].y);
	}
	bool IsNextDirectionLeft() {
		return(dir.x == directions[1].x && dir.y == directions[1].y);
	}
	bool IsNextDirectionDown() {
		return(dir.x == directions[2].x && dir.y == directions[2].y);
	}
	bool IsNextDirectionRight() {
		return(dir.x == directions[3].x && dir.y == directions[3].y);
	}
	void stay() {
		dir = directions[4];
	}

	bool IsNewLocationValid(int newX, int newY, char nextCharOnBoard);
	void setBoard(Board& board) {
		pBoard = &board;
	}
};

