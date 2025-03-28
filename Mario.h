#pragma once

#include <iostream>
#include "Board.h"
#include "utils.h"
#include "Point.h"


class Mario {
	
	bool jumping = false, onLadderUp = false, onLadderDown = false, falling = false;
	bool isHasHammer = false;
	int jumpingCounter = 4;
	Point mario;

public:
	bool moveMario();
	void setBoolMoves();
	void setHasHammer(bool newState) { isHasHammer = newState; }
	bool isOnAirMario() const;
	void moveAboveFloor();
	void moveBelowFloor();
	void resetMario();
	bool isMarioAroundExplosion(Point p);
	Point& getMarioPoint() { return mario; }
	bool getJumping() const { return jumping; }
	bool getHasHammer() const { return isHasHammer; }
};