#pragma once
#include <iostream>
#include "utils.h"
#include "Point.h"

class Board {
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;
	const char* originalBoard[MAX_Y] = {

		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "================================================================================", // 0
          "               &                       $                                Lives:  ", // 1
          "       < <=> << >>>>>        =======================                            ", // 2
		  "                             H                   H                              ", // 3
          "                             H                   H                              ", // 4
          "      =<<<<<<<<<<<<<>>>>>>>>>>    ================>>>>>>>>>>                    ", // 5
          "       H                               H                                        ", // 6
          "       H                               H                                        ", // 7
          "       H                               H                                        ", // 8
          "   >>>>=========        >>>>>>>>>>>==============                               ", // 9
          "                                   H            H                               ", // 10
          "       >>>>>>>>>>>>>>>>            H            H                               ", // 11
          "        H                          H            H                               ", // 12
          "        H                     ===========       >>>>>>>>>> >>>>>>>>>>>>>>>>     ", // 13
          "        H                     H                                           H     ", // 14
          "        H                     H                          <<<=========     H     ", // 15
          " >>>>>>>>>>>>>>>>===   <<<========>>>>>>>>>>>>>>           H        H     H     ", // 16
          "                 H                             H           H        H     H     ", // 17
          "                 H                             H           H        H     H     ", // 18
          "                 H                             H           H        H     H     ", // 19
          "         <<=========        <<<<<<<<<<<<<<<===============>>>>      ========    ", // 20
          "           H                                             H                      ", // 21
          "           H                                             H                      ", // 22
          "           H                                             H                      ", // 23
          "================================================================================"  // 24
	};
	char currentBoard[MAX_Y][MAX_X + 1];

public:
	void reset();
	void print() const;
    void printLivesLeft(int lives);
	char getChar(int x, int y) const {
		return currentBoard[y][x];
	}
    void setChar(int x, int y, char ch) {
        currentBoard[y][x] = ch;
    }
    void drawOnBoard(int x, int y) {
        gotoxy(x, y);
        std::cout << getChar(x,y);
    }
    void drawcharOnBoard(int x, int y, char ch) {
        gotoxy(x, y);
        std::cout << ch;
    }
    void drawOnBoard(Point p) {
        drawOnBoard(p.getX(), p.getY());
    }
};