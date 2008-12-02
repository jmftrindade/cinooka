#ifndef _INTERFACE
#define _INTERFACE

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>

#include "interface/image.h"
#include "objects/Cue.h"
#include "objects/Point.h"
#include "objects/Table.h"
#include "objects/Ball.h"
#include "objects/Shot.h"
#include "physics/physics.h"

class Interface {

private:
	Table* table;
	Cue cue;
	Ball* cueBall;
	BallArray* ba;

	GLuint floorTextureId;
	GLuint wallTextureId;
	GLuint cueTextureId;
	GLuint floorId;
	GLuint floorAndWallsId;

	//void initFloor();
	void initFloorAndWalls();
public:
	Interface();
	~Interface();
	void init();
	void drawEnvironment();
	void drawBalls();
	void drawCue(Shot *shot, bool guideLine);

	Table *getTable() const;
	void setTable(Table *table);
	Ball *getCueBall() const;
	void setCueBall(Ball *cueBall);
	BallArray *getBallsArray() const;
	void setBallsArray(BallArray *ba);
};

#endif
