#include "LadderGhost.h"

bool LadderGhost::moveEnemy() {
	int rand = randomSeed % 100;
	if (enemy.isAboveFloor() && enemy.isNextCharFloor()) {
		if (rand >= 95 && rand < 100) {
			enemy.oppositeDirection();
		}
	}
	else {
		enemy.oppositeDirection();
	}
	setBoolMoves();


	if (onLadderUp) {
		if (!enemy.isBelowFloor()) enemy.moveOneUp();
		else {
			moveAboveFloor();
		}
	}
	else if (onLadderDown && !onLadderUp) {
		if (!enemy.isAboveFloor()) {
			enemy.moveOneDown();
		}
		else moveBelowFloor();
	}
	else {
		enemy.move();
	}
	return true;
}

void LadderGhost::moveAboveFloor() {
	int newY = -2;
	enemy.updateLocation(0, newY);
}
void LadderGhost::moveBelowFloor() {
	int newY = 2;
	enemy.updateLocation(0, newY);
}

void LadderGhost::setBoolMoves() {

	if (enemy.isBelowLadder() && prevDir != DOWN) {
		onLadderUp = true;
		prevDir = UP;
	}
	else if (enemy.isAboveFloor() && prevDir == UP) {
		prevDir = REGULAR;
		onLadderUp = false;
	}
	else if (enemy.isAboveLadder() && prevDir != UP) {
		onLadderDown = true;
		prevDir = DOWN;
	}
	else if (enemy.isAboveFloor() && prevDir == DOWN) {
		prevDir = REGULAR;
		onLadderDown = false;
	}
}