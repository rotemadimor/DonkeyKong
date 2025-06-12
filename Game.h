#pragma once

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
#include "LadderGhost.h"
#include "Hammer.h"
#include <vector>
#include "Pauline.h"
#include <cctype>
#include <memory>

	static constexpr int ESC = 27;
	static constexpr int INSTRUCTIONS = 56;
	static constexpr int GAME_START = 49;
	static constexpr int GAME_EXIT = 57;

	static constexpr int PAULINE_X = 39;
	static constexpr int PAULINE_Y = 1;

	static constexpr int MOVE_SLEEP = 100;

	static constexpr int SCORE_TIME = 600000000;

	static constexpr int sizeBarrels = 5;
	static constexpr int sizeGhosts = 4;
class Game{
protected:
	Board board;
	Mario player;
	Pauline pauline;
	Menu menu;
	std::vector<Barrel> barrels;
	std::vector<Ghost*> ghosts;
	Hammer hammer;
	std::vector<std::string> vec_to_fill;
	size_t iteration = 0;
	int lives = 3;
	bool isWin = false;
	bool isKeyPressed = false;
	int score = 0;
	int level = 0;
	long randomSeed;
	bool isSilent = false;
public:
	virtual void run();
	void createBarrels(Board& board);
	void menuChooseLevel(int start);
	void createHammerInGame(Board& pBoard);
	virtual void gameLoop();
	void pauseGame();
	bool ishitMario(int i);
	bool isTheSameLocation(Point p1, Point p2); // return true if 2 point are in the same location
	virtual void lifeLost();
	bool isSwappedLocations(Point p1, Point p2); //return true if the next location of p1 is the curr location of p2 and vice versa
	void resetLevel();
	//void loadAndResetBoard();
	void eraseBarrel(int j);
	virtual bool reachedPauline();// return true if mario reached pauline
	bool reachedHammer();
	bool isMarioHitEnemy(Point pMario, Point pEnemy);
	void getAllBoardFileNames(std::vector<std::string>& vec_to_fill);
	bool isNotNumber(char c) {
		return !std::isdigit(static_cast<unsigned char>(c));
	}
	void clearVector();
};

