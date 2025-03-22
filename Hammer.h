#pragma once
#include "Point.h"

static constexpr int HAM_X = 8;
static constexpr int HAM_Y = 23;
//static constexpr char HAMMER = 'p';


class Hammer
{
	Point hammer;

public:
	//Hammer();
	void createHammer(Board& pBoard);
	Point& getHammerPoint() { return hammer; }

};

