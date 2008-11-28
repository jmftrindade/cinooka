#include "Point3d.h"

Point3d::Point3d() {
		x = y = z = 0.0;
};

Point3d::Point3d(GLdouble x, GLdouble y, GLdouble z) {
		this->x = x;
		this->y = y;
		this->z = z;
};

Point3d::~Point3d(){};
