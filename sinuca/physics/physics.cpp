//TODO implementar a colisão com as bordas da mesa na função checkTableCollision

#include "physics.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Physics::Physics() {
	collisionOrder = (int*) malloc(sizeof(int) * 16);
	firstCollision = 0;
}

Physics::~Physics() {
	free(collisionOrder);
}

void Physics::attrition(Ball* b) {
	if (b->isMoving()) {
		float attrict = ATTRITION;
		Vector speed = b->getSpeed();

		float angle = b->calculateSpeedAngle();
		float oldX;

		speed.vectorRotation(angle);
		oldX = speed.getX();

		if (oldX == 0) {
			return;
		} else if (oldX > 0) {
			speed.setX(oldX - attrict);
		} else {
			speed.setX(oldX + attrict);
		}

		if (oldX * speed.getX() < 0) {
			b->resetSpeed();
		} else {
			speed.vectorRotation(-angle);
			b->setSpeed(&speed);
		}
	}
}

void Physics::energyLoss(Ball* b) {

	Vector ballSpeed = b->getSpeed();
	Vector loss;

	loss.setVector(CONSERVATION, CONSERVATION);
	ballSpeed.mulVector(&loss);

	b->setSpeed(&ballSpeed);
}

void Physics::movement(Ball* b) {
	Vector ballSpeed;

	attrition(b);
	ballSpeed = b->getSpeed();
	b->addPosition(&ballSpeed);
}

int Physics::insertDistance(float* distArray, int size, float dist) {
	int i, j;

	for (i = 0; i < size; i++) {
		if (dist <= distArray[i]) {
			for (j = size; j > i; j--) {
				distArray[i] = distArray[i - 1];
			}
			distArray[i] = dist;
			break;
		}
	}

	return i;
}

void Physics::insertIndex(int* indexArray, int size, int value, int position) {
	int i;

	for (i = size; i > position; i--) {
		indexArray[i] = indexArray[i - 1];
	}
	indexArray[i] = value;
}

void Physics::getCollisionOrder(BallArray* ba, int ballIndex) {
	int i, position;
	float* distArray = (float*) malloc(sizeof(float) * (ba->getSize()
			- ballIndex));
	float dist;
	Ball* myBall = ba->getBall(ballIndex);
	Ball* current;

	totalCollisions = 0;

	for (i = ballIndex + 1; i < ba->getSize(); i++) {

		current = ba->getBall(i);

		if (current->inGame()) {
			if (checkBallCollision(myBall, current, &dist)) {
				position = insertDistance(distArray, totalCollisions, dist);
				insertIndex(collisionOrder, totalCollisions, i, position);
				totalCollisions = totalCollisions + 1;
			}
		}
	}

	if (!ballIndex && !firstCollision) {
		firstCollision = collisionOrder[0];
	}
	free(distArray);
}

bool Physics::hasCollisions() {
	return (totalCollisions != 0);
}

int Physics::getCollision() {
	totalCollisions--;
	return (collisionOrder[0]);
}

bool Physics::checkBallCollision(Ball* a, Ball* b, float* pDist) {
	float dist, radiusSum;
	Vector aPos, bPos;

	aPos = a->getPosition();
	bPos = b->getPosition();

	dist = aPos.sqrDistance(&bPos);
	radiusSum = 4 * BALL_RADIUS * BALL_RADIUS;

	if (pDist)
		*pDist = dist;

	if (dist <= radiusSum) {
		return (true);
	} else {
		return (false);
	}
}

// Colisao bola-mesa
void Physics::checkTableCollision(Table* t, Ball* b) {

	tableRegion = NONE;

	// colisio with x plane
    if (b->getXPosition() + BALL_RADIUS >= X_DIMENSION) {
            tableRegion = RIGHT;
    } else if (b->getXPosition() - BALL_RADIUS <= -X_DIMENSION) {
            tableRegion = LEFT;
    } 
    // colision with z plane
    else if (b->getZPosition() + BALL_RADIUS >= Z_DIMENSION) {
            tableRegion = DOWN;
    } else if (b->getZPosition() - BALL_RADIUS <= -Z_DIMENSION) {
            tableRegion = UP;
    }
    
}

