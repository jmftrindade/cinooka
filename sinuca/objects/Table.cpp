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

GLfloat tab_col_spec[4] = {0.0, 0.0, 0.0, 0.0};
GLfloat tab_col_diff[4] = {0.05, 0.4, 0.13, 1.0};
GLfloat tab_col_amb [4];
GLfloat wood_col_spec[4] = {0.7, 0.7, 0.7, 1.0};
GLfloat wood_col_spec_null[4] = {0.0, 0.0, 0.0, 1.0};
GLfloat wood_col_diff[4] = {0.25, 0.08, 0.02, 1.0};
GLfloat wood_col_diff2[4] = {0.7, 0.7, 0.7, 1.0};
GLfloat wood_col_diff3[4] = {0.07, 0.07, 0.07, 1.0};
GLfloat wood_col_amb  [4];
GLfloat wood_col_amb2 [4];
GLfloat wood_col_amb3 [4];
GLfloat wood_col_shin = 100.0;
//    GLfloat dia_col_spec[4] = {1.0, 0.9, 0.4, 1.0};
GLfloat dia_col_spec[4] = {0.5, 0.5, 0.5, 1.0};
GLfloat dia_col_diff[4] = {0.8, 0.7, 0.1, 1.0};
GLfloat dia_col_amb [4];
GLfloat dia_col_shin = 100.0;
GLfloat bumpers_col_spec[4] = {1.0, 1.0, 1.0, 1.0};
GLfloat bumpers_col_diff[4] = {0.3, 0.3, 0.3, 1.0};
GLfloat bumpers_col_amb [4];
GLfloat bumpers_col_shin = 100.0;
GLfloat hole_col_spec[4] = {0.6, 0.6, 0.6, 0.6};
GLfloat hole_col_diff[4] = {0.2, 0.2, 0.2, 1.0};
GLfloat hole_col_amb [4];
GLfloat hole_col_shin = 1000.0;
GLfloat t_gen_params[] = {8.0,0.0,0.0,0.0};
GLfloat s_gen_params[] = {0.0,1.0,0.0,0.0};	

