#include "Point.h"

void Point::keyPressed(char key) {
	for (size_t i = 0; i < numKeys; i++) {
		if (std::tolower(key) == keys[i]) {
			prevDir = dir;
			dir = directions[i];
			return;
		}
	}
}

char Point::move() {
	int newX = x + dir.x;
	int newY = y + dir.y;
	char currCharOnBoard = pBoard->getChar(x, y);
	char nextCharOnBoard = pBoard->getChar(newX, newY);

	// + Better use a constant for the wall character

	if (IsNewLocationValid(newX, newY, nextCharOnBoard)) {
		if (!IsNextDirectionUp()) {
			x = newX;
			y = newY;
			return nextCharOnBoard;
		}
	}
	return currCharOnBoard;
}

bool Point::IsOnFloor() {
	char v = this->pBoard->getChar(x, y + 1);
	if (v == '=' || v == '>' || v == '<') {
		return true;
	}
	return false;
}


void Point::moveOneUp() {
	int newY = y + dir.y;
	int newX = x + dir.x;
	char nextCharOnBoard = pBoard->getChar(x, newY);
	if (IsNewLocationValid(newX, newY, nextCharOnBoard)) {
		y = newY;
		x = newX;
		draw(ch);
		Sleep(100);
		erase();
	}
}

void Point::moveOneUpRight() {
	moveOneUpRight();

}

void Point::moveOneDown() {
	y = y + 1;
	draw(ch);
	Sleep(100);
	erase();
}

void Point::jumpUp() {
	moveOneUp();
	moveOneUp();
	fall();
	stay();
}

void Point::jumpRight() {
	int newY = y - 1;
	int newX = x + 1;
	char nextCharOnBoard = pBoard->getChar(newX, newY);
	if (IsNewLocationValid(x, newY, nextCharOnBoard)) {
		y = newY;
		x = newX;
		draw(ch);
		Sleep(100);
		erase();
	}
}

void Point::jumpLeft() {

}
void Point::fall() {
	while (!IsOnFloor()) {
		moveOneDown();
	}
}
bool Point::IsNextToLadder() {
	char currCharOnBoard = pBoard->getChar(x, y);
	
	if (IsNewLocationValid(x, y - 1, currCharOnBoard)) {
		if (currCharOnBoard == 'H' && IsNextDirectionUp()) {
			return true;
		}
	}
	return false;
}

void Point::climb() {
	char currCharOnBoard = pBoard->getChar(x, y);
	moveOneUp();
	pBoard->setChar(x, y + 1, 'H');
	moveOneUp();
	pBoard->setChar(x, y + 1, 'H');
	moveOneUp();
	/*while (!this->IsOnFloor()) {
		pBoard->setChar(x, y, 'H');
		moveOneUp();
		
	}*/
}

bool Point::IsNewLocationValid(int newX, int newY, char nextCharOnBoard) {
	if (nextCharOnBoard == '=' || nextCharOnBoard == '<' || nextCharOnBoard == '>') {
		return false;
	}
	return (newX < 80 && newY < 24) && (newX > 0 && newY > 0);
}
