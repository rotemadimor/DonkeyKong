#pragma once

#include <iostream>
#include "Board.h"
#include "utils.h"

static constexpr int MAX_Y = 25;
static constexpr int SCREEN_SLEEP = 800;

class Menu {


    const char* menu[MAX_Y] = {

        // 01234567890123456789012345678901234567890123456789012345678901234567890123456789
          "================================================================================", // 0
          "                                                                                ", // 1
          "    DDDD   OOO   N   N  K   K  EEEEE  Y   Y    K   K   OOO   N   N  GGGG        ", // 2
          "    D   D O   O  NN  N  K  K   E       Y Y     K  K   O   O  NN  N  G           ", // 3
          "    D   D O   O  N N N  KKK    EEEE     Y      KK     O   O  N N N  G  GG       ", // 4
          "    D   D O   O  N  NN  K  K   E        Y      K  K   O   O  N  NN  G   G       ", // 5
          "    DDDD   OOO   N   N  K   K  EEEEE    Y      K   K   OOO   N   N  GGGG        ", // 6
          "                                                                                ", // 7
          "                                                                                ", // 8
          "                                                                                ", // 9
          "                                                                                ", // 10
          "                                                                                ", // 11
          "                     (1) Start a new game                                       ", // 12
          "                     (8) Present instructions and keys                          ", // 13
          "                     (9) EXIT                                                   ", // 14
          "                                                                                ", // 15
          "                                                                                ", // 16
          "                                                                                ", // 17
          "                                                                                ", // 18
          "                  This game is dedicated to Corinne Allal,                      ", // 19
          "               and to all to the survivors of the Nova party,                   ", // 20
          "                   and to everyone who is a Zan Nadir.                          ", // 21
          "                                                                                ", // 22
          "                                                                                ", // 23
          "================================================================================"  // 24
    };

    const char* instructions[MAX_Y] = {

        // 01234567890123456789012345678901234567890123456789012345678901234567890123456789
          "================================================================================", // 0
          "                                                                                ", // 1
          "                                                                                ", // 2
          "                                                                                ", // 3
          "                         DONKEY KONG - INSTRUCTIONS                             ", // 4
          "                                                                                ", // 5
          "       Welcome to Donkey Kong!                                                  ", // 6
          "                                                                                ", // 7
          "       Guide Mario through the levels and save the girl from Donkey Kong!       ", // 8
          "                                                                                ", // 9
          "        Controls:                                                               ", // 10
          "                                                                                ", // 11
          "         - Use the keys A,D,W to move left, right, and jump.                    ", // 12
          "                                                                                ", // 13
          "         - Press ESC to pause the game.                                         ", // 14
          "                                                                                ", // 15
          "         - Avoid the barrels and other hazards!                                 ", // 16
          "                                                                                ", // 17
          "         - Reach Pauline to complete each level and move to the next one!       ", // 18
          "                                                                                ", // 19
          "                                                                                ", // 20
          "              Good luck, and have fun playing Donkey Kong!                      ", // 21
          "                                                                                ", // 22
          "                                                                                ", // 23
          "================================================================================"  // 24
    };

    const char* livesLeft[MAX_Y] = {

        // 01234567890123456789012345678901234567890123456789012345678901234567890123456789
          "================================================================================", // 0
          "                                                                                ", // 1
          "                                                                                ", // 2
          "                                                                                ", // 3
          "                                                                                ", // 4
          "                                                                                ", // 5
          "                                                                                ", // 6
          "                                                                                ", // 7
          "       You Lost! :(                                                             ", // 8
          "                                                                                ", // 9
          "                 You still have   lives left                                    ", // 10
          "                                                                                ", // 11
          "                                                                                ", // 12
          "                                                                                ", // 13
          "                                                                                ", // 14
          "                                                                                ", // 15
          "                                                                                ", // 16
          "                                                                                ", // 17
          "                                                                                ", // 18
          "                                                                                ", // 19
          "                                                                                ", // 20
          "                                                                                ", // 21
          "                                                                                ", // 22
          "                                                                                ", // 23
          "================================================================================"  // 24
    };

    const char* gameOver[MAX_Y] = {

        // 01234567890123456789012345678901234567890123456789012345678901234567890123456789
           "================================================================================", // 0
          "                                                                                ", // 1
          "                                                                                ", // 2
          "                                                                                ", // 3
          "                                                                                ", // 4
          "                                                                                ", // 5
          "                                                                                ", // 6
          "                                                                                ", // 7
          "                         You lost all your lives :(                             ", // 8
          "                                                                                ", // 9
          "                         try again to save Pauline                              ", // 10
          "                                                                                ", // 11
          "                                                                                ", // 12
          "                                                                                ", // 13
          "                                                                                ", // 14
          "                                                                                ", // 15
          "                                                                                ", // 16
          "                                                                                ", // 17
          "                                                                                ", // 18
          "                                                                                ", // 19
          "                                                                                ", // 20
          "                                                                                ", // 21
          "                                                                                ", // 22
          "                                                                                ", // 23
          "================================================================================"  // 24
    };

    const char* win[MAX_Y] = {

        // 01234567890123456789012345678901234567890123456789012345678901234567890123456789
           "================================================================================", // 0
           "                                                                                ", // 1
           "                                                                                ", // 2
           "                                                                                ", // 3
           "                                                                                ", // 4
           "          *           *         *     *                                         ", // 5
           "              *  *        *                                                     ", // 6
           "        *                     *  *                                              ", // 7
           "               *   YOU WON!          *                                          ", // 8
           "            *    *              *                                               ", // 9
           "                      *                                                         ", // 10
           "                                                                                ", // 11
           "                                                                                ", // 12
           "                   You reached pauline and saved her!                           ", // 13
           "                                                                                ", // 14
           "                                                                                ", // 15
           "                                                                                ", // 16
           "                                                                                ", // 17
           "                                                                                ", // 18
           "                                                                                ", // 19
           "                                                                                ", // 20
           "                                                                                ", // 21
           "                                                                                ", // 22
           "                                                                                ", // 23
           "================================================================================"  // 24
    };
public:
    void printInstructions();
    void printLoseScreen(int lives);
    void printMenu();
    void printWinScreen();
    void printGameOverScreen();

};

   
