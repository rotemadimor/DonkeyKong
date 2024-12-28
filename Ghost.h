#pragma once
#include "Point.h"

static constexpr char GHOST = 'x';
static constexpr int GHOST_X = 15;
static constexpr int GHOST_Y = 35;

class Ghost
{
	Point ghost;

public:
	Point getGhostPoint() const { return ghost; }
	void createGhost(Board& pBoard);
	void moveGhost();
};

