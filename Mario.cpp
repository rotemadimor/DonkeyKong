#pragma once
#include "Mario.h"

void Mario::keyPressed(char key) {
	for (size_t i = 0; i < this->mario.numKeys; i++) {
		if (std::tolower(key) == this->mario.keys[i]) {
			this->mario.dir = this->mario.directions[i];
			return;
		}
	}
}

void Mario::moveMario() {
	char nextCharOnBoard = mario.move();
	switch (nextCharOnBoard) {
		case 'H':
			moveOnLadderUp();
			break;
		case 'O':
			hitBarrels();
			break;
		case '$':
			reachedPauline();
		default:
			if (this->mario.IsNextDirectionUp()) {
				jump();
			}
			break;
		}
}



	//if (mario.IsNewLocationValid(newX, newY, nextCharOnBoard)) {
		
	/*	this->mario.x = newX;
		this->mario.y = newY;
	}*/



void Mario::moveOnLadderUp() {
	
	return;
}

void Mario::moveOnFloor() {
	return;
}

void Mario::hitBarrels() {
	return;
}

void Mario::reachedPauline() {
	return;
}

void Mario::jump() {
	if (this->mario.IsNextDirectionLeft()) {
		mario.jumpLeft();
	}
	else if (this->mario.IsNextDirectionRight()) {
		mario.jumpRight();
	}
	else {
		mario.jumpUp();
	}
}
