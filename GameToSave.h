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
#include "Results.h"
#include "Steps.h"
#include <cctype>
#include "Game.h"


class GameToSave : public Game {
	Steps steps;
	Results results;
	size_t iteration = 0;
	public:
		void run() override;
		void gameLoop()override;
		void resetResultsSteps();
		void saveFiles(std::string stepsFilename, std::string resultsFilename);
		void lifeLost() override;
};