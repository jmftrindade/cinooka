#include "Game.h"
#include <stdio.h>
//#include "sounds/sound.h"

#if !defined(GLUT_WHEEL_UP)
#  define GLUT_WHEEL_UP   3
#  define GLUT_WHEEL_DOWN 4
#endif

Player::Player() {
	p_id = 1;
	final = false;
	total_balls = 7;
	previous_total_balls = 7;
}

Player::Player(int id, int total) {
	p_id = id;
	final = false;
	total_balls = total;
	previous_total_balls = total;
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

/*void Game::initSound() {
    hit = Sound("sounds/hit.wav",AL_FALSE);
    music = Sound("sounds/hit.wav",AL_FALSE);
    ALfloat lis_pos[] = {0.0, 0.0, 0.0};
    ALfloat lis_vel[] = {0.0, 0.0, 0.0};
    ALfloat lis_ori[] = {0.0, 0.0, -1.0, 0.0, 1.0, 0.0};
    music.SetListener(lis_pos,lis_vel,lis_ori);
    ALfloat src_pos[] = {0.0, 0.0, 0.0};
    ALfloat src_vel[] = {0.0, 0.0, 0.0};
    music.SetSource(src_pos,src_vel);
    music.PlaySound();
}*/

void Game::initializeGame() {
	currentPlayer = 1;
	printf("Player %d turn.\n",currentPlayer);
	cueBall_collided = false;
	mode = DIRECTION;
	cam_mode = TABLE;
	ba.initializeBallArray(NUM_BALLS);

	cueBall = ba.getBall(0);

	interface.setBallsArray(&ba);
	interface.setCueBall(cueBall);
	interface.setTable(&table);

	physicsTimer.start();
	animationTimer.start();
	ball_camera.at.x = cueBall->getXPosition();
	ball_camera.at.y = 3.75;
	ball_camera.at.z = cueBall->getZPosition();
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
	printf("Player %d turn.\n",currentPlayer);
	cueBall_collided = false;
	//printf("total 1: %d  total 2: %d\n",P1.total_balls,P2.total_balls);

	ball_camera.at.x = cueBall->getXPosition();
	ball_camera.at.y = 3.75;
	ball_camera.at.z = cueBall->getZPosition();
	if (cam_mode == BALL) {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();        
		gluLookAt(ball_camera.eye.x,ball_camera.eye.y,ball_camera.eye.z,
				ball_camera.at.x,ball_camera.at.y,ball_camera.at.z,
				ball_camera.up.x,ball_camera.up.y,ball_camera.up.z);
	};
	return true;
}

void Game::processEnd() {
	bool illegalMovePlayer1 = illegalMove(1);
	bool illegalMovePlayer2 = illegalMove(2);

	updateBallCount();
	
	if (currentPlayer == 1) {
		if (illegalMovePlayer1) {
			printf("Illegal move from player 1! Player 2 has now one ball less.\n");
			//printf("ball hit: %d \ncollided: %b \ntotal: %d \n)",ball_hit,cueBall_collided,P1.total_balls);
			
			// nao precisa atualizar a contagem aqui, ja que o killplayerball atualiza
			killPlayerBall(2);
			respawnCueBall();
			
			// se o player 2 ficou sem nenhuma bola apos disso
			if (P2.total_balls == 0) {
				processEndGame(2);
			}

		}
		if (!ba.getBall(8)->inGame()) {
			if (P1.total_balls == 0) {
				processEndGame(1);
			} else {
				processEndGame(2);
			}
		}
	}
	if (currentPlayer == 2) {
		if (illegalMovePlayer2) {
			printf("Illegal move from player 2! Player 1 has now one ball less.\n");
			//printf("ball hit: %d \ncollided: %b \ntotal: %d \n)",ball_hit,cueBall_collided,P2.total_balls);

			// nao precisa atualizar a contagem aqui, ja que o killplayerball atualiza
			killPlayerBall(1);
			respawnCueBall();

			// se o player 2 ficou sem nenhuma bola apos disso
			if (P1.total_balls == 0) {
				processEndGame(1);
			}
		}
		if (!ba.getBall(8)->inGame()) {
			if (P2.total_balls == 0) {
				processEndGame(2);
			} else {
				processEndGame(1);
			}
		}

	}

	// garantir a permanencia de um jogador apos ter feito alguma bola

	// garantidamente fui eu que encacapei uma ou mais bolas.
	if (P1.total_balls < P1.previous_total_balls) {
		// gambiarra para continuar jogando o player 1
		if (!illegalMovePlayer1) {
			currentPlayer = op_id(currentPlayer);
		}
	}
	// atualiza o numero de bolas anterior
	P1.previous_total_balls = P1.total_balls;
	
	// garantidamente fui eu que encacapei uma ou mais bolas.
	if (P2.total_balls < P2.previous_total_balls) {
		// gambiarra para continuar jogando o player 1
		if (!illegalMovePlayer2) {
			currentPlayer = op_id(currentPlayer);
		}
	}
	// atualiza o numero de bolas anterior
	P2.previous_total_balls = P2.total_balls;

}

// update ball count for both players
void Game::updateBallCount() {
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
	if (!cueBall_collided) {
		return true;
	}
	if (pl == 1) {
		if ( (ball_hit > 8)  || 
				((ball_hit == 8) && (P1.total_balls != 0)) ) {
			return true;
		}
	}
	if (pl == 2) {
		if ( (ball_hit < 8)  || 
				((ball_hit == 8) && (P2.total_balls != 0)) ) {
			return true;
		}
	}
	return false;
}


// mata a bola de um jogador pl e recoloca a bola branca no lugar
void Game::killPlayerBall(int pl) {
	int minBall = 1, maxBall = 7;
	// bolas 9 a 16
	if (pl == 2) {
		minBall = 9;
		maxBall = 15;
	}
	Ball* b;
	for (int i = minBall; i <= maxBall; i++) {
		b = ba.getBall(i);
		if (b->inGame()) {
			//printf("MATEI BOLA PLAYER %d\n!!!!", pl);
			b->kill();
			if (pl == 1) {
				P1.total_balls--;
				P1.previous_total_balls--;
			}
			if (pl == 2) {
				P2.total_balls--;
				P2.previous_total_balls--;
			}
			return;
		}
	}
}

void Game::processEndGame(int pl) {
	mode = FIM;
	printf("Player %d won! Congratulations! :-D\n",pl);
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
				//playHit(myBall);
				physics.ballCollision(myBall, otherBall);
				if ((myBall == cueBall) and (!cueBall_collided)) {
					ball_hit = otherBall->getNumber();
					//printf("bola branca bateu na %d\n",ball_hit);
					cueBall_collided = true;
				}
			}
		}
	}
}

