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
#include "camera/Camera.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif

#define SPACE_KEY 32

//#define NUM_BALLS 10 /*de 0(branca) a 9*/
#define NUM_BALLS 16 /*de 0(branca) a 9*/

enum MODE {
	DIRECTION, SHOT, PHYSICS, FIM
};

struct Player {
    int p_id;
    bool final;
    int total_balls;

    Player();
    Player(int id, int total);
};

class Game {

private:
    //NOSSAS
    Player P1;
    Player P2;
    bool cueBall_collided;
    int ball_hit;
    //FIM DAS NOSSAS
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
	void processEnd();
	bool illegalMove(int pl);
	void processEndGame(int pl);
	bool isOver();
	bool checkCueBall();
	void respawnCueBall();
	void physicsInterface();
	int op_id(int pl);

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
