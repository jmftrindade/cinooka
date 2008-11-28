
#ifndef _PHYSICS
#define _PHYSICS

//Corrigir as posições na colisão
#define FACTOR 0.0001
//Conservação de energia
#define CONSERVATION 0.5
//Coeficiente de atrito
#define ATTRITION 0.00025

#include "objects/Point.h"
#include "objects/Table.h"
#include "objects/Ball.h"
#include "objects/Shot.h"

class Physics {

private:
	enum enumTable { NONE = 0, LEFT, RIGHT, UP, DOWN };
	int tableRegion;

	enum enumType { RAY = 1, CORNER };
	int type;

	int rayIndex;
	int* collisionOrder;
	int totalCollisions;
public:
	int firstCollision;

private:
	void attrition (Ball* b);
	void energyLoss (Ball* b);
	int insertDistance (float* distArray, int size, float dist);
	void insertIndex (int* indexArray, int size, int value, int position);

	bool checkBallCollision (Ball* a, Ball* b, float* pDist);
	void checkTableCollision (Table* t, Ball* b);
	bool checkHoleCollision (Table* t, Ball* b, int hole);

	void fixBallCollision (Ball* a, Ball* b);
	void fixTableCollision (Ball* b);

public:
	Physics();
	~Physics();

	void getCollisionOrder (BallArray* ba, int ballIndex);
	bool hasCollisions();
	int getCollision();

	void movement (Ball* b);

	void ballCollision (Ball* a, Ball* b);
	bool tableCollision (Table* t, Ball* b);
	bool holeAreaCollision (Table* t, Ball* b);
	void respawnCollision (Table* t, BallArray* ba, bool upward);

	void hitCueBall (Ball* cueBall, Shot* shot);
};

#endif
