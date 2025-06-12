#pragma once
#include "Point.h"
#include "Enemy.h"


static constexpr char GHOST = 'x';
static constexpr int GHOST_X = 15;
static constexpr int GHOST_Y = 35;

class Ghost: public Enemy{
protected:
	long randomSeed = 0;
public:
	Ghost() {};	
	Ghost(Point point,long _randomSeed) : Enemy(point){
		randomSeed = _randomSeed;
		int randDir = 2 * (randomSeed % 2) + 1;
		enemy.setDirection(enemy.directions[randDir]);
	}
	virtual ~Ghost() {};
	virtual bool moveEnemy() override;
	void setRandomSeed(long randSeed) { randomSeed = randSeed; }
};

