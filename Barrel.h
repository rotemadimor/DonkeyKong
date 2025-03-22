#pragma once

#include <iostream>
#include "Board.h"
#include "utils.h"
#include "Point.h"
#include "Enemy.h"


class Barrel:public Enemy {
public:
	Barrel() {};
	Barrel(int x, int y, char icon, Board& pBoard) : Enemy(x, y, icon, pBoard) {
		enemy.setDirection(enemy.directions[2]);
	}
	bool moveEnemy() override;
	char getFloorType();
	//Point& getEnemyPoint() { return barrel; }
};


