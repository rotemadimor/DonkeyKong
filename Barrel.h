#pragma once

#include <iostream>
#include "Board.h"
#include "utils.h"
#include "Point.h"

class Barrel {
	Point barrel;
public:
	Barrel() {};
	void createBarrel(Board &pBoard);
	bool moveBarrel();
	char getFloorType();
	Point& getBarrelPoint() { return barrel; }
};