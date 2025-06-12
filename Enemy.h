#pragma once
#include "Point.h"
#include <memory>

class Enemy{
protected:
	Point enemy;
public:
	Enemy() {};
	Enemy(Point point) : enemy(point) {};
	virtual const Point& getEnemyPoint() const { return enemy; }
	virtual Point& getEnemyPoint() { return enemy; }
	virtual bool moveEnemy() = 0;
};

