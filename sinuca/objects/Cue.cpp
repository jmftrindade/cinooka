
#include "Cue.h"

Cue::Cue() {
	angle = 0.0;
	strength = 0.0;
}

Cue::~Cue() {
}

void Cue::init() {
	//cueTextureId = loadTexture((char*) "images/cue.sgi");
	cueTextureId = LoadBitmap((char*) "images/queue.bmp");
	cueId = gluNewQuadric();
}

void Cue::draw() {
	glBindTexture(GL_TEXTURE_2D, cueTextureId);

	gluQuadricTexture(cueId, GL_TRUE);

	glPushMatrix();
	glTranslatef(position.getX(), 3.7, position.getZ());
	glRotatef(angle-180, 0, 1, 0);
	glTranslatef(0.0, 0.0, strength*STRENGTH_FACTOR + INITIAL_DISTANCE);
	glRotatef(-13, 1, 0, 0);
	gluCylinder(cueId, 0.05, 0.1, 13.0, 32, 12);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_TEXTURE_2D);
	//glColor3f(1.0, 1.0, 1.0);
	glTranslatef(position.getX(), 3.7, position.getZ());
	glRotatef(angle-180, 0, 1, 0);
	glTranslatef(0.0, 0.0, -5.5);
	glScalef(0.05, 0.05, 11.0);
	glutSolidCube(1);
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();

}

Vector Cue::getPosition() const {
	return position;
}

void Cue::setPosition(Vector position) {
	this->position = position;
}

float Cue::getAngle() const {
	return angle;
}

void Cue::setAngle(float angle) {
	this->angle = angle;
}

void Cue::setStrength(float strength) {
	this->strength = strength;
}

float Cue::getStrength() const {
	return strength;
}