void Table::init() {
	//table
	GLUquadricObj *quadric;

	//tableTextureId = loadTexture((char*) "images/table.sgi");
	tableTextureId = LoadBitmap((char*) "images/table_frame.bmp");
	upTableTextureId = LoadBitmap((char*) "images/green.bmp");
	legTableTextureId = LoadBitmap((char*) "images/table_frame.bmp");

	glBindTexture(GL_TEXTURE_2D, tableTextureId);

	tableId = glGenLists(1);
	glNewList(tableId, GL_COMPILE_AND_EXECUTE);

	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);

	//lados fora
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f); // normal Z
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 2.5, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 4.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(2.0, 1.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 4.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(2.0, 0.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 2.5, Z_DIMENSION + TABLE_SPACE);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f); // normal -Z
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 2.5, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(2.0, 1.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(2.0, 0.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 2.5, -(Z_DIMENSION + TABLE_SPACE));
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f); // normal -X
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 2.5, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 4.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 2.5, -(Z_DIMENSION + TABLE_SPACE));
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f); // normal X
	glTexCoord2f(0.0, 0.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 2.5, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 4.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(1.0, 0.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 2.5, -(Z_DIMENSION + TABLE_SPACE));
	glEnd();

	//lado dentro
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f); // normal -Z
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-X_DIMENSION, 2.5, Z_DIMENSION);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-X_DIMENSION, 4.0, Z_DIMENSION);
	glTexCoord2f(2.0, 1.0);
	glVertex3f(X_DIMENSION, 4.0, Z_DIMENSION);
	glTexCoord2f(2.0, 0.0);
	glVertex3f(X_DIMENSION, 2.5, Z_DIMENSION);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f); // normal Z
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-X_DIMENSION, 2.5, -Z_DIMENSION);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-X_DIMENSION, 4.0, -Z_DIMENSION);
	glTexCoord2f(2.0, 1.0);
	glVertex3f(X_DIMENSION, 4.0, -Z_DIMENSION);
	glTexCoord2f(2.0, 0.0);
	glVertex3f(X_DIMENSION, 2.5, -Z_DIMENSION);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f); // normal X
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-X_DIMENSION, 2.5, Z_DIMENSION);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-X_DIMENSION, 4.0, Z_DIMENSION);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-X_DIMENSION, 4.0, -Z_DIMENSION);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-X_DIMENSION, 2.5, -Z_DIMENSION);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f); // normal -X
	glTexCoord2f(0.0, 0.0);
	glVertex3f(X_DIMENSION, 2.5, Z_DIMENSION);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(X_DIMENSION, 4.0, Z_DIMENSION);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(X_DIMENSION, 4.0, -Z_DIMENSION);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(X_DIMENSION, 2.5, -Z_DIMENSION);
	glEnd();

	//lado cima
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0); // normal apontando pra cima
	glTexCoord2f(0.0, 0.0);
	glVertex3f(X_DIMENSION, 4.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(X_DIMENSION, 4.0, Z_DIMENSION);
	glTexCoord2f(5.0, 1.0);
	glVertex3f(-(X_DIMENSION), 4.0, Z_DIMENSION);
	glTexCoord2f(5.0, 0.0);
	glVertex3f(-(X_DIMENSION), 4.0, Z_DIMENSION + TABLE_SPACE);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0); // normal apontando pra cima
	glTexCoord2f(0.0, 0.0);
	glVertex3f(X_DIMENSION, 4.0, -Z_DIMENSION);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(X_DIMENSION, 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(5.0, 1.0);
	glVertex3f(-(X_DIMENSION), 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(5.0, 0.0);
	glVertex3f(-(X_DIMENSION), 4.0, -Z_DIMENSION);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0); // normal apontando pra cima
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 4.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-X_DIMENSION, 4.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(2.0, 1.0);
	glVertex3f(-X_DIMENSION, 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(2.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0); // normal apontando pra cima
	glTexCoord2f(0.0, 0.0);
	glVertex3f(X_DIMENSION, 4.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 4.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(2.0, 1.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(2.0, 0.0);
	glVertex3f(X_DIMENSION, 4.0, -(Z_DIMENSION + TABLE_SPACE));
	glEnd();

	// topo da mesa	
	glBindTexture(GL_TEXTURE_2D, upTableTextureId);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0); // normal apontando pra cima
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-X_DIMENSION, 3.48, Z_DIMENSION);
	glTexCoord2f(0.0, 4.0);
	glVertex3f(X_DIMENSION, 3.48, Z_DIMENSION);
	glTexCoord2f(4.0, 4.0);
	glVertex3f(X_DIMENSION, 3.48, -Z_DIMENSION);
	glTexCoord2f(4.0, 0.0);
	glVertex3f(-X_DIMENSION, 3.48, -Z_DIMENSION);
	glEnd();
	
	// draw a big centered leg :-)
	glBindTexture(GL_TEXTURE_2D, legTableTextureId);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -0.3f, 1.0f); // normal -Z
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-X_DIMENSION+2.0, -4.21, Z_DIMENSION);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-X_DIMENSION-1.0, 2.5, Z_DIMENSION+1.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(X_DIMENSION+1.0	, 2.5, Z_DIMENSION+1.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(X_DIMENSION-2.0, -4.21, Z_DIMENSION);
	glEnd();
	
	glBegin(GL_QUADS);
	glNormal3f(1.0f, -0.3f, 0.0f); // normal X
	glTexCoord2f(0.0, 0.0);
	glVertex3f(X_DIMENSION-2.0, -4.21, Z_DIMENSION);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(X_DIMENSION+1.0, 2.5, Z_DIMENSION+1.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(X_DIMENSION+1.0, 2.5, -Z_DIMENSION-1.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(X_DIMENSION-2.0, -4.21, -Z_DIMENSION);
	glEnd();
	
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -0.3f, -1.0f); // normal -Z
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-X_DIMENSION+2.0, -4.21, -Z_DIMENSION);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-X_DIMENSION-1.0, 2.5, -Z_DIMENSION-1.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(X_DIMENSION+1.0	, 2.5, -Z_DIMENSION-1.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(X_DIMENSION-2.0, -4.21, -Z_DIMENSION);
	glEnd();
	
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, -0.3f, 0.0f); // normal -X
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-X_DIMENSION+2.0, -4.21, Z_DIMENSION);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-X_DIMENSION-1.0, 2.5, Z_DIMENSION+1.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-X_DIMENSION-1.0, 2.5, -Z_DIMENSION-1.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-X_DIMENSION+2.0, -4.21, -Z_DIMENSION);
	glEnd();

    glPopMatrix();
	

	//buracos
	GLUquadricObj* quadricHole;
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	for (int i = 0; i < 6; ++i) {
		quadricHole = gluNewQuadric();
		glColor4f(0.0, 0.0, 0.0, 1.0);
		glPushMatrix();
		glTranslatef(holes[i].getX(), 3.5, holes[i].getZ());
		glRotatef(180, 1, 1, 0);
		gluSphere(quadricHole, HOLE_RADIUS, 2, 12);
		glPopMatrix();
	}
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

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