bool Physics::checkHoleCollision(Table* t, Ball* b, int hole) {
	Point p1, p2;
	float sqrDist, sqrRadius;

	p1 = t->getHoleCenter(hole);
	p2 = b->getPosition();

	sqrDist = p1.sqrDistance(&p2);
	sqrRadius = HOLE_RADIUS * HOLE_RADIUS;

	if (sqrDist <= sqrRadius) {
		return (true);
	}

	return (false);
}

void Physics::fixBallCollision(Ball* a, Ball* b) {

	while (checkBallCollision(a, b, NULL)) {
		if (a->getXPosition() > b->getXPosition()) {
			a->addXPosition(FACTOR);
			b->subXPosition(FACTOR);
		} else {
			b->addXPosition(FACTOR);
			a->subXPosition(FACTOR);
		}
	}
}

void Physics::fixTableCollision(Ball* b) {
	switch (tableRegion) {
	case RIGHT:
		// Canto direito
		b->setXPosition(X_DIMENSION- BALL_RADIUS - FACTOR);
		break;

	case LEFT:
		// Canto esquerdo
		b->setXPosition(-X_DIMENSION + BALL_RADIUS + FACTOR);
		break;

	case DOWN:
		// Canto inferior
		b->setYPosition(Z_DIMENSION- BALL_RADIUS - FACTOR);
		break;

	case UP:
		// Canto superior
		b->setYPosition(-Z_DIMENSION + BALL_RADIUS + FACTOR);
		break;

	default:
		break;
	}
}

void Physics::ballCollision(Ball* a, Ball* b) {
	float angle;
	Vector aCenter, bCenter;

	aCenter = a->getPosition();
	bCenter = b->getPosition();
	angle = aCenter.calculateAngle(&bCenter);

	a->rotateSpeed(angle);
	b->rotateSpeed(angle);

	a->tradeXSpeed(b);

	// Tira do estado de colisao
	fixBallCollision(a, b);

	// Desfaz rotacao
	a->rotateSpeed(-angle);
	b->rotateSpeed(-angle);

}

bool Physics::tableCollision(Table* t, Ball* b) {

	checkTableCollision(t, b);

	switch (tableRegion) {
	case 1:
		// Canto direito
		b->reverseXSpeed();
		break;
	case 2:
		// Canto esquerdo
		b->reverseXSpeed();
		break;
	case 3:
		// Canto inferior
		b->reverseZSpeed();
		break;
	case 4:
		// Canto superior
		b->reverseZSpeed();
		break;
	default:
		return (false);
		break;
	}

	energyLoss(b);
	fixTableCollision(b);

	return (true);
}

bool Physics::holeAreaCollision(Table* t, Ball* b) {
	int hole;
	Point p0, p2;

	if (!(t->holeArea(b->getPosition()))) {
		// Fora da regiao de risco
		return false;
	}

	// Buraco da possivel colisao
	hole = t->nearestHole(b->getPosition());

	if (checkHoleCollision(t, b, hole)) {
		// Colisao com buraco
		b->kill();
		b->resetSpeed();
		return true;
	}

	return false;
}

void Physics::respawnCollision(Table* t, BallArray* ba, bool upward) {
	int i, indexSize;
	int indexArray[16];
	float cueXPos, xPos, limit;

	Ball* cueBall = ba->getBall(0);

	limit = 2 * BALL_RADIUS;
	cueXPos = cueBall->getXPosition();
	indexSize = 0;

	tableCollision(t, cueBall);

	for (i = 1; i < ba->getSize(); i++) {
		xPos = (ba->getBall(i))->getXPosition();

		if (cueXPos - limit <= xPos && xPos <= cueXPos + limit) {
			indexArray[indexSize++] = i;
		}
	}

	bool collision = true;
	while (collision) {
		for (i = 0; i < indexSize; i++) {

			if (checkBallCollision(cueBall, ba->getBall(indexArray[i]), NULL)) {
				while (checkBallCollision(cueBall, ba->getBall(indexArray[i]),
						NULL)) {
					if (upward) {
						cueBall->subYPosition(1.0);
					} else {
						cueBall->addYPosition(1.0);
					}
				}
				break;
			}
		}
		collision = false;
	}
}

void Physics::hitCueBall(Ball* cueBall, Shot* shot) {
	float angle, str;
	Vector v;

	angle = shot->getAngle();
	str = shot->getStr();

	v.setX(str * sin((angle) * M_PI / 180.0));
	v.setZ(str * cos((angle) * M_PI / 180.0));
	cueBall->setSpeed(&v);
}
