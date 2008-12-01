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
	//floorTextureId = loadTexture((char*) "images/floor.sgi");
	floorTextureId = LoadBitmap((char*) "images/red_carpet.bmp");
	cueTextureId = LoadBitmap((char*) "images/wall_cue.bmp");
	initFloorAndWalls();
}

void Interface::initFloorAndWalls() {
    //floor
    float size = 60.0;
    floorAndWallsId = glGenLists(1);
    glNewList(floorAndWallsId, GL_COMPILE_AND_EXECUTE);
    //glBindTexture(GL_TEXTURE_2D, floorTextureId);
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.0, -5.0, 0.0);
    
    glColor3f(1.0f, 0.0f, 0.0f);
    
    // chao
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f); // normal apontando pra cima
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-size, 0, size);
    glTexCoord2f(0.0, 10.0);
    glVertex3f(size, 0, size);
    glTexCoord2f(10.0, 10.0);
    glVertex3f(size, 0, -size);
    glTexCoord2f(10.0, 0.0);
    glVertex3f(-size, 0, -size);
    glEnd();
    glPopMatrix();

    // parede de tras
    glPushMatrix();
    glTranslatef(0.0, -5.0, 0.0);

    glBegin(GL_QUADS);
    glNormal3f( 1.0f, 0.0f, 0.0f); // normal X
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-size, 0, size);
    glTexCoord2f(0.0, 2.0);
    glVertex3f(-size, 0, -size);
    glTexCoord2f(2.0, 2.0);
    glVertex3f(-size, size, -size);
    glTexCoord2f(2.0, 0.0);
    glVertex3f(-size, size, size);
    glEnd();
    glPopMatrix();
    
    
    // parede da direita
    glPushMatrix();
    glTranslatef(0.0, -5.0, 0.0);

    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, -1.0f); // normal -Z
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-size, size, size);
    glTexCoord2f(0.0, 2.0);
    glVertex3f(size, size, size);
    glTexCoord2f(2.0, 2.0);
    glVertex3f(size, 0, size);
    glTexCoord2f(2.0, 0.0);
    glVertex3f(-size, 0, size);
    glEnd();
    glPopMatrix();
    
    // parede da frente
    glPushMatrix();
    glTranslatef(0.0, -5.0, 0.0);

    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f); // normal -X
    glTexCoord2f(0.0, 0.0);
    glVertex3f(size, size, size);
    glTexCoord2f(0.0, 2.0);
    glVertex3f(size, size, -size);
    glTexCoord2f(2.0, 2.0);
    glVertex3f(size, 0, -size);
    glTexCoord2f(2.0, 0.0);
    glVertex3f(size, 0, size);
    glEnd();
    glPopMatrix();
    
    // parede da esquerda
    glPushMatrix();
    glTranslatef(0.0, -5.0, 0.0);

    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f); // normal Z
    glTexCoord2f(0.0, 0.0);
    glVertex3f(size, size, -size);
    glTexCoord2f(0.0, 2.0);
    glVertex3f(-size, size, -size);
    glTexCoord2f(2.0, 2.0);
    glVertex3f(-size, 0, -size);
    glTexCoord2f(2.0, 0.0);
    glVertex3f(size, 0, -size);
    glEnd();
    glPopMatrix();
    
    glEnable(GL_TEXTURE_2D);
    
    glEndList();	
}

void Interface::drawEnvironment() {
	// TODO desenhar chao
    table->draw();
    glCallList(floorAndWallsId);
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
