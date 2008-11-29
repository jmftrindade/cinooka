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
	//FIXME Carregar textura do chão
    floorId = glGenLists(1);
    glNewList(floorId, GL_COMPILE_AND_EXECUTE);
    //floor
    float floor_area = 40.0;
    glBindTexture(GL_TEXTURE_2D, floorTextureId);

    glPushMatrix();
    glTranslatef(0.0, -4.21, 0.0);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-floor_area, 0, floor_area);
    glTexCoord2f(0.0, 2.0);
    glVertex3f(floor_area, 0, floor_area);
    glTexCoord2f(2.0, 2.0);
    glVertex3f(floor_area, 0, -floor_area);
    glTexCoord2f(2.0, 0.0);
    glVertex3f(-floor_area, 0, -floor_area);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, -4.21, 0.0);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-floor_area, 0, floor_area);
    glTexCoord2f(0.0, 2.0);
    glVertex3f(-floor_area, 0, -floor_area);
    glTexCoord2f(2.0, 2.0);
    glVertex3f(-floor_area, floor_area, -floor_area);
    glTexCoord2f(2.0, 0.0);
    glVertex3f(-floor_area, floor_area, floor_area);
    glEnd();
    glPopMatrix();

    glEndList();	
}

void Interface::drawEnvironment() {
	// TODO desenhar chao
    table->draw();
    glBindTexture(GL_TEXTURE_2D, floorTextureId);
    glCallList(floorId);
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
