
#ifndef _POINT
#define _POINT

#include <math.h>

#define Point Vector

class Vector {

private:
	float x;
	float z;

public:
	// Constructors
	Vector ();
	Vector (float x0, float z0);

	// Read properties
	float getX ();
	float getZ ();

	// Write properties
	void setX (float x);
	void setZ (float z);
	void setVector (float x, float z);
	void setVector (Vector* v);

	// Other
	void addVector (Vector* v);
	void subVector (Vector* v);
	void mulVector (Vector* v);
	// Anti-Clockwise Rotation
	void vectorRotation (float angle);
	// Calculate the angle between our Point and another Point (Related to the X axis)
	float calculateAngle (Point* p);
	// Square of the distance between our Point and another Point
	float sqrDistance (Point* p);
};

#endif

