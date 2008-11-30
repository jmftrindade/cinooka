
// TODO Camera
// TODO Iluminação

#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "objects/Game.h"
#include "objects/Point3d.h"

Game game;

// Light Parameters
static GLfloat	LightAmb[] = {1.0f, 1.0f, 1.0f, 1.0f};				// Ambient Light
static GLfloat	LightDif[] = {1.0f, 1.0f, 1.0f, 1.0f};				// Diffuse Light
static GLfloat	LightPos[] = {4.0f, 4.0f, 6.0f, 1.0f};				// Light Position
static GLfloat	SpecRef[] = {1.0f, 1.0f, 1.0f, 1.0f};				// Material color


void display() {
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

	game.loop();

	glutSwapBuffers();
}

void reshape(int w, int h) {

	if (h == 0)
		h = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45, 1.0f * w / h, 1, 200);

	Point3d eye = game.camera.eye;
    Point3d at = game.camera.at;
    Point3d up = game.camera.up;
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(eye.x,eye.y,eye.z,at.x,at.y,at.z,up.x,up.y,up.z);
    //gluLookAt(20, 0, 43, 0, 0, 0, 0.0f, 1.0f, 0.0f);
}

void specialkey(int key, int x, int y) {
	game.processKey(key);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);

	if (key == 32)
		game.processKey(32);
	
	if (key == 'o') {
		game.camera.zoom(-2.0);
	}
	
	if (key == 'l') {
		game.camera.zoom(2.0);
	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    game.processMouse(x,y,button,state);
}

void motion(int x, int y) {
    game.processMotion(x,y);
}

void init_gl(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);

	glutCreateWindow("Sinuca");
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutIdleFunc(display);
	glutSpecialFunc(specialkey);

	// Iluminacao
    glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
    glClearDepth(1.0f);                                 // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                             // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations
    glEnable(GL_TEXTURE_2D);                            // Enable 2D Texture Mapping

    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);         // Set The Ambient Lighting For Light0
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);         // Set The Diffuse Lighting For Light0
    glLightfv(GL_LIGHT0, GL_POSITION, LightPos);        // Set The Position For Light0

    glEnable(GL_LIGHT0);                                // Enable Light 0
    glEnable(GL_LIGHTING);                              // Enable Lighting

    /*glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT, GL_SPECULAR, SpecRef);
    glMateriali(GL_FRONT, GL_SHININESS, 128);*/


}

int main(int argc, char **argv) {

	init_gl(argc, argv);
	game.initGL();

	glutMainLoop();
	return (0);

}
