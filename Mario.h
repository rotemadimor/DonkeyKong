#pragma once

#include <iostream>
#include "Board.h"
#include "utils.h"
#include "Point.h"

class Mario {
public:
	Point mario;

	void keyPressed(char key);
	void moveMario();
	void jump();
	void moveOnLadderUp();
	void moveOnFloor();
	void hitBarrels();
	void reachedPauline();
};