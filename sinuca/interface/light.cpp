#include "light.h"

GLfloat no_mat[4] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat mat_ambient[4] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat mat_ambient_color[4] = {0.8f, 0.8f, 0.2f, 1.0f};
GLfloat mat_diffuse[4] = {0.1f, 0.5f, 0.8f, 1.0f};
GLfloat mat_specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat mat_emission[4] = {0.3f, 0.2f, 0.2f, 0.0f};
GLfloat no_shininess = 0.0f;
GLfloat low_shininess = 5.0f;
GLfloat high_shininess = 100.0f;

GLfloat g_shadowMatrix[16];
GLfloat g_lightPosition[] = { 2.0f, 6.0f, 0.0f, 1.0f }; // World position of light source

struct Vertex
{
    float nx, ny, nz;
    float x, y, z;
};

Vertex g_floorQuad[] =
{
    { 0.0f, 1.0f,  0.0f,  -60.0f, -3.0f, -60.0f },
    { 0.0f, 1.0f,  0.0f,  -60.0f, -3.0f,  60.0f },
    { 0.0f, 1.0f,  0.0f,   60.0f, -3.0f,  60.0f },
    { 0.0f, 1.0f,  0.0f,   60.0f, -3.0f, -60.0f },
};

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


// SHADOW -------------------------

void findPlane( GLfloat plane[4], GLfloat v0[3], GLfloat v1[3], GLfloat v2[3] )
{
    GLfloat vec0[3], vec1[3];

    // Need 2 vectors to find cross product
    vec0[0] = v1[0] - v0[0];
    vec0[1] = v1[1] - v0[1];
    vec0[2] = v1[2] - v0[2];

    vec1[0] = v2[0] - v0[0];
    vec1[1] = v2[1] - v0[1];
    vec1[2] = v2[2] - v0[2];

    // Find cross product to get A, B, and C of plane equation
    plane[0] =   vec0[1] * vec1[2] - vec0[2] * vec1[1];
    plane[1] = -(vec0[0] * vec1[2] - vec0[2] * vec1[0]);
    plane[2] =   vec0[0] * vec1[1] - vec0[1] * vec1[0];

    plane[3] = -(plane[0] * v0[0] + plane[1] * v0[1] + plane[2] * v0[2]);
}

//-----------------------------------------------------------------------------
// Name: buildShadowMatrix()
// Desc: 
//-----------------------------------------------------------------------------
void buildShadowMatrix( float fMatrix[16], float fLightPos[4], float fPlane[4] )
{
    float dotp;

    // Calculate the dot-product between the plane and the light's position
    dotp = fPlane[0] * fLightPos[0] + 
           fPlane[1] * fLightPos[1] + 
           fPlane[1] * fLightPos[2] + 
           fPlane[3] * fLightPos[3];

    // First column
    fMatrix[0]  = dotp - fLightPos[0] * fPlane[0];
    fMatrix[4]  = 0.0f - fLightPos[0] * fPlane[1];
    fMatrix[8]  = 0.0f - fLightPos[0] * fPlane[2];
    fMatrix[12] = 0.0f - fLightPos[0] * fPlane[3];

    // Second column
    fMatrix[1]  = 0.0f - fLightPos[1] * fPlane[0];
    fMatrix[5]  = dotp - fLightPos[1] * fPlane[1];
    fMatrix[9]  = 0.0f - fLightPos[1] * fPlane[2];
    fMatrix[13] = 0.0f - fLightPos[1] * fPlane[3];

    // Third column
    fMatrix[2]  = 0.0f - fLightPos[2] * fPlane[0];
    fMatrix[6]  = 0.0f - fLightPos[2] * fPlane[1];
    fMatrix[10] = dotp - fLightPos[2] * fPlane[2];
    fMatrix[14] = 0.0f - fLightPos[2] * fPlane[3];

    // Fourth column
    fMatrix[3]  = 0.0f - fLightPos[3] * fPlane[0];
    fMatrix[7]  = 0.0f - fLightPos[3] * fPlane[1];
    fMatrix[11] = 0.0f - fLightPos[3] * fPlane[2];
    fMatrix[15] = dotp - fLightPos[3] * fPlane[3];
}

GLfloat* getShadowMatrix() {
    GLfloat shadowPlane[4];
    GLfloat v0[3], v1[3], v2[3];

    // To define a plane that matches the floor, we need to 3 vertices from it
    v0[0] = g_floorQuad[0].x;
    v0[1] = g_floorQuad[0].y;
    v0[2] = g_floorQuad[0].z;

    v1[0] = g_floorQuad[1].x;
    v1[1] = g_floorQuad[1].y;
    v1[2] = g_floorQuad[1].z;

    v2[0] = g_floorQuad[2].x;
    v2[1] = g_floorQuad[2].y;
    v2[2] = g_floorQuad[2].z;

    findPlane( shadowPlane, v0, v1, v2 );
    
    buildShadowMatrix( g_shadowMatrix, g_lightPosition, shadowPlane );
    return g_shadowMatrix;
}
