#include "Ghost.h"


bool Ghost::moveEnemy(){
	int rand = randomSeed % 100;
	if (enemy.isAboveFloor() && enemy.isNextCharFloor()) {
		if (rand >= 95 && rand < 100) {
			enemy.oppositeDirection();
		}
	}
	else {
		enemy.oppositeDirection();
	}
	enemy.move();
	return true;
}