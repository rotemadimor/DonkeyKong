#pragma once

#include "Menu.h"
#include"Point.h"
#include "utils.h"
#include <windows.h>
#include <conio.h>
#include <iostream>

void Menu::printMenu() {
	system("cls");
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << menu[i] << '\n';
	}
	std::cout << menu[MAX_Y - 1];

}
void Menu::printInstructions(){
	system("cls");
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << instructions[i] << '\n';
	}
	std::cout << instructions[MAX_Y - 1];

}

void Menu::printLoseScreen(int lives) {
	system("cls");
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << livesLeft[i] << '\n';
	}
	std::cout << livesLeft[MAX_Y - 1];
	gotoxy(32, 10);
	std::cout << lives;
}

void Menu::printWinScreen() {
	system("cls");
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << win[i] << '\n';
	}
	std::cout << win[MAX_Y - 1];
	Sleep(SCREEN_SLEEP);
}

void Menu::printGameOverScreen() {
	system("cls");
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << gameOver[i] << '\n';
	}
	std::cout << gameOver[MAX_Y - 1];
	Sleep(SCREEN_SLEEP);
}

