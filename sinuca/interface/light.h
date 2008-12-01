#ifndef _MAT_LIGHT
#define _MAT_LIGHT

#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#   include <GLUT/glut.h>
#   include <OpenGL/glu.h>
#else
#   include <GL/glut.h>
#   include <GL/glu.h>
#endif

extern void setWoodenMaterial();
extern void setMetallicMaterial();
extern void buildShadowMatrix( float fMatrix[16], float fLightPos[4], float fPlane[4] );
extern GLfloat* getShadowMatrix();
extern void findPlane( GLfloat plane[4], GLfloat v0[3], GLfloat v1[3], GLfloat v2[3]);
	

#endif /* _MAT_LIGHT */
