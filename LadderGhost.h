#pragma once
#include "Point.h"
#include "Ghost.h"

static constexpr char GHOST_LADDER = 'X';

class LadderGhost : public Ghost {
	bool onLadderUp = false, onLadderDown = false;
	enum Dir { REGULAR, UP, DOWN };
	int prevDir;
public:
	LadderGhost() {};
	LadderGhost(Point point, long _randomSeed) : Ghost(point, _randomSeed) {
		onLadderUp = false;
		onLadderDown = false;
		prevDir = REGULAR;
	}
	~LadderGhost() {} ;
	bool moveEnemy() override;
	void moveAboveFloor();
	void moveBelowFloor();
	void setBoolMoves();
};
