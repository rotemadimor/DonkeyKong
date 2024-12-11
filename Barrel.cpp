#pragma once

#include <iostream>
#include "Board.h"
#include "utils.h"
#include "Point.h"
#include "Barrel.h"

void Barrel::hitMario() {
	//Point currMario = getMarioLocation();
	return;
	
}
void Barrel::born() {

	int dirFlag = 14;
	barrel = Point(16, 1, 'O');
	//barrel.draw();
}
void Barrel::moveBarrel() {

	char floor, nextCharOnBoard;
	nextCharOnBoard = 'r';

	if (barrel.IsOnFloor()) {
		floor = this->getFloorType();
		switch (floor) {
		case '<':
			barrel.setDirection(barrel.directions[1]);
			barrel.moveOneByDirection();
			break;
		case '>':
			barrel.setDirection(barrel.directions[3]);
			barrel.moveOneByDirection();
			break;
		case '=':
			barrel.setDirection(barrel.prevDir);
			//barrel.moveOneByDirection();
			break;
		default:
			break;
		}
	}

	
}

char Barrel::getFloorType() {
	 return barrel.pBoard->getChar(barrel.x, barrel.y + 1);
}
 
