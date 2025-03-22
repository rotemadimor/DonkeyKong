#pragma once
#include "Point.h"
static constexpr int PAU_X = 15;
static constexpr int PAU_Y = 23;
static constexpr char PAULINE = '$';
class Pauline
{
	Point pauline;

public:
	
	void createpauline(Board& pBoard) {
		pauline = Point(PAU_X, PAU_Y, PAULINE);
		pauline.setBoard(pBoard);
	};
	Point& getPaulinePoint() { return pauline; }

};