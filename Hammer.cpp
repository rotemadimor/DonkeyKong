#include "Hammer.h"

void Hammer::createHammer(Board& pBoard) {
	hammer = Point(HAM_X, HAM_Y, HAMMER);
	hammer.setBoard(pBoard);
}
