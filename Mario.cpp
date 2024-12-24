#pragma once
#include "Mario.h"

bool Mario::moveMario() {
	setBoolMoves();
	if (!mario.isAboveFloor() && !jumping && !onLadderUp && !onLadderDown) {
		mario.moveOneDown();
		mario.fallCounter++;
		if (mario.isAboveFloor() && (mario.fallCounter >= 5)) {
			mario.explode();
			mario.fallCounter = 0;
			return false;
		}
		else if (mario.isAboveFloor())
			mario.fallCounter = 0;
	}
	else if (jumping) {
			jumping = mario.moveOneByDirection();
			if (jumping) {
				jumpingCounter--;
				if (jumpingCounter <= 2) {
					mario.setDirection(mario.directions[2]);
				}
				if (jumpingCounter == 0) {
					jumping = false;
					jumpingCounter = 4;
					mario.setDirections(mario.prevDir);
				}
			}
	}
	else if (onLadderUp) {
		if (!mario.isBelowFloor()) mario.moveOneUp();
		else {
			moveAboveFloor();
			mario.stay();
			onLadderUp = false;
		}
	}
	else if (onLadderDown && !onLadderUp) {
		if (!mario.isAboveFloor()) {
			mario.moveOneDown();
			mario.stay();
			onLadderDown = false;
		}
		else moveBelowFloor();
	}
	else {
		mario.move();
	}
	return true;
}



void Mario::setBoolMoves() {
	falling = isOnAirMario();
	if (mario.IsNextDirectionUp() && !falling && !jumping && !mario.isBelowFloor()) {
		if (mario.isBelowLadder() || (mario.isOnLadder() && onLadderUp)) {
			onLadderUp = true;
		}
		else{
			jumping = true;
		}
	}
	if (mario.IsNextDirectionDown() && !falling && !jumping) {
		if (mario.isAboveLadder()) {
			onLadderDown = true;
		}
	}
}

bool Mario::isOnAirMario() const {
	char oneBelow = mario.getOneCharBelow();
	return (oneBelow == AIR && !jumping);
}



void Mario::moveAboveFloor() {
	int newY = - 2;
	mario.updateLocation(0, newY);
	mario.stay();
}


void Mario::moveBelowFloor() {
	int newY = 2;
	mario.updateLocation(0, newY);
	mario.stay();
}



void Mario::resetMario() {
	mario.setPoint(0, 23);
	mario.stay();
}
bool Mario::isMarioAroundExplosion(Point p) {
	int xM = this->mario.getX();
	int yM = this->mario.getY();
	int xB = p.getX();
	int yB = p.getY();

	if (xM == xB -1 && yM == yB) { return true; } // left +1
	else if (xM == xB - 2 && yM == yB) { return true; } // left +2
	
	else if (xM == xB + 1 && yM == yB) { return true; } // right +1
	else if (xM == xB - 2 && yM == yB) { return true; } // right +2
	
	else if (xM == xB && yM == yB + 1) { return true; } // down +1
	else if (xM == xB && yM == yB + 2) { return true; } // down +2
	
	else if (xM == xB && yM == yB - 1) { return true; } // up +1
	else if (xM == xB && yM == yB - 2) { return true; } // up +2
	
	else if (xM == xB - 1 && yM == yB - 1) { return true; } // up left +1
	else if (xM == xB - 1 && yM == yB - 2) { return true; } // up left +2
	
	else if (xM == xB - 1 && yM == yB + 1) { return true; } // down left +1
	else if (xM == xB - 1 && yM == yB + 2) { return true; } // down left +2
	
	else if (xM == xB + 1 && yM == yB - 1) { return true; } // up right +1
	else if (xM == xB + 1 && yM == yB - 2) { return true; } // up right +2
	
	else if (xM == xB + 1 && yM == yB + 1) { return true; } // down right +1
	else if (xM == xB + 1 && yM == yB + 2) { return true; } // down right +2
	
	else if (xM == xB - 2 && yM == yB - 2) { return true; } // up + 2 left +2
	else if (xM == xB - 2 && yM == yB - 1) { return true; } // up + 1 left +2

	else if (xM == xB - 2 && yM == yB + 2) { return true; } // down + 2 left +1
	else if (xM == xB - 2 && yM == yB + 1) { return true; } // down + 1 left +2

	else if (xM == xB + 2 && yM == yB - 2) { return true; } // up  + 2 right +2
	else if (xM == xB + 2 && yM == yB - 1) { return true; } // up  + 1 right +2

	else if (xM == xB + 2 && yM == yB + 2) { return true; } // down + 2 right +2
	else if (xM == xB + 2 && yM == yB + 1) { return true; } // down + 1 right +2
	
	return false;
}