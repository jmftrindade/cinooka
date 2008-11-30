#ifndef _TABLE
#define _TABLE

//						 Up
//		 ___________________________________
//		|									|
//		|									|
//		|									|
//Left	|			    Mesa				|Right
//		|									|
//		|									|
//		|									|
//		|___________________________________|
//						Down
//


#define HOLE_RADIUS 0.6

//Centro da mesa
#define CENTER_X 0.0
#define CENTER_Z 0.0

//Comprimento da mesa
#define X_LENGTH 30.0
#define Z_LENGTH 16.0

#define TABLE_SPACE 1.0

#define HOLE_AREA_X 0.6
#define HOLE_AREA_Z 0.6
#define X_DIMENSION (CENTER_X + X_LENGTH/2.0)
#define Z_DIMENSION (CENTER_Z + Z_LENGTH/2.0)

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "interface/image.h"
#include "interface/texture.h"
#include "interface/material_light.h"
#include "Point.h"

class Table {

private:
	GLuint legTableTextureId;
	GLuint upTableTextureId;
	GLuint tableTextureId;
	GLuint tableId;

	Point holes[6];

public:
	// Constructor
	Table();

	void init();
	void draw();

	Point getHoleCenter(int hole);

	// Other
	bool holeArea(Point p);
	int nearestHole(Point p);
};

#endif
