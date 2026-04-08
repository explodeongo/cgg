#include <GL/glut.h>
#include <iostream>
using namespace std;

float tx = 3.0, ty = 2.0, tz = 1.0;

void drawCube(float x, float y, float z) {

    // Front face
    glBegin(GL_LINE_LOOP);
        glVertex3f(-1+x, -1+y,  1+z);
        glVertex3f( 1+x, -1+y,  1+z);
        glVertex3f( 1+x,  1+y,  1+z);
        glVertex3f(-1+x,  1+y,  1+z);
    glEnd();

    // Back face
    glBegin(GL_LINE_LOOP);
        glVertex3f(-1+x, -1+y, -1+z);
        glVertex3f( 1+x, -1+y, -1+z);
        glVertex3f( 1+x,  1+y, -1+z);
        glVertex3f(-1+x,  1+y, -1+z);
    glEnd();

    // Connecting edges
    glBegin(GL_LINES);
        glVertex3f(-1+x, -1+y,  1+z); glVertex3f(-1+x, -1+y, -1+z);
        glVertex3f( 1+x, -1+y,  1+z); glVertex3f( 1+x, -1+y, -1+z);
        glVertex3f( 1+x,  1+y,  1+z); glVertex3f( 1+x,  1+y, -1+z);
        glVertex3f(-1+x,  1+y,  1+z); glVertex3f(-1+x,  1+y, -1+z);
    glEnd();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, 1.0, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Camera to see the cube from an angle
    gluLookAt(8, 8, 8,
              0, 0, 0,
              0, 1, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Original cube — white
    glColor3f(1.0, 1.0, 1.0);
    drawCube(0, 0, 0);

    // Translated cube — yellow
    glColor3f(1.0, 1.0, 0.0);
    drawCube(tx, ty, tz);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("3D Cube Translation");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}