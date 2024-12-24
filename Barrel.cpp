#pragma once

#include <iostream>
#include "Board.h"
#include "utils.h"
#include "Point.h"
#include "Barrel.h"




void Barrel::createBarrel(Board &pBoard) {

	srand(time(NULL));
	int direction = 2 * ( rand() % 2);
	barrel = Point(14 + direction , 1, 'O');
	barrel.setBoard(pBoard);

}


bool Barrel::moveBarrel() {
	char floor;
	if (barrel.isAboveFloor()) {
		 if (barrel.fallCounter >= 8) {
			barrel.explode();

			barrel.fallCounter = 0;
			return false;
		 }
		 else if (barrel.isAboveFloor())
			 barrel.fallCounter = 0;
		floor = getFloorType();
		switch (floor) {
		case FLOOR_LEFT:
			barrel.setDirection(barrel.directions[1]);
			break;
		case FLOOR_RIGHT:
			barrel.setDirection(barrel.directions[3]);
			break;
		default:
			break;
		}
		barrel.move();
	}
	else {
		barrel.moveOneDown();
		barrel.fallCounter++;
		
	}
	return true;
}

char Barrel::getFloorType() {
	return barrel.getOneCharBelow();
}


 