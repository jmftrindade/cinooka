//TODO carregar e aplicar a textura na bola

#include "Ball.h"
#include "interface/light.h"
#include <iostream>
#include <string>
#include <sstream>

void Ball::init() {
	    //TODO carregar a textura de acordo com o numero da bola
        std::ostringstream ballTexturePath;
        ballTexturePath << "images/" << number << ".bmp";
        ballTextureId = LoadBitmap((char*) ballTexturePath.str().c_str());
        ballSphereMapTexId = LoadBitmap((char*) "images/sphere_map.bmp");
        //ballLightFlareTexId = LoadBitmap((char*) "images/lightflare.bmp");
}

void Ball::draw() {	
	//Abaixo estão apenas as partes para deslocar e rolar a bola
	float rotation = SPEED_FACTOR * (speed.getX() * speed.getX() + speed.getZ()
			* speed.getZ());
	
        ballId = gluNewQuadric();

	// shadow matrix
        GLfloat *shadowMatrix = getShadowMatrix();
        
        // draw shadow
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glColor3f(0.2f, 0.2f, 0.2f); // Shadow's color
        glPushMatrix();
        glMultMatrixf((GLfloat *)shadowMatrix);
        glTranslatef(center.getX(), 3.5 + BALL_RADIUS, center.getZ());
        glRotatef(rotation, ROTATION_FACTOR*(-speed.getZ()), 0, ROTATION_FACTOR
        * speed.getX());
	gluSphere(ballId, BALL_RADIUS, 32, 16);
	glPopMatrix();
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);

	// textures...
        gluQuadricNormals(ballId, GL_SMOOTH);                        // Generate Smooth Normals For The Quad
        gluQuadricTexture(ballId, GL_TRUE);                          // Enable Texture Coords For The Quad    
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);    // Set Up Sphere Mapping
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);    // Set Up Sphere Mapping

	glPushMatrix();
	glTranslatef(center.getX(), 3.5 + BALL_RADIUS, center.getZ());
	glRotatef(rotation, ROTATION_FACTOR*(-speed.getZ()), 0, ROTATION_FACTOR
	* speed.getX());
	
	// ball texture
	glColor3f(1.0f, 1.0f, 1.0f);
        glBindTexture(GL_TEXTURE_2D, ballTextureId);
	gluSphere(ballId, BALL_RADIUS, 32, 16);
	
	glBindTexture(GL_TEXTURE_2D, ballSphereMapTexId);
	glColor4f(1.0f, 1.0f, 1.0f, 0.4f);			// Set Color To White With 40% Alpha
	glEnable(GL_BLEND);							// Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);			// Set Blending Mode To Mix Based On SRC Alpha
	glEnable(GL_TEXTURE_GEN_S);					// Enable Sphere Mapping
	glEnable(GL_TEXTURE_GEN_T);					// Enable Sphere Mapping

	gluSphere(ballId, BALL_RADIUS, 32, 16);		// Draw Another Sphere Using New Texture
												// Textures Will Mix Creating A MultiTexture Effect (Reflection)
	/*glBindTexture(GL_TEXTURE_2D, ballLightFlareTexId);
	glColor4f(1.0f, 1.0f, 1.0f, 0.4f);			// Set Color To White With 40% Alpha

	gluSphere(ballId, BALL_RADIUS, 32, 16);		// Draw Another Sphere Using New Texture
	*/
	glDisable(GL_TEXTURE_GEN_S);				// Disable Sphere Mapping
	glDisable(GL_TEXTURE_GEN_T);				// Disable Sphere Mapping
	glDisable(GL_BLEND);						// Disable Blending
	
	glPopMatrix();
}

bool Ball::inGame() {
	return (gameStatus);
}

int Ball::getNumber() {
	return (number);
}

Vector Ball::getPosition() {
	return (center);
}

float Ball::getXPosition() {
	return (center.getX());
}

float Ball::getZPosition() {
	return (center.getZ());
}

Vector Ball::getSpeed() {
	return (speed);
}

float Ball::getXSpeed() {
	return (speed.getX());
}

float Ball::getYSpeed() {
	return (speed.getZ());
}

float Ball::getLastAngle() {
	return (speedAngle);
}

void Ball::setPosition(Vector* v) {
	center.setVector(v);
}

void Ball::setXPosition(float x) {
	center.setX(x);
}

void Ball::setYPosition(float y) {
	center.setZ(y);
}

void Ball::setSpeed(Vector* v) {
	speed.setVector(v);
}

void Ball::addPosition(Vector* v) {
	center.addVector(v);
}

void Ball::addXPosition(float value) {
	Vector v(value, 0.0);
	center.addVector(&v);
}

void Ball::addYPosition(float value) {
	Vector v(0.0, value);
	center.addVector(&v);
}

void Ball::subPosition(Vector* v) {
	center.subVector(v);
}

void Ball::subXPosition(float value) {
	Vector v(value, 0.0);
	center.subVector(&v);
}

void Ball::subYPosition(float value) {
	Vector v(0.0, value);
	center.subVector(&v);
}

bool Ball::isMoving() {
	return (speed.getX() != 0.0 || speed.getZ() != 0.0);
}

float Ball::calculateSpeedAngle() {
	Vector v;
	speedAngle = v.calculateAngle(&speed);
	return (speedAngle);
}

void Ball::resetSpeed() {
	speed.setVector(0.0, 0.0);
}

void Ball::addSpeed(Vector* v) {
	speed.addVector(v);
}

void Ball::subSpeed(Vector* v) {
	speed.subVector(v);
}

void Ball::rotateSpeed(float angle) {
	speed.vectorRotation(angle);
}

void Ball::tradeXSpeed(Ball* b) {
	Vector aux1(b->getXSpeed(), getYSpeed());
	Vector aux2(getXSpeed(), b->getYSpeed());

	setSpeed(&aux1);
	b->setSpeed(&aux2);
}

void Ball::reverseXSpeed() {
	Vector aux(-1.0, 1.0);
	speed.mulVector(&aux);
}

void Ball::reverseZSpeed() {
	Vector aux(1.0, -1.0);
	speed.mulVector(&aux);
}

void Ball::putInGame() {
	gameStatus = true;
}

void Ball::kill() {
	gameStatus = false;
}

void Ball::whitePosition() {
	Vector defaultPosition(-9, 0);
	setPosition(&defaultPosition);
}

void BallArray::initializeBallArray(int totalBalls) {
	int i, j, k = 0;

	size = totalBalls;

	for (i = 0; i < size; i++) {
		array[i].number = i;
		array[i].resetSpeed();
		array[i].speedAngle = 0.0;
		array[i].putInGame();
	}

	Vector v;
	array[0].kill();
	array[0].whitePosition();

	for (i = 0; i < 5; i++) {
		for (j = 0; j <= i; j++) {
			v.setX(i * BALL_RADIUS*2 + 7.5);
			v.setZ((i * BALL_RADIUS*2) - (j * BALL_RADIUS*2) - 0.55);
			array[1 + k].setPosition(&v);
			k++;
		}
	}
}

Ball* BallArray::getBall(int number) {
	return (&array[number]);
}

int BallArray::getSize() {
	return size;
}

int BallArray::ballsLeft() {
	int i, n = 0;
	for (i = 1; i < size; i++) {
		if (array[i].inGame()) {
			n++;
		}
	}
	return n;
}
