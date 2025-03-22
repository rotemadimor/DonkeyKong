#pragma once

#include <iostream>
#include "Board.h"
#include "utils.h"
#include "Point.h"
#include "Barrel.h"

bool Barrel::moveEnemy() {
	char floor;
	if (enemy.isAboveFloor()) {
		 if (enemy.fallCounter >= 8) {
			 if (!enemy.isSilent) {
				enemy.explode();
			 }

			 enemy.fallCounter = 0;
			return false;
		 }
		 else if (enemy.isAboveFloor())
			 enemy.fallCounter = 0;
		floor = getFloorType();
		switch (floor) {
		case FLOOR_LEFT:
			enemy.setDirection(enemy.directions[1]);
			break;
		case FLOOR_RIGHT:
			enemy.setDirection(enemy.directions[3]);
			break;
		default:
			break;
		}
		enemy.move();
	}
	else {
		enemy.moveOneDown();
		enemy.fallCounter++;
		
	}
	return true;
}

char Barrel::getFloorType() {
	return enemy.getOneCharBelow();
}


 