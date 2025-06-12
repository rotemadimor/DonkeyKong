#pragma once
#include <iostream>
#include "utils.h"
#include "Point.h"
#include "Ghost.h"
#include <fstream>
#include <vector>

using std::vector;

class Board {
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;
    static constexpr int MAX_STRING_LENGTH = 20;
	//const char* originalBoard[MAX_Y] = {

	//	// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
	//	  "================================================================================", // 0
 //         "               &                       $                            Lives:      ", // 1
 //         "       < <=> << >>>>>        =======================                Hammer:     ", // 2
	//	  "                             H                   H                              ", // 3
 //         "                             H                   H                              ", // 4
 //         "      =<<<<<<<<<<<<<>>>>>>>>>>    ================>>>>>>>>>>                    ", // 5
 //         "       H                               H                                        ", // 6
 //         "       H                               H                                        ", // 7
 //         "       H                               H                                        ", // 8
 //         "   >>>>=========        >>>>>>>>>>>==============                               ", // 9
 //         "                                   H            H                               ", // 10
 //         "       >>>>>>>>>>>>>>>>            H            H                               ", // 11
 //         "        H                          H            H                               ", // 12
 //         "        H                     ===========       >>>>>>>>>> >>>>>>>>>>>>>>>>     ", // 13
 //         "        H                     H                                           H     ", // 14
 //         "        H                     H                          <<<=========     H     ", // 15
 //         " >>>>>>>>>>>>>>>>===   <<<========>>>>>>>>>>>>>>           H        H     H     ", // 16
 //         "                 H                             H           H        H     H     ", // 17
 //         "                 H                             H           H        H     H     ", // 18
 //         "                 H                             H           H        H     H     ", // 19
 //         "         <<=========        <<<<<<<<<<<<<<<===============>>>>      ========    ", // 20
 //         "           H                                             H                      ", // 21
 //         "           H                                             H                      ", // 22
 //         "           H                                             H                      ", // 23
 //         "================================================================================"  // 24
	//};
    char originalBoard[MAX_Y][MAX_X + 1];
	char currentBoard[MAX_Y][MAX_X + 1];
    int xLegend = 75, yLegend = 1;
    int xDonkey, yDonkey;
    bool isSilent = false;

public:
    
	void reset();
	void print() const;
    void printLivesLeft(int lives);
    void printHammerState(bool state);
    void printScore(int score);
    int load(const std::string& filename, Point& pPauline, Point& pMario, Point& pHammer, vector<Ghost*>& pGhostsVec,int lives, int score,long randomSeed);
    int getXDonkey() { return xDonkey; }
    int getYDonkey() { return yDonkey; }
    void setIsSilentBoard(bool _isSilent) { isSilent = _isSilent; }
	char getChar(int x, int y) const {
		return currentBoard[y][x];
	}
    void setChar(int x, int y, char ch) {
        currentBoard[y][x] = ch;
    }
    void drawOnBoard(int x, int y) {
        gotoxy(x, y);
        if (!isSilent) {
            std::cout << getChar(x, y);
        }
    }
    void drawStringAndNumOnBoard(int x, int y,std::string toPrint, int numToPrint){
        gotoxy(x, y);
        if (!isSilent) {
            std::cout << toPrint << numToPrint;
        }
    }
    void drawStringOnBoard(int x, int y, std::string toPrint) {
        gotoxy(x, y);
        if (!isSilent) {
            std::cout << toPrint;
        }
    }
    void drawcharOnBoard(int x, int y, char ch) {
        gotoxy(x, y);
        if (!isSilent) {
            std::cout << ch;
        }
    }
    void drawOnBoard(Point p) {
        drawOnBoard(p.getX(), p.getY());
    }
};