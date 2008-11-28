#ifndef POINT3D_H_INCLUDED
#define POINT3D_H_INCLUDED

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Point3d {

public:
    GLdouble x;
	GLdouble y;
	GLdouble z;

	Point3d();
	Point3d(GLdouble x, GLdouble y, GLdouble z);
    ~Point3d();
};

#endif // POINT3D_H_INCLUDED
