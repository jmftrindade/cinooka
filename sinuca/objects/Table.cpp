#include "Table.h"

// Constructor
Table::Table() {
	holes[0].setVector(-X_DIMENSION, Z_DIMENSION);
	holes[1].setVector(0.0, Z_DIMENSION);
	holes[2].setVector(X_DIMENSION, Z_DIMENSION);
	holes[3].setVector(X_DIMENSION, -Z_DIMENSION);
	holes[4].setVector(0.0, -Z_DIMENSION);
	holes[5].setVector(-X_DIMENSION, -Z_DIMENSION);
}

void Table::init() {
	//table
	GLUquadricObj *quadric;

	tableTextureId = loadTexture((char*) "images/table.sgi");
	upTableTextureId = loadTexture((char*) "images/up.sgi");

	glBindTexture(GL_TEXTURE_2D, tableTextureId);

	tableId = glGenLists(1);
	glNewList(tableId, GL_COMPILE_AND_EXECUTE);

	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);

	//lados fora
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 2.5, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 4.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 4.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 2.5, Z_DIMENSION + TABLE_SPACE);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 2.5, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(1.0, 1.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(1.0, 0.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 2.5, -(Z_DIMENSION + TABLE_SPACE));
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 2.5, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 4.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(2.0, 1.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(2.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 2.5, -(Z_DIMENSION + TABLE_SPACE));
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 2.5, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 4.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(2.0, 1.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(2.0, 0.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 2.5, -(Z_DIMENSION + TABLE_SPACE));
	glEnd();

	//lado dentro
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-X_DIMENSION, 2.5, Z_DIMENSION);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-X_DIMENSION, 4.0, Z_DIMENSION);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(X_DIMENSION, 4.0, Z_DIMENSION);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(X_DIMENSION, 2.5, Z_DIMENSION);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-X_DIMENSION, 2.5, -Z_DIMENSION);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-X_DIMENSION, 4.0, -Z_DIMENSION);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(X_DIMENSION, 4.0, -Z_DIMENSION);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(X_DIMENSION, 2.5, -Z_DIMENSION);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-X_DIMENSION, 2.5, Z_DIMENSION);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-X_DIMENSION, 4.0, Z_DIMENSION);
	glTexCoord2f(2.0, 1.0);
	glVertex3f(-X_DIMENSION, 4.0, -Z_DIMENSION);
	glTexCoord2f(2.0, 0.0);
	glVertex3f(-X_DIMENSION, 2.5, -Z_DIMENSION);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(X_DIMENSION, 2.5, Z_DIMENSION);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(X_DIMENSION, 4.0, Z_DIMENSION);
	glTexCoord2f(2.0, 1.0);
	glVertex3f(X_DIMENSION, 4.0, -Z_DIMENSION);
	glTexCoord2f(2.0, 0.0);
	glVertex3f(X_DIMENSION, 2.5, -Z_DIMENSION);
	glEnd();

	//lado cima
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-(X_DIMENSION), 4.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(X_DIMENSION, 4.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(X_DIMENSION, 4.0, Z_DIMENSION);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-(X_DIMENSION), 4.0, Z_DIMENSION);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-(X_DIMENSION), 4.0, -Z_DIMENSION);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(X_DIMENSION, 4.0, -Z_DIMENSION);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(X_DIMENSION, 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-(X_DIMENSION), 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 4.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-X_DIMENSION, 4.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-X_DIMENSION, 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(X_DIMENSION, 4.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 4.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(1.0, 0.0);
	glVertex3f(X_DIMENSION, 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glEnd();

	glBindTexture(GL_TEXTURE_2D, upTableTextureId);
	//glColor3f(0.099, 0.578, 0.165);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-X_DIMENSION, 3.48, Z_DIMENSION);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(X_DIMENSION, 3.48, Z_DIMENSION);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(X_DIMENSION, 3.48, -Z_DIMENSION);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-X_DIMENSION, 3.48, -Z_DIMENSION);
	glEnd();

	//buracos
	GLUquadricObj* quadricHole;
	glDisable(GL_TEXTURE_2D);
	for (int i = 0; i < 6; ++i) {
		quadricHole = gluNewQuadric();
		glColor4f(0.0, 0.0, 0.0, 1.0);
		glPushMatrix();
		glTranslatef(holes[i].getX(), 3.5, holes[i].getZ());
		glRotatef(180, 1, 1, 0);
		gluSphere(quadricHole, 0.5, 2, 12);
		glPopMatrix();
	}
	glEnable(GL_TEXTURE_2D);

	glEndList();
}

void Table::draw() {
	glBindTexture(GL_TEXTURE_2D, tableTextureId);
	glCallList(tableId);
}

Point Table::getHoleCenter(int hole) {
	return (holes[hole]);
}

// Other
bool Table::holeArea(Point p) {
	float x = p.getX();
	float z = p.getZ();

	if ((z > -Z_DIMENSION + HOLE_AREA_Z) && (z < Z_DIMENSION - HOLE_AREA_Z)) {

		return false;

		if ((x > -X_DIMENSION + HOLE_AREA_X) && (x < -HOLE_AREA_X)) {
			return false;
		}
		if ((x < X_DIMENSION - HOLE_AREA_X) && (x > HOLE_AREA_X)) {
			return false;
		}
	}

	return true;
}

int Table::nearestHole(Point p) {
	float x, z;
	x = p.getX();
	z = p.getZ();

	if ((x <= 10 * HOLE_AREA_X) && (x >= -10 * HOLE_AREA_X)) {
		if (z > 0.0)
			return 1;
		else
			return 4;
	}
	if (x < HOLE_AREA_X) {
		if (z > 0.0)
			return 0;
		else
			return 5;
	}
	if (x > HOLE_AREA_X) {
		if (z > 0.0)
			return 2;
	}
	return 3;
}
