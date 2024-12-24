#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Board.h"
#include "utils.h"
#include "Point.h"
#include "Mario.h"
#include "Game.h"
#include "Menu.h"


void Game::run() {
	ShowConsoleCursor(false);
	menu.printMenu();
	char key;
	while (true) {
		key = _getch();
		if (key == GAME_START) {
			board.reset();
			resetLevel();
			lives = 3;
			isWin = false;
			board.print();
			board.printLivesLeft(lives);
			gameLoop();
			menu.printMenu();
		}
		else if (key == INSTRUCTIONS) {
			menu.printInstructions();
			continue;
		}
		else if (key == GAME_EXIT) {
			break;
		}
	}
}




void Game::createBarrels(Board& board) {
	int i;
	for (i = 0; i < sizeBarrels; i++) {
		barrels[i].createBarrel(board);
	}
}
void Game::gameLoop() {
	int count = 0;
	char key;
	bool pauseFlag = false;
	while (lives > 0 && !isWin) {
		count++;
		if (count % 20 == 0 && barrelsCreated < sizeBarrels) {
			barrelsOnBoard++;
			barrels[barrelsOnBoard].createBarrel(board);
			barrelsCreated++;
		}
		player.getMarioPoint().draw();
		for (int j = barrelsOnBoard; j >= 0; j--) {
			barrels[j].getBarrelPoint().draw();
		}

		if (_kbhit() && !player.getJumping()) {
			key = _getch();
			if (key == ESC) {
				pauseGame();
			}
			player.getMarioPoint().keyPressed(key);
		}
		Sleep(MOVE_SLEEP);
		player.getMarioPoint().erase();
		if (!player.moveMario()) {
			lifeLost();
			continue;
		}
		for (int j = barrelsOnBoard; j >= 0; j--) { 
			barrels[j].getBarrelPoint().erase();
			if (ishitMario(j)) {
				lifeLost();
				break;
			}
			else if (!(barrels[j].moveBarrel())) {
				if (player.isMarioAroundExplosion(barrels[j].getBarrelPoint())) {
					lifeLost();
				}
				eraseBarrel(j, barrelsOnBoard);
				barrelsOnBoard--;
				break;
			}
		}
		if (reachedPauline()) {
			menu.printWinScreen();
			isWin = true;
			resetLevel();
			break;
		}
	}
	if( lives == 0){ menu.printGameOverScreen(); }
}
			

void Game::pauseGame() {
	while (true) {
		if (_kbhit()) {
			char key = _getch();
			if (key == ESC) {
				break;
			}
		}
	}
}

bool Game::ishitMario(int i) {
		if (isTheSameLocation(barrels[i].getBarrelPoint(), player.getMarioPoint())) {
			barrels[i].getBarrelPoint().explode();
			if (player.isMarioAroundExplosion(barrels[i].getBarrelPoint())) {
				return true;
			}
			return true;
		}
		return false;
}


bool Game::isTheSameLocation(Point p1, Point p2) {

	if (p1.getX() == p2.getX() && p1.getY() == p2.getY()) {
		return true;
	}
	else if(isSwappedLocations(p1,p2) ){
		return true;
	}
	return false;
}
void Game::lifeLost() {
	lives--;
	if (lives > 0) {
		menu.printLoseScreen(lives);
		Sleep(SCREEN_SLEEP);
		resetLevel();
		board.print();
		board.printLivesLeft(lives);
	}
}

bool Game::isSwappedLocations(Point p1, Point p2){
	return ((p1.getX() == p2.getX() + p2.dir.x && p1.getY() == p2.getY() + p2.dir.y) || (p2.getX() == p1.getX() + p2.dir.x && p2.getY() == p1.getY() + p1.dir.y));
}

void Game::resetLevel() {
	barrelsOnBoard = -1;
	barrelsCreated = 0;
	player.resetMario();
	player.getMarioPoint().setBoard(board);
	player.getMarioPoint().setChar('@');
	currSize = sizeBarrels;
	createBarrels(board);
}

void Game::eraseBarrel(int j, int barrelsOnBoard) {
	for (int i = j; i < barrelsOnBoard ; i++) {
		barrels[i] = barrels[i + 1];
	}
	currSize = barrelsOnBoard - 1;
}

bool Game::reachedPauline() {
	return isTheSameLocation(player.getMarioPoint(), Point(PAULINE_X, PAULINE_Y));
}