/*void Game::playHit(Ball* ball) {
    ALfloat lis_pos[] = {camera.eye.x, camera.eye.y, camera.eye.z};
    ALfloat lis_vel[] = {0.0, 0.0, 0.0};
    ALfloat lis_ori[] = {camera.at.x, camera.at.y, camera.at.z, 0.0, 1.0, 0.0};
    hit.SetListener(lis_pos,lis_vel,lis_ori);
    ALfloat src_pos[] = {ball->getXPosition(), 0.0, ball->getZPosition()};
    ALfloat src_vel[] = {0.0, 0.0, 0.0};
    hit.SetSource(src_pos,src_vel);
    hit.PlaySound();
}*/

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
		shot.addAngle(0.5);
		break;
	case GLUT_KEY_LEFT:
		shot.addAngle(-0.5);
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
	if (key == 'j') {
		if (cam_mode == TABLE) {
			cam_mode = BALL;
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(ball_camera.eye.x,ball_camera.eye.y,ball_camera.eye.z,
					ball_camera.at.x,ball_camera.at.y,ball_camera.at.z,
					ball_camera.up.x,ball_camera.up.y,ball_camera.up.z);
		}
		else {
			cam_mode = TABLE;
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(camera.eye.x,camera.eye.y,camera.eye.z,
					camera.at.x,camera.at.y,camera.at.z,
					camera.up.x,camera.up.y,camera.up.z);
		}
	};
	if (key == 'n')
		initializeGame();
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

void Game::processMouse(int x, int y, int button, int state) {
	Camera camera;
	if (cam_mode == TABLE)
		camera = this->camera;
	else
		camera = this->ball_camera;

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
	if (cam_mode == TABLE)
		this->camera = camera;
	else
		this->ball_camera = camera;
	//glutPostRedisplay();
}

void Game::processMotion(int x, int y) {
	Camera camera;
	if (cam_mode == TABLE)
		camera = this->camera;
	else
		camera = this->ball_camera;

	if (camera.is_panning)
		camera.pan((float)x,(float)y);
	if (camera.is_rotating)
		camera.rotate((float)x,(float)y);

	if (cam_mode == TABLE)
		this->camera = camera;
	else
		this->ball_camera = camera;
	//glutPostRedisplay();
}

