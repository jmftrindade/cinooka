#include "Table.h"
//#include "interface/light.h"

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

	//tableTextureId = loadTexture((char*) "images/table.sgi");
	tableTextureId = LoadBitmap((char*) "images/table_frame.bmp");
	upTableTextureId = LoadBitmap((char*) "images/green.bmp");
	legTableTextureId = LoadBitmap((char*) "images/table_frame.bmp");

	GLuint marbleTextureId = LoadBitmap((char*) "images/white_marble.bmp");

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

	// parte inferior
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f); // normal Z
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 1.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 2.3, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(2.0, 1.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 2.3, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(2.0, 0.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 1.0, Z_DIMENSION + TABLE_SPACE);
	glEnd();

	// parte interna
	glBindTexture(GL_TEXTURE_2D, marbleTextureId);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f); // normal Z
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE)+0.5, 2.0, Z_DIMENSION + TABLE_SPACE-0.5);
	glTexCoord2f(0.0, 6.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE)+0.5, 3.0, Z_DIMENSION + TABLE_SPACE-0.5);
	glTexCoord2f(6.0, 6.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE-0.5, 3.0, Z_DIMENSION + TABLE_SPACE-0.5);
	glTexCoord2f(6.0, 0.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE-0.5, 2.0, Z_DIMENSION + TABLE_SPACE-0.5);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, tableTextureId);
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

	// parte inferior
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f); // normal -Z
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 1.0, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 2.3, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(2.0, 1.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 2.3, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(2.0, 0.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 1.0, -(Z_DIMENSION + TABLE_SPACE));
	glEnd();

	// parte interna
	glBindTexture(GL_TEXTURE_2D, marbleTextureId);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f); // normal -Z
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE)+0.5, 2.0, -(Z_DIMENSION + TABLE_SPACE)+0.5);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE)+0.5, 3.0, -(Z_DIMENSION + TABLE_SPACE)+0.5);
	glTexCoord2f(2.0, 1.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE-0.5, 3.0, -(Z_DIMENSION + TABLE_SPACE)+0.5);
	glTexCoord2f(2.0, 0.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE-0.5, 2.0, -(Z_DIMENSION + TABLE_SPACE)+0.5);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, tableTextureId);
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

	// parte inferior
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f); // normal -X
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 1.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 2.3, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 2.3, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE), 1.0, -(Z_DIMENSION + TABLE_SPACE));
	glEnd();

	// parte interna
	glBindTexture(GL_TEXTURE_2D, marbleTextureId);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f); // normal -X
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE)+0.5, 2.0, Z_DIMENSION + TABLE_SPACE-0.5);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE)+0.5, 3.0, Z_DIMENSION + TABLE_SPACE-0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE)+0.5, 3.0, -(Z_DIMENSION + TABLE_SPACE)+0.5);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-(X_DIMENSION + TABLE_SPACE)+0.5, 2.0, -(Z_DIMENSION + TABLE_SPACE)+0.5);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, tableTextureId);
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

	// parte inferior
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f); // normal X
	glTexCoord2f(0.0, 0.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 1.0, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 2.3, Z_DIMENSION + TABLE_SPACE);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 2.3, -(Z_DIMENSION + TABLE_SPACE));
	glTexCoord2f(1.0, 0.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE, 1.0, -(Z_DIMENSION + TABLE_SPACE));
	glEnd();

	// parte interna
	glBindTexture(GL_TEXTURE_2D, marbleTextureId);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f); // normal X
	glTexCoord2f(0.0, 0.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE-0.5, 2.0, Z_DIMENSION + TABLE_SPACE-0.5);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE-0.5, 3.0, Z_DIMENSION + TABLE_SPACE-0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE-0.5, 3.0, -(Z_DIMENSION + TABLE_SPACE)+0.5);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(X_DIMENSION + TABLE_SPACE-0.5, 2.0, -(Z_DIMENSION + TABLE_SPACE)+0.5);
	glEnd();


	//lado dentro
	glBindTexture(GL_TEXTURE_2D, tableTextureId);
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
	glBindTexture(GL_TEXTURE_2D, marbleTextureId);
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

	glBindTexture(GL_TEXTURE_2D, tableTextureId);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0); // normal apontando pra cima
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-(X_DIMENSION+TABLE_SPACE), 2.3, Z_DIMENSION+TABLE_SPACE);
	glTexCoord2f(0.0, 4.0);
	glVertex3f(X_DIMENSION+TABLE_SPACE, 2.3, Z_DIMENSION+TABLE_SPACE);
	glTexCoord2f(4.0, 4.0);
	glVertex3f(X_DIMENSION+TABLE_SPACE, 2.3, -(Z_DIMENSION+TABLE_SPACE));
	glTexCoord2f(4.0, 0.0);
	glVertex3f(-(X_DIMENSION+TABLE_SPACE), 2.3, -(Z_DIMENSION+TABLE_SPACE));
	glEnd();


	// draw 4 legs
	glBindTexture(GL_TEXTURE_2D, legTableTextureId);
	glPushMatrix();
	glScalef(2.5, 6.0, 2.5);

	// used to calculate shadow
	/*GLfloat *shadowMatrix = getShadowMatrix(SHADOW_PLANE_FLOOR);

	// draw shadow
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glColor3f(0.2f, 0.2f, 0.2f); // Shadow's color
	glPushMatrix();
	glMultMatrixf((GLfloat *)shadowMatrix);
	glTranslatef(X_DIMENSION-9.2, -0.3, Z_DIMENSION-5.1);
	drawLeg(1);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);*/

	// draw leg
	glPushMatrix();
	glTranslatef(X_DIMENSION-9.2, -0.3, Z_DIMENSION-5.1);
	drawLeg(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-X_DIMENSION+9.2, -0.3, -Z_DIMENSION+5.1);
	drawLeg(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(X_DIMENSION-9.2, -0.3, -Z_DIMENSION+5.1);
	drawLeg(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-X_DIMENSION+9.2, -0.3, Z_DIMENSION-5.1);
	drawLeg(1);
	glPopMatrix();

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

void Table::drawLeg(GLfloat size) {
	static GLfloat n[6][3] =
	{
			{-1.0, 0.0, 0.0},
			{0.0, 1.0, 0.0},
			{1.0, 0.0, 0.0},
			{0.0, -1.0, 0.0},
			{0.0, 0.0, 1.0},
			{0.0, 0.0, -1.0}
	};
	static GLint faces[6][4] =
	{
			{0, 1, 2, 3},
			{3, 2, 6, 7},
			{7, 6, 5, 4},
			{4, 5, 1, 0},
			{5, 6, 2, 1},
			{7, 4, 0, 3}
	};
	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

	for (i = 5; i >= 0; i--) {
		glBegin(GL_QUADS);
		glNormal3fv(&n[i][0]);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv(&v[faces[i][0]][0]);
		glTexCoord2f(0.0, 1.0);
		glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2f(1.0, 1.0);
		glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2f(1.0, 0.0);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}


