#include "Game.h"
#include <stdio.h>

#if !defined(GLUT_WHEEL_UP)
#  define GLUT_WHEEL_UP   3
#  define GLUT_WHEEL_DOWN 4
#endif

Player::Player() {
    p_id = 1;
    final = false;
    total_balls = 7;
}

Player::Player(int id, int total) {
    p_id = id;
    final = false;
    total_balls = total;
}

Game::Game() {
    P1 = Player(1,7);
    P2 = Player(1,7);
	currentPlayer = 1;
	initializeGame();
}

void Game::initGL() {
	interface.init();
}

void Game::initializeGame() {
    currentPlayer = 1;
    printf("current player: %d\n",currentPlayer);
    cueBall_collided = false;
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
    processEnd();
    currentPlayer = op_id(currentPlayer);
    printf("current player: %d\n",currentPlayer);
    cueBall_collided = false;
    printf("total 1: %d  total 2: %d\n",P1.total_balls,P2.total_balls);
	return true;
}

void Game::processEnd() {
    if (currentPlayer == 1) {
        if ((ball_hit > 8) || (!cueBall_collided) || ((ball_hit == 8) && (P1.total_balls != 0))) {
            printf("ball hit: %d \ncollided: %b \ntotal: %d \n)",ball_hit,cueBall_collided,P1.total_balls);
            if(!illegalMove(1))
                processEndGame(2);
        }
        if (!ba.getBall(8)->inGame()) {
            if (P1.total_balls == 0)
                processEndGame(1);
            else
                processEndGame(2);
        }
    }
    if (currentPlayer == 2) {
        if ((ball_hit < 8) || (!cueBall_collided) || ((ball_hit == 8) && (P2.total_balls != 0))) {
            if(!illegalMove(2))
                processEndGame(1);
        }
        if (!ba.getBall(8)->inGame()) {
            if (P1.total_balls == 0)
                processEndGame(2);
            else
                processEndGame(1);
        }
    }
    Ball* b;
    int balls1 = 0;
    int balls2 = 0;
    for (int i = 1; i < 16; i++) {
        b = ba.getBall(i);
        if (b->inGame()){
            if (i < 8)
                balls1++;
            if (i > 8)
                balls2++;
        }
    }
    P1.total_balls = balls1;
    P2.total_balls = balls2;
}

bool Game::illegalMove(int pl) {
    printf("illegal move\n");
    if (pl == 1) {
        Ball* b;
        for (int i = 9; i < 16; i++) {
            b = ba.getBall(i);
            if (b->inGame()) {
                b->kill();
                return true;
            }
        }
        return false;
    }
    if (pl == 2) {
        Ball* b;
        for (int i = 1; i < 8; i++) {
            b = ba.getBall(i);
            if (b->inGame()) {
                b->kill();
                return true;
            }
        }
        return false;
    }
}

void Game::processEndGame(int pl) {
    mode = FIM;
    printf("acabou, jogador vencedor: %d\n",pl);
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
				if ((myBall == cueBall) and (!cueBall_collided)) {
				    ball_hit = otherBall->getNumber();
                    printf("bola branca bateu na %d\n",ball_hit);
                    cueBall_collided = true;
				}
			}
		}
	}
}

int Game::op_id(int pl) {
    if (pl == 1)
        return 2;
    return 1;
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
		    if (mode != FIM)
                initializeGame();
		}
		else {
		    if (mode != FIM)
                mode = DIRECTION;
		}
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
    case FIM:
        if (key == GLUT_KEY_F2)
            initializeGame();
        break;
	default:
		break;
	}
}

void Game::processMouse(int x, int y, int button, int state) {
    switch(button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) {
            camera.is_panning = true;
            camera.save((float)x,(float)y);
        } else {
            camera.is_panning = false;
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN) {
            camera.is_rotating = true;
            camera.save((float)x,(float)y);
        } else {
            camera.is_rotating = false;
        }
        break;
    case GLUT_WHEEL_UP:
        camera.zoom(-2.0);
        break;
    case GLUT_WHEEL_DOWN:
        camera.zoom(2.0);
    //glutPostRedisplay();
    }
    //glutPostRedisplay();
}

void Game::processMotion(int x, int y) {
    if (camera.is_panning)
        camera.pan((float)x,(float)y);
    if (camera.is_rotating)
        camera.rotate((float)x,(float)y);
    //glutPostRedisplay();
}

