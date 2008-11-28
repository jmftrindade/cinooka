//TODO renderizar o chão

#include "interface.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

Interface::Interface() {
}

Interface::~Interface() {
}

void Interface::init() {
	table->init();
	cue.init();

	Ball* b;
	for (int i = 0; i < ba->getSize(); i++) {
		b = ba->getBall(i);
		b->init();
		b->draw();
	}
	floorTextureId = loadTexture((char*) "images/floor.sgi");
	initFloor();
}

void Interface::initFloor() {
	//TODO Carregar textura do chão
}

void Interface::drawEnvironment() {
	// TODO desenhar chao
    table->draw();
    glBindTexture(GL_TEXTURE_2D, floorTextureId);
}

void Interface::drawBalls() {
	Ball* b;

	for (int i = 0; i < ba->getSize(); i++) {
		b = ba->getBall(i);
		if (b->inGame())
			b->draw();
	}
}

void Interface::drawCue(Shot* shot, bool guideLine) {
	cue.setPosition(cueBall->getPosition());
	cue.setAngle(shot->getAngle());
	cue.setStrength(shot->getStr());
	cue.draw();
}

Table *Interface::getTable() const {
	return table;
}

void Interface::setTable(Table *table) {
	this->table = table;
}

Ball *Interface::getCueBall() const {
	return cueBall;
}

void Interface::setCueBall(Ball *cueBall) {
	this->cueBall = cueBall;
}

BallArray *Interface::getBallsArray() const {
	return ba;
}

void Interface::setBallsArray(BallArray *ba) {
	this->ba = ba;
}
