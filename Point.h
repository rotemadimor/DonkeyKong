#pragma once
#include <iostream>
#include "utils.h"
#include "Point.h"

static constexpr int ANIM_SLEEP = 30;

static constexpr char UP = 'w';
static constexpr char LEFT = 'a';
static constexpr char DOWN = 'x';
static constexpr char RIGHT = 'd';
static constexpr char STAY = 's';

static constexpr char FLOOR_RIGHT = '>';
static constexpr char FLOOR_LEFT = '<';
static constexpr char FLOOR_STRAIGHT = '=';
static constexpr char LADDER = 'H';
static constexpr char AIR = ' ';
static constexpr char EXPLODE = 'x';

static constexpr char DEFAULT_POINT = '*';
static constexpr int DEFAULT_X_POINT = 0;
static constexpr int DEFAULT_Y_POINT = 23;


class Board;

class Point {
	Board* pBoard = nullptr;
	int x = DEFAULT_X_POINT , y = DEFAULT_Y_POINT;
	char ch = DEFAULT_POINT;
public:
	static constexpr char keys[] = { UP, LEFT, DOWN, RIGHT, STAY };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	struct Direction { int x, y; };
	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	Direction dir{ 0 , 0 };
	Direction prevDir{ 0 , 0 };
	int fallCounter = 0;

	Board* getPBoard() { return pBoard; }
	int getX() const { return x; }
	int getY() const { return y; }

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
	void setPoint(int _x, int _y) { x = _x; y = _y; }
	Point() {};
	Point(int _x, int _y, char _ch, Direction _dir = directions[4]) : x(_x), y(_y), ch(_ch),  dir(_dir)  {}
	Point(int _x, int _y) : x(_x), y(_y) {}

	void keyPressed(char key);
	void move();
	int fall();
	bool moveOneByDirection();
	void moveOneDown();
	void moveOneUp();
	bool isAboveFloor() const;
	bool isBelowFloor() const;
	char getOneCharBelow() const;
	bool isBelowLadder() const;
	bool isAboveLadder() const;
	void explode();
	bool isOnAir() const;
	void updateLocation(int newX, int newY);
	
	bool IsNextDirectionUp() { return(dir.x == directions[0].x && dir.y == directions[0].y);}
	bool IsNextDirectionLeft() { return(dir.x == directions[1].x && dir.y == directions[1].y);}
	bool IsNextDirectionDown() { return(dir.x == directions[2].x && dir.y == directions[2].y);}
	bool IsNextDirectionRight() { return(dir.x == directions[3].x && dir.y == directions[3].y);}
	void stay() {dir = directions[4];}

	bool IsNewLocationValid(int newX, int newY, char nextCharOnBoard);
	bool IsNewLocationValid(int newX, int newY);
	bool isInsideBoard() const;
	bool isInsideBoard(int newX, int newY) const;
	bool isFloor(char ch) const;
	bool isOnLadder();
	void setBoard(Board& board) { pBoard = &board;}
	void setDirections(Direction d) {prevDir = dir; dir = d;}
	void setDirection(Direction d) { dir = d;}

};

