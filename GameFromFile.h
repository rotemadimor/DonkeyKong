#pragma once

#include <iostream>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <filesystem>
#include "Board.h"
#include "utils.h"
#include "Point.h"
#include "Barrel.h"
#include "Menu.h"
#include "Mario.h"
#include "Ghost.h"
#include "Hammer.h"
#include <vector>
#include "Pauline.h"
#include <cctype>
#include "Steps.h"
#include "Results.h"
#include "Game.h"

class GameFromFile : public Game {
	Steps steps;
	Results results;
	size_t iteration = 0;
	bool unmatching_result_found = false;

public:
	void run() override;
	void gameLoop()override;
	void loadLevel();
	void lifeLost()override;
	bool reachedPauline() override;
	void reportResultError(const std::string& message, size_t iteration);
	void loadAndResetBoard();
	// return true if mario reached pauline
	void SetIsSilent( bool _isSilent) {  isSilent = _isSilent; }
};


