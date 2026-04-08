#include <GL/glut.h>
#include <iostream>
using namespace std;

float tx = 3.0, ty = 2.0, tz = 1.0;

// Cuboid: x→-2to+2, y→-1to+1, z→-1to+1
void drawCuboid(float x, float y, float z) {

    // Front face
    glBegin(GL_LINE_LOOP);
        glVertex3f(-2+x, -1+y,  1+z);
        glVertex3f( 2+x, -1+y,  1+z);
        glVertex3f( 2+x,  1+y,  1+z);
        glVertex3f(-2+x,  1+y,  1+z);
    glEnd();

    // Back face
    glBegin(GL_LINE_LOOP);
        glVertex3f(-2+x, -1+y, -1+z);
        glVertex3f( 2+x, -1+y, -1+z);
        glVertex3f( 2+x,  1+y, -1+z);
        glVertex3f(-2+x,  1+y, -1+z);
    glEnd();

    // Connecting edges
    glBegin(GL_LINES);
        glVertex3f(-2+x, -1+y,  1+z); glVertex3f(-2+x, -1+y, -1+z);
        glVertex3f( 2+x, -1+y,  1+z); glVertex3f( 2+x, -1+y, -1+z);
        glVertex3f( 2+x,  1+y,  1+z); glVertex3f( 2+x,  1+y, -1+z);
        glVertex3f(-2+x,  1+y,  1+z); glVertex3f(-2+x,  1+y, -1+z);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Original — white
    glColor3f(1, 1, 1);
    drawCuboid(0, 0, 0);

    // Translated — yellow
    glColor3f(1, 1, 0);
    drawCuboid(tx, ty, tz);

    glFlush();
}

void init() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(8, 6, 12, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("3D Cuboid Translation");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}