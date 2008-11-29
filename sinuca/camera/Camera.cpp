#include "camera.h"

Camera::Camera(){
    at = Point3d(0.0,0.0,0.0);
	up = Point3d(0.0,1.0,0.0);
	theta = M_PI/3;
	phi = M_PI/3;
	R = 43.0;
    eye = transf_coord();
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
    //gluLookAt(eye.x,eye.y,eye.z,at.x,at.y,at.z,up.x,up.y,up.z);
};

Camera::~Camera(){};

void Camera::update(float x, float y){
    float new_phi = phi_old - (y-y_old)/50.0;	// atualiza phi de acordo com o movimento do mouse no eixo y
    if (new_phi > (M_PI/2.2))								// normaliza phi no intervalo (0,PI)
        new_phi = M_PI/2.2 + 0.001;
    else if (new_phi < 0)
        new_phi = 0.001;

    float new_theta = theta_old - (x-x_old)/50.0; //atualiza theta de acordo com o movimento do mouse no eixo x

    theta = new_theta;
    phi = new_phi;
    //printf("phi: %f  theta: %f  R: %f\n",phi,theta,R);
};

void Camera::save(float x, float y){
    x_old = x;
    y_old = y;
    theta_old = theta;
    phi_old = phi;
}

Point3d Camera::transf_coord(){
    Point3d result;
    result.z = (GLdouble)R*sin(phi)*cos(theta);
    result.x = (GLdouble)R*sin(phi)*sin(theta);
    result.y = (GLdouble)R*cos(phi);
    return result;
}

void Camera::zoom(float x){
    R += x;
    if (R < 23.0)
        R = 23.0;
    if (R > 47.0)
        R = 47.0;
    eye = transf_coord();
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(eye.x,eye.y,eye.z,at.x,at.y,at.z,up.x,up.y,up.z);
    //printf("R: %f\n", R);
}

void Camera::pan(float x, float z){
//    at.x = (x_pan - x_old)/50.0;
//    at.z = (z_pan - y_old)/50.0;
//    glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//    gluLookAt(eye.x,eye.y,eye.z,at.x,at.y,at.z,up.x,up.y,up.z);
    printf("PAN NAO IMPLEMENTADO");
}

void Camera::rotate(float x, float y){
    update(x,y);
    eye = transf_coord();
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(eye.x,eye.y,eye.z,at.x,at.y,at.z,up.x,up.y,up.z);
}
