
#ifndef CUE_H_
#define CUE_H_

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "interface/image.h"
#include "objects/Point.h"

#define INITIAL_DISTANCE 0.3
#define STRENGTH_FACTOR 10.0

class Cue {

private:

	Vector position;
	float angle;
	float strength;

	GLuint cueTextureId;
	GLUquadricObj *cueId;

public:
	Cue();
	virtual ~Cue();

	void init();
	void draw();
	Vector getPosition() const;

	void setPosition(Vector position);

	float getAngle() const;

	void setAngle(float strength);

	float getStrength() const;

	void setStrength(float strength);

};

#endif /* CUE_H_ */
