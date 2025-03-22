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
#include "Mario.h"
#include "GameToSave.h"
#include "Menu.h"
#include"Steps.h"
#include "Results.h"

void GameToSave::run() {

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



void GameToSave::gameLoop() {
	char key = ' ', key2 = ' ';
	bool pauseFlag = false;
	std::string filename_prefix, stepsFilename, resultsFilename;
	randomSeed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
	steps.setRandomSeed(randomSeed);

	while (lives > 0 && !isWin && level < vec_to_fill.size()) {

		filename_prefix = vec_to_fill[level].substr(0, vec_to_fill[level].find_last_of('.'));
		stepsFilename = filename_prefix + ".steps";
		resultsFilename = filename_prefix + ".result";

		iteration++;

		if (iteration % 20 == 0 && barrels.size() < sizeBarrels) {
			barrels.push_back(Barrel(board.getXDonkey(), board.getYDonkey() + 1, 'O', board));
		}
		player.getMarioPoint().draw();
		if (player.getHasHammer() == false) {
			hammer.getHammerPoint().draw();
			board.printHammerState(player.getHasHammer());
		}
		for (int j = 0; j < ghosts.size(); j++) {
			ghosts[j].getEnemyPoint().draw();
		}
		for (int j = 0; j < barrels.size(); j++) {
			barrels[j].getEnemyPoint().draw();
		}

		if (_kbhit() && !player.getJumping()) {
			key = _getch();
			if (key != 'p' && key != 'P') {
				if (player.getMarioPoint().keyPressed(key)) {
					steps.addStep(iteration, key);
				}
			}
			if (key == ESC) pauseGame();
		}

		Sleep(MOVE_SLEEP);

		if (_kbhit() && !player.getJumping()) {
			key2 = _getch();
			if (key2 == 'p' || key2 == 'P') {
				steps.addStep(iteration, key2);
				if (player.getHasHammer()) {
					for (int g = 0; g < ghosts.size(); g++) {
						if (isMarioHitEnemy(player.getMarioPoint(), ghosts[g].getEnemyPoint())) {
							ghosts[g].getEnemyPoint().erase();
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
				if (player.getMarioPoint().keyPressed(key2)) {
					steps.addStep(iteration, key2);
				}
			}
		}

		if ((key == 'p' || key == 'P') && player.getHasHammer()) {
			for (int g = 0; g < ghosts.size(); g++) {
				if (isMarioHitEnemy(player.getMarioPoint(), ghosts[g].getEnemyPoint())) {
					ghosts[g].getEnemyPoint().erase();
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
			ghosts[j].getEnemyPoint().erase();
			board.drawcharOnBoard(ghosts[j].getEnemyPoint().getX(), ghosts[j].getEnemyPoint().getY(),' ');
			for (int i = 0; i < ghosts.size() && i != j; i++) {
				if (isSwappedLocations(ghosts[j].getEnemyPoint(), ghosts[i].getEnemyPoint())) {
					ghosts[j].getEnemyPoint().oppositeDirection();
					ghosts[i].getEnemyPoint().oppositeDirection();
				}
			}
			ghosts[j].moveEnemy();
			if (isTheSameLocation(player.getMarioPoint(), ghosts[j].getEnemyPoint())) {
				lifeLost();
				break;
			}
		}
		if (reachedPauline()) {
			if (iteration < SCORE_TIME) {
				score += 100;
				results.setScoreInResults(100);
			}
			menu.printWinScreen();
			results.addResult(iteration, results.finished);
		
			if (vec_to_fill.size() - 1 == level) {
				isWin = true;
				level = 0;
				score = 0;
				continue;
			}
			saveFiles(stepsFilename, resultsFilename);
			level++;
			resetResultsSteps();
			resetLevel();
		}

	}
	if( lives == 0){ 
		menu.printGameOverScreen();
		saveFiles(stepsFilename, resultsFilename);
	}
}

void GameToSave::resetResultsSteps() {
	results.setScoreInResults(0);
	results.emptyResults();
	steps.emptySteps();
}

void GameToSave::saveFiles(std::string stepsFilename, std::string resultsFilename) {
	results.saveResults(resultsFilename);
	steps.saveSteps(stepsFilename);
}

void GameToSave::lifeLost() {
	lives--;
	if (lives > 0) {
		menu.printLoseScreen(lives);
		Sleep(SCREEN_SLEEP);
		resetLevel();
	}
	results.addResult(iteration, results.died);
}
