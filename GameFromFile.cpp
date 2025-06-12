#pragma once
#include "GameFromFile.h"
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
#include"Steps.h"
#include "Results.h"


void GameFromFile::run(){
	ShowConsoleCursor(false);
	srand(time(NULL));
	getAllBoardFileNames(vec_to_fill);
	lives = 3;
	isWin = false;
	resetLevel();
	gameLoop();
}

void GameFromFile::gameLoop() {
	char key = ' ', key2 = ' ';
	bool pauseFlag = false;
	bool unmatching_result_found = false;
	loadLevel();
	
	while (lives > 0 && !isWin && level < vec_to_fill.size() && !unmatching_result_found) {
		player.getMarioPoint().setIsSilentPoint(isSilent);
		board.setIsSilentBoard(isSilent);
		iteration++;
		if (iteration % 20 == 0 && barrels.size() < sizeBarrels) {
			barrels.push_back(Barrel(Point(board.getXDonkey(), board.getYDonkey() + 1, 'O', board)));
		}
   		if (!isSilent) {
			player.getMarioPoint().draw();
		}
		if (player.getHasHammer() == false) {
			if(!isSilent){
			hammer.getHammerPoint().draw();
			board.printHammerState(player.getHasHammer());
			}
		}
		if (!isSilent) {
			for (int j = 0; j < ghosts.size(); j++) {
				ghosts[j]->getEnemyPoint().draw();
			}
			for (int j = 0; j < barrels.size(); j++) {
				barrels[j].getEnemyPoint().draw();
			}
		}
		if (!player.getJumping()) {
			if (steps.popStep(iteration, key)) {
				if (key != 'p' && key != 'P') {
					player.getMarioPoint().keyPressed(key);
				}
			}

		}
		Sleep(MOVE_SLEEP / 2);
		if (!player.getJumping()) {
			if (steps.popStep(iteration, key2)) {
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
		if (iteration == 226) {
			score = 100;
		}

		player.getMarioPoint().erase();
		if (!player.moveMario()) {
			lifeLost();
			continue;
		}
		if (reachedHammer()) {
			player.setHasHammer(true);
			if (!isSilent) {
				board.printHammerState(player.getHasHammer());
			}
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
			if (!isSilent) {
				menu.printWinScreen();
			}
			if (vec_to_fill.size() - 1 == level) {
				isWin = true;
				level = 0;
				score = 0;
				continue;
			}
			level++;
			loadLevel();
			resetLevel();
		}
		
	}
	if (lives == 0 && !isSilent) { menu.printGameOverScreen(); }
	//if(level >= vec_to_fill.size()){ menu.printinvalidScreen(); }
}

void GameFromFile::loadLevel() {
	if (level < vec_to_fill.size()) {
		std::string filename_prefix = vec_to_fill[level].substr(0, vec_to_fill[level].find_last_of('.'));
		std::string stepsFilename = filename_prefix + ".steps";
		std::string resultsFilename = filename_prefix + ".result";
		steps = Steps::loadSteps(stepsFilename);
		randomSeed = steps.getRandomSeed();
		results = Results::loadResults(resultsFilename);
	}
}


void GameFromFile::lifeLost() {

	if (results.getNextBombIteration() != iteration) {
		//unmatching_result_found = true;
		reportResultError("Results file has a die event that didn't happen!", iteration);
		return;
	}
	else {
		lives--;
	}
	if (lives > 0) {
		if (!isSilent) {
			menu.printLoseScreen(lives);
		}
		Sleep(SCREEN_SLEEP);
		resetLevel();
	}
}

bool GameFromFile::reachedPauline() {
	bool reached = isTheSameLocation(player.getMarioPoint(), pauline.getPaulinePoint());
	if (reached && results.getWinIteration() == iteration) {
		return true;
	}
	else if (reached && results.getWinIteration() != iteration) {
		reportResultError("Results file doesn't match finished event!", iteration);
		//unmatching_result_found = true;
		return false;
	}
	return false;
}

void GameFromFile::reportResultError(const std::string& message, size_t iteration) {
	system("cls");
	std::cout << message << '\n';
	std::cout << "Iteration: " << iteration << '\n';
	Sleep(SCREEN_SLEEP);
	level++;
	loadAndResetBoard();
}

void GameFromFile::loadAndResetBoard() {
	if (level < vec_to_fill.size()) {
		loadLevel();
		resetLevel();
	}
}