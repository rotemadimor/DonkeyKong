#include <iostream>
#include <windows.h>
#include <conio.h> 
#include <string.h>

#include "Board.h"
#include "utils.h"
#include "Mario.h"
#include "Game.h"
#include "GameToSave.h"
#include "GameFromFile.h"


int main(int argc, char** argv) {
	bool isLoad, isSave, isSilent;
	isLoad = argc > 1 && std::string(argv[1]) == "-load";
	isSilent = isLoad && argc > 2 && std::string(argv[2]) == "-silent";
	isSave = !isLoad && !isSilent && argc>1;
	if (isLoad) {
		GameFromFile gff;
		if (isSilent) {
			gff.SetIsSilent(isSilent);
		}
		gff.run();
	}
	else if(isSave) {
		GameToSave().run();
	}
	else {
		Game().run();
	}
}
