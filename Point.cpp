#include "Point.h"
#include "Board.h"


bool Point::keyPressed(char key) {
	for (size_t i = 0; i < numKeys; i++) {
		if (std::tolower(key) == keys[i]) {
			prevDir = dir;
			dir = directions[i];
			return true;
		}
	}
	return false;
}

void Point::move() {
	int newX = x + dir.x;
	int newY = y + dir.y;
	char currCharOnBoard = pBoard->getChar(x, y);
	char nextCharOnBoard = pBoard->getChar(newX, newY);
	if (IsNewLocationValid(newX, newY, nextCharOnBoard)) {
		if (!isSilent) {
			pBoard->drawOnBoard(x, y);
		}
		x = newX;
		y = newY;
	}
}

bool Point::isNextCharFloor() {
	int newX = x + dir.x;
	int newY = y + 1;
	char nextCharOnBoard = pBoard->getChar(newX, newY);
	return isFloor(nextCharOnBoard);
}

bool Point::moveOneByDirection() {
	int newY = y + prevDir.y + dir.y;
	int newX = x + prevDir.x + dir.x;
	char nextCharOnBoard = pBoard->getChar(newX, newY);
	if (IsNewLocationValid(newX, newY, nextCharOnBoard)) {
		if (!isSilent) {
			pBoard->drawOnBoard(x, y);
		}
		y = newY;
		x = newX;
		return true;
	}
	return false;
}


void Point::moveOneDown() {
	if (!isSilent) {
		pBoard->drawOnBoard(x, y);
	}
	y = y + 1;
}

void Point::moveOneUp() {
	if (!isSilent) {
		pBoard->drawOnBoard(x, y);
	}
	y = y - 1;

}
bool Point::isAboveFloor() const{
	char oneBelow = getOneCharBelow();
	return (oneBelow == FLOOR_STRAIGHT || oneBelow == FLOOR_RIGHT || oneBelow == FLOOR_LEFT);//TODO const for floor
}

bool Point::isBelowFloor() const {
	char oneAbove = pBoard->getChar(x, y - 1);
	return (oneAbove == FLOOR_STRAIGHT || oneAbove == FLOOR_RIGHT || oneAbove == FLOOR_LEFT);//TODO const for floor
}

char Point::getOneCharBelow() const {
	return pBoard->getChar(x, y + 1);
}

bool Point::isBelowLadder() const {
	char oneAbove = pBoard->getChar(x, y - 1);
	return (oneAbove == LADDER);
}

bool Point::isAboveLadder() const{
	char oneBelow = pBoard->getChar(x, y + 2);
	return (oneBelow == LADDER);
}


void Point::updateLocation(int newX, int newY) {
	if (!isSilent) {
		pBoard->drawOnBoard(x, y);
	}
	y = y + newY;
	x = x + newX;
	draw();
}


int Point::fall() {
	int countFloors = 0;
	while (!isAboveFloor()) {
		moveOneDown();
		countFloors++;
	}
	return countFloors;
}

bool Point::IsNewLocationValid(int newX, int newY, char nextCharOnBoard) {
	return isInsideBoard(newX,newY) && !isFloor(nextCharOnBoard);
}

bool Point::IsNewLocationValid(int newX, int newY) {
	char nextCharOnBoard = this->pBoard->getChar(newX, newY);
	return isInsideBoard(newX, newY) && !isFloor(nextCharOnBoard);
}

bool Point::isInsideBoard() const {
	return (x < 80 && y < 24) && (x >= 0 && y > 0) && !isNextCharQLimit(x, y);
}

bool Point::isNextCharQLimit(int newX, int newY) const {
	char nextCharOnBoard = this->pBoard->getChar(newX, newY);
	return (nextCharOnBoard == 'Q');
}

bool Point::isInsideBoard(int newX, int newY) const {
	return (newX < 80 && newY < 24) && (newX >= 0 && newY > 0) && !isNextCharQLimit(newX,newY) ;
}

bool Point::isFloor(char ch) const {
	return (ch == FLOOR_STRAIGHT || ch == FLOOR_LEFT || ch == FLOOR_RIGHT);
}
bool Point::isOnLadder() {
	char oneBelow = pBoard->getChar(x, y + 1);
	return (oneBelow == LADDER);
}

void Point::oppositeDirection(){
	if (IsNextDirectionRight()) {
		setDirection(directions[1]);
	}
	else if (IsNextDirectionLeft()) {
		setDirection(directions[3]);
	}
}

bool Point::isNewPointOnFloor(int newX, int newY) {
	if (isInsideBoard(newX, newY)) {
		x = newX;
		y = newY;
		if (isAboveFloor()) {
			return true;
		}
		else { return false;}
	}
	else {return false;}
}


void Point::explode() {
	pBoard->drawcharOnBoard(x + 1, y, EXPLODE); //right
	pBoard->drawcharOnBoard(x - 1, y, EXPLODE); // left
	pBoard->drawcharOnBoard(x, y - 1, EXPLODE); // up
	pBoard->drawcharOnBoard(x - 1, y - 1, EXPLODE); // left up
	pBoard->drawcharOnBoard(x + 1, y - 1, EXPLODE); // right up
	Sleep(ANIM_SLEEP);
	pBoard->drawcharOnBoard(x + 1, y, ' '); //right
	pBoard->drawcharOnBoard(x - 1, y, ' '); // left
	pBoard->drawcharOnBoard(x, y - 1, ' '); // up
	pBoard->drawcharOnBoard(x - 1, y - 1, ' '); // left up
	pBoard->drawcharOnBoard(x + 1, y - 1, ' '); // right up
}
bool Point::isOnAir() const {
	char oneBelow = getOneCharBelow();
	return (oneBelow == AIR);
}