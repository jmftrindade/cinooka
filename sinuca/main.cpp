
// TODO Camera
// TODO Iluminação

#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>

#include "objects/Game.h"

Game game;

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
	gluPerspective(45, 1.0f * w / h, 1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 40, 13, 0, 0, 0, 0.0f, 1.0f, 0.0f);

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
	glutPostRedisplay();
}

void init_gl(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);

	glutCreateWindow("Sinuca");
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(display);
	glutSpecialFunc(specialkey);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);

}

int main(int argc, char **argv) {

	init_gl(argc, argv);

	game.initGL();

	glutMainLoop();
	return (0);

}
