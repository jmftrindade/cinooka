#include "Game.h"

Game::Game() {
	currentPlayer = 1;
	initializeGame();
}

void Game::initGL() {
	interface.init();
}

void Game::initializeGame() {
	mode = DIRECTION;
	ba.initializeBallArray(NUM_BALLS);

	cueBall = ba.getBall(0);

	interface.setBallsArray(&ba);
	interface.setCueBall(cueBall);
	interface.setTable(&table);

	physicsTimer.start();
	animationTimer.start();
}

void Game::draw() {
	interface.drawEnvironment();
	interface.drawBalls();
}

void Game::drawShot() {
	interface.drawCue(&shot, true);
}

void Game::drawSelection() {
	interface.drawCue(&shot, false);
}

bool Game::isOver() {
	Ball* b;
	for (int i = 1; i < ba.getSize(); i++) {
		b = ba.getBall(i);
		if (b->inGame()) {
			return false;
		}
	}
	return true;
}

bool Game::turnEnded() {
	Ball* b;
	int i;
	for (i = 0; i < ba.getSize(); i++) {
		b = ba.getBall(i);
		if (b->inGame()) {
			if (b->isMoving()) {
				return false;
			}
		}
	}
	return true;
}

bool Game::checkCueBall() {
	if (!cueBall->inGame()) {
		respawnCueBall();
		return true;
	}
	return false;
}

void Game::respawnCueBall() {

	shot.setAngle(90.0);
	cueBall->whitePosition();
	cueBall->putInGame();

	physics.respawnCollision(&table, &ba, true);
	drawSelection();

	cueBall->setYPosition((int) cueBall->getZPosition());
}

void Game::physicsInterface() {

	int i;
	Ball* myBall;
	Ball* otherBall;

	for (i = 0; i < ba.getSize(); i++) {

		myBall = ba.getBall(i);

		if (myBall->inGame()) {
			physics.movement(myBall);

			physics.holeAreaCollision(&table, myBall);

			physics.tableCollision(&table, myBall);

			physics.getCollisionOrder(&ba, i);

			while (physics.hasCollisions()) {
				otherBall = ba.getBall(physics.getCollision());
				physics.ballCollision(myBall, otherBall);
			}
		}
	}
}

void Game::setDirection(int key) {
	switch (key) {
	case GLUT_KEY_UP:
		shot.addAngle(5.0);
		break;
	case GLUT_KEY_DOWN:
		shot.addAngle(-5.0);
		break;
	case GLUT_KEY_RIGHT:
		shot.addAngle(1.0);
		break;
	case GLUT_KEY_LEFT:
		shot.addAngle(-1.0);
		break;
	case SPACE_KEY:
		initShot();
		break;
	default:
		break;
	}
}
void Game::initShot() {
	strLevel = 1.57;
	strength = 0;
	mode = SHOT;
}
void Game::executeShot(int key) {
	if (key == SPACE_KEY) {
		physics.hitCueBall(cueBall, &shot);
		mode = PHYSICS;
	}
}
void Game::applyPhysics() {
	if (physicsTimer.elapsed() < 0.007)
		return;
	physicsTimer.start();
	if (!turnEnded()) {
		physicsInterface();
	} else {
		if(isOver()){
			initializeGame();
		}
		mode = DIRECTION;
	}
}

void Game::loop() {
	draw();
	switch (mode) {
	case DIRECTION:
		checkCueBall();
		drawShot();
		break;
	case SHOT:
		drawShot();
		if (animationTimer.elapsed() > 0.025) {
			strength = 21 - (abs((int) (20 * (sin(strLevel)))) + 1);
			strLevel += 0.05;
			shot.setStr(strength/75);
			animationTimer.start();
		}
		break;
	case PHYSICS:
		applyPhysics();
		break;
	default:
		break;
	}
}

void Game::processKey(int key) {
	switch (mode) {
	case DIRECTION:
		setDirection(key);
		break;
	case SHOT:
		executeShot(key);
		break;
	default:
		break;
	}
}
