#pragma once

#include <iostream>
#include "Board.h"
#include "utils.h"
#include "Point.h"

class Barrel {
public:
	Point barrel;
	//void explode();
	void hitMario();
	void born();
	void moveBarrel();
	char getFloorType();
	
	
};
