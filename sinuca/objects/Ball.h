#ifndef _BALL
#define _BALL

#define BALL_RADIUS 0.25
#define SPEED_FACTOR 150000
#define ROTATION_FACTOR 1000

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "interface/image.h"
#include "interface/texture.h"
#include "Point.h"

class Ball {

	friend class BallArray;

private:
	GLuint ballSphereMapTexId;
	GLuint ballLightFlareTexId;	
	GLuint ballTextureId;
	GLUquadricObj *ballId;

	bool gameStatus;
	int number;

	Vector center;

	Vector speed;
	float speedAngle;

public:
	void init();
	void draw();

	// Read Properties
	bool inGame();
	int getNumber();
	Vector getPosition();
	float getXPosition();
	float getZPosition();
	Vector getSpeed();
	float getXSpeed();
	float getYSpeed();
	float getLastAngle();

	// Write Properties
	void setPosition(Vector* v);
	void setXPosition(float x);
	void setYPosition(float y);
	void setSpeed(Vector* v);

	// Position Functions
	void addPosition(Vector* v);
	void addXPosition(float value);
	void addYPosition(float value);
	void subPosition(Vector* v);
	void subXPosition(float value);
	void subYPosition(float value);

	// Speed functions
	bool isMoving();
	float calculateSpeedAngle();
	void resetSpeed();
	void addSpeed(Vector* v);
	void subSpeed(Vector* v);
	void rotateSpeed(float angle);
	void tradeXSpeed(Ball* b);
	void reverseXSpeed();
	void reverseZSpeed();

	// Other
	void putInGame();
	void kill();
	void whitePosition();
};

class BallArray {

private:
	Ball array[16];
	int size;

public:
	// Array Functions
	void initializeBallArray(int totalBalls);
	Ball* getBall(int number);
	int getSize();
	int ballsLeft();
};

#endif
