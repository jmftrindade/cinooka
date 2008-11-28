#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <stdio.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "objects/Point3d.h"

class Camera {

public:
    Point3d eye;
    Point3d at;
    Point3d up;
    float theta;
    float phi;
    float R;
    bool is_panning;
    bool is_rotating;
    float x_old;
    float y_old;
    float theta_old;
    float phi_old;

    Camera();
    ~Camera();
    void update(float x, float y);
    void save(float x, float y);
    void zoom(float x);
    void pan(float x, float y);
    void rotate(float x, float y);

private:
    Point3d transf_coord();
};

#endif // CAMERA_H_INCLUDED
