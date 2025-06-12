#pragma once
#include "Game.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <filesystem>
#include "Board.h"
#include "utils.h"
#include "Point.h"
#include "Mario.h"
#include "Menu.h"

void Game::run() {
	ShowConsoleCursor(false);
	srand(time(NULL));
	getAllBoardFileNames(vec_to_fill);
	menu.printMenu();
	int start = 0;
	char key;
	while (true) {
		key = _getch();
		if (key == GAME_START) {
			menuChooseLevel(start);
			lives = 3;
			isWin = false;
			resetLevel();
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
		Barrel temp;
		temp = Barrel(Point(board.getXDonkey(), board.getYDonkey() + 1, 'O', board));
		barrels.push_back(temp);
	}
}

void Game::menuChooseLevel(int start) {
	if (vec_to_fill.size() > MAX_LEVELS_IN_MENU) {
		menu.printChooseLevel(vec_to_fill, start);
		char nev = _getch();
		while (isNotNumber(nev)) {
			if (nev == 'n') {
				menu.printChooseLevel(vec_to_fill, MAX_LEVELS_IN_MENU - start);
			}
			if (nev == 'p') {
				menu.printChooseLevel(vec_to_fill, start);
			}
			nev = _getch();
		}
		if (isNotNumber(nev)) {
			level = nev - 49;
		}
	}
	else {
		menu.printChooseLevel(vec_to_fill, start);
		char nev = _getch();
		while (isNotNumber(nev)) {
			nev = _getch();
		}
		if (!isNotNumber(nev)) {
			level = nev - 49;
		}
	}
}

void Game::createHammerInGame(Board& pBoard) {
	hammer.createHammer(pBoard);
}

void Game::gameLoop() {
	char key = ' ', key2 = ' ';
	bool pauseFlag = false;
	while (lives > 0 && !isWin && level < vec_to_fill.size()) {
		iteration++;
		if (iteration % 20 == 0 && barrels.size() < sizeBarrels) {
			barrels.push_back(Barrel(Point(board.getXDonkey(), board.getYDonkey() + 1, 'O', board)));
		}
		player.getMarioPoint().draw();
		if (player.getHasHammer() == false) {
			hammer.getHammerPoint().draw();
			board.printHammerState(player.getHasHammer());
		}
		for (int j = 0; j < ghosts.size(); j++) {
			ghosts[j]->getEnemyPoint().draw();
		}
		for (int j = 0; j < barrels.size(); j++) {
			barrels[j].getEnemyPoint().draw();
		}

		if (_kbhit() && !player.getJumping()) {
			key = _getch();
			if (key != 'p' && key != 'P') {
				player.getMarioPoint().keyPressed(key);
			}
			if (key == ESC) pauseGame();
		}
		Sleep(MOVE_SLEEP);

		if (_kbhit() && !player.getJumping()) {
			key2 = _getch();
			if (key2 == 'p' || key2 == 'P') {
				if (player.getHasHammer()) {
					for (int g = 0; g < ghosts.size(); g++) {
						if (isMarioHitEnemy(player.getMarioPoint(), ghosts[g]->getEnemyPoint())) {
							ghosts[g]->getEnemyPoint().erase();
							ghosts.erase(ghosts.begin() + g);
						}
					}
					for (int b = 0; b < barrels.size(); b++) {
						if (isMarioHitEnemy(player.getMarioPoint(), barrels[b].getEnemyPoint())) {
							eraseBarrel(b);
						}
					}
				}
			}
			else {
				player.getMarioPoint().keyPressed(key2);
			}
		}

		if ((key == 'p' || key == 'P') && player.getHasHammer()) {
			for (int g = 0; g < ghosts.size(); g++) {
				if (isMarioHitEnemy(player.getMarioPoint(), ghosts[g]->getEnemyPoint())) {
					ghosts[g]->getEnemyPoint().erase();
					ghosts.erase(ghosts.begin() + g);
				}
			}
			for (int b = 0; b < barrels.size(); b++) {
				if (isMarioHitEnemy(player.getMarioPoint(), barrels[b].getEnemyPoint())) {
					eraseBarrel(b);
				}
			}
		}

		player.getMarioPoint().erase();
		if (!player.moveMario()) {
			lifeLost();
			continue;
		}
		if (reachedHammer()) {
			player.setHasHammer(true);
			board.printHammerState(player.getHasHammer());
			hammer.getHammerPoint().erase();

		}
		for (int j = 0; j < barrels.size(); j++) {
			barrels[j].getEnemyPoint().erase();
			if (ishitMario(j)) {
				lifeLost();
				break;
			}
			else if (!(barrels[j].moveEnemy())) {
				if (player.isMarioAroundExplosion(barrels[j].getEnemyPoint())) {
					lifeLost();
					break;
				}
				eraseBarrel(j);
				break;
			}
		}
		for (int j = 0; j < ghosts.size(); j++) {
			ghosts[j]->getEnemyPoint().erase();
			board.drawcharOnBoard(ghosts[j]->getEnemyPoint().getX(), ghosts[j]->getEnemyPoint().getY(), ' ');
			for (int i = 0; i < ghosts.size() && i != j; i++) {
				if (isSwappedLocations(ghosts[j]->getEnemyPoint(), ghosts[i]->getEnemyPoint())) {
					ghosts[j]->getEnemyPoint().oppositeDirection();
					ghosts[i]->getEnemyPoint().oppositeDirection();
				}
			}
			ghosts[j]->moveEnemy();
			if (isTheSameLocation(player.getMarioPoint(), ghosts[j]->getEnemyPoint())) {
				lifeLost();
				break;
			}
		}
		if (reachedPauline()) {
			if (iteration < SCORE_TIME) {
				score += 100;
			}
			if(!isSilent) menu.printWinScreen();
			if (vec_to_fill.size() - 1 == level) {
				isWin = true;
				level = 0;
				score = 0;
				continue;
			}
			level++;
			resetLevel();
		}
	}
	if (lives == 0) { menu.printGameOverScreen(); }
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
	if (isTheSameLocation(barrels[i].getEnemyPoint(), player.getMarioPoint())) {
		if (!isSilent) {
			barrels[i].getEnemyPoint().explode();
		}
		if (player.isMarioAroundExplosion(barrels[i].getEnemyPoint())) {
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
	else if (isSwappedLocations(p1, p2)) {
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
	}
}

bool Game::isSwappedLocations(Point p1, Point p2) {
	return ((p1.getX() == p2.getX() + p2.dir.x && p1.getY() == p2.getY() + p2.dir.y) || (p2.getX() == p1.getX() + p1.dir.x && p2.getY() == p1.getY() + p1.dir.y));
}

void Game::resetLevel() {
	bool isValidScreen = true;
	clearVector();
	barrels.clear();
	while (board.load(vec_to_fill[level], pauline.getPaulinePoint(), player.getMarioPoint(), hammer.getHammerPoint(), ghosts, lives, score, randomSeed) == -1) {
		level++;
		if (level == vec_to_fill.size()) {
			isValidScreen = false;
			if (!isSilent) {
				menu.printinvalidLastScreen();
			}
			break;
		}
		if (!isSilent) {
			menu.printinvalidScreen();
		}
	}
	if (isValidScreen) {
		board.reset();
		player.setHasHammer(false);
		if (!isSilent) {
			board.print();
			board.printLivesLeft(lives);
			board.printHammerState(false);
			board.printScore(score);
		}
	}
}



void Game::eraseBarrel(int j) {
	barrels[j].getEnemyPoint().erase();
	barrels.erase(barrels.begin() + j);
}

bool Game::reachedPauline() {
	return isTheSameLocation(player.getMarioPoint(), pauline.getPaulinePoint());
}

bool Game::reachedHammer() {
	return isTheSameLocation(player.getMarioPoint(), hammer.getHammerPoint());
}
bool Game::isMarioHitEnemy(Point pMario, Point pEnemy) {
	return ((pMario.getX() == pEnemy.getX() + 2 * pEnemy.dir.x || pEnemy.getX() == pMario.getX() + 2 * pMario.dir.x) && pMario.getY() == pEnemy.getY());
}


void Game::getAllBoardFileNames(std::vector<std::string>& vec_to_fill) {
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(fs::current_path())) {
		auto filename = entry.path().filename();
		auto filenameStr = filename.string();
		if (filenameStr.substr(0, 6) == "dkong_" && filename.extension() == ".screen") {
			vec_to_fill.push_back(filenameStr);
		}
	}
}
void Game::clearVector() {

	for (Ghost* g: ghosts) {
		delete g;
	}
	ghosts.clear();
}
