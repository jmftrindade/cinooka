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
	

#endif /* _MAT_LIGHT */
