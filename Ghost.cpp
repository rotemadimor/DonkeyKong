#include "Ghost.h"

void Ghost::createGhost(Board& pBoard) {
	int randDir, randX = 0, randY = 0;
	randDir = 2 * (rand() % 2) + 1;
	ghost = Point(randX, randY, GHOST, ghost.directions[randDir]);
	ghost.setBoard(pBoard);
	while (!ghost.isNewPointOnFloor(randX, randY)) {
		randX = 1 + rand() % 79;
		randY = 1 + rand() % 19;
	}

}

void Ghost::moveGhost(){
	if (ghost.isAboveFloor() && ghost.isNextCharFloor()) {
		ghost.move();
	}
	else {
		ghost.oppositeDirection();
	}
}
