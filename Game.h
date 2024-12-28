#pragma once

#include <iostream>
#include "Board.h"
#include "utils.h"
#include "Point.h"
#include "Barrel.h"
#include "Menu.h"
#include "Mario.h"
#include "Ghost.h"

static constexpr int ESC = 27;
static constexpr int INSTRUCTIONS = 56;
static constexpr int GAME_START = 49;
static constexpr int GAME_EXIT = 57;

static constexpr int PAULINE_X = 39;
static constexpr int PAULINE_Y = 1;

static constexpr int MOVE_SLEEP = 100;

static constexpr int sizeBarrels = 5;
static constexpr int sizeGhosts = 4;

class Game {
	
	int currSize = sizeBarrels;
	Board board;
	Mario player;
	Menu menu;
	Barrel barrels[sizeBarrels];
	Ghost ghosts[sizeGhosts];
	int barrelsOnBoard = -1;
	int barrelsCreated = 0;
	int lives = 3;
	bool isWin = false;
	bool isKeyPressed = false;
	int score = 0;

	public:
		void run();
		void createBarrels(Board& board);
		void createGhosts(Board& board);
		void gameLoop();
		void pauseGame();
		bool ishitMario(int i);
		bool isTheSameLocation(Point p1, Point p2); // return true if 2 point are in the same location
		void lifeLost();
		bool isSwappedLocations(Point p1, Point p2); //return true if the next location of p1 is the curr location of p2 and vice versa
		void resetLevel();
		void eraseBarrel(int j, int barrelsOnBoard);
		bool reachedPauline();// return true if mario reached pauline
		
};

