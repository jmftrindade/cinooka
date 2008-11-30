#include "material_light.h"

GLfloat no_mat[4] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat mat_ambient[4] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat mat_ambient_color[4] = {0.8f, 0.8f, 0.2f, 1.0f};
GLfloat mat_diffuse[4] = {0.1f, 0.5f, 0.8f, 1.0f};
GLfloat mat_specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat mat_emission[4] = {0.3f, 0.2f, 0.2f, 0.0f};
GLfloat no_shininess = 0.0f;
GLfloat low_shininess = 5.0f;
GLfloat high_shininess = 100.0f;

/* ambient, diffuse and specular reflection; low shininess */
void setWoodenMaterial() {
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMateriali(GL_FRONT, GL_SHININESS, low_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

/* ambient, diffuse and specular reflection; high shininess */
void setMetallicMaterial() {
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}
