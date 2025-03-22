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

void Menu::printChooseLevel(std::vector<std::string>& vec_to_fill, int start)
{
	system("cls");
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << chooseLevel[i] << '\n';
	}
	std::cout << chooseLevel[MAX_Y - 1];

	int count = 0;
	int min = (MAX_LEVELS_IN_MENU < (vec_to_fill.size()-start) ? MAX_LEVELS_IN_MENU : vec_to_fill.size());
	for (int i = start; i < min; i++) {
		gotoxy(25, 3 + count);
		std::cout << '(' << i + 1<< ") " << vec_to_fill[i] << std::endl;
		count++;
	}
}
void Menu::printinvalidScreen() {
	system("cls");
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << invalidScreen[i] << '\n';
	}
	std::cout << invalidScreen[MAX_Y - 1];
	Sleep(SCREEN_SLEEP);
}

void Menu::printinvalidLastScreen() {
	system("cls");
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << invalidLastScreen[i] << '\n';
	}
	std::cout << invalidLastScreen[MAX_Y - 1];
	Sleep(SCREEN_SLEEP);
}

