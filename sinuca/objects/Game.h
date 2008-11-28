#ifndef _GAME
#define _GAME

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "physics/physics.h"
#include "interface/interface.h"
#include "Timer/Timer.h"
#include "objects/Shot.h"
#include "objects/Table.h"
#include "objects/Ball.h"
#include "camera/camera.h"

#define SPACE_KEY 32

#define NUM_BALLS 10 /*de 0(branca) a 9*/

enum MODE {
	DIRECTION, SHOT, PHYSICS
};

class Game {

private:
	int currentPlayer;
	Shot shot;

	Table table;
	BallArray ba;
	Ball* cueBall;

	Interface interface;
	Physics physics;

	MODE mode;
	Timer physicsTimer;
	Timer animationTimer;

	float strLevel;
	float strength;
	void setDirection(int key);
	void initShot();
	void initializeGame();
	void executeShot(int key);
	void applyPhysics();
	void draw();
	void drawShot();
	void drawSelection();
	bool turnEnded();
	bool isOver();
	bool checkCueBall();
	void respawnCueBall();
	void physicsInterface();

public:

    Camera camera;
	Game();
	void initGL();
	void processKey(int key);
	void processMouse(int x, int y, int button, int state);
	void processMotion(int x, int y);
	void loop();
};

#endif
