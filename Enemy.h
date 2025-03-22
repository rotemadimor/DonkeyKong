#pragma once
#include "Point.h"

class Enemy{
protected:
	Point enemy;
public:
	Enemy() {};
	Enemy(int x, int y,char icon, Board& pBoard) :enemy(x, y,icon,pBoard) {}
	virtual const Point& getEnemyPoint() const { return enemy; }
	virtual Point& getEnemyPoint() { return enemy; }
	virtual bool moveEnemy() = 0;
};

