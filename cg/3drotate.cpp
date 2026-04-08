#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

#define PI 3.14159

float angle;
// rotation axis: x-axis=1, y-axis=2, z-axis=3
int axis;

// ─── Rotate point around chosen axis ─────────────
void rotate(float x, float y, float z,
            float &rx, float &ry, float &rz) {
    float a = angle * PI / 180;

    if(axis == 1) {       // X axis
        rx = x;
        ry = y*cos(a) - z*sin(a);
        rz = y*sin(a) + z*cos(a);
    }
    else if(axis == 2) {  // Y axis
        rx = x*cos(a) + z*sin(a);
        ry = y;
        rz = -x*sin(a) + z*cos(a);
    }
    else {                // Z axis
        rx = x*cos(a) - y*sin(a);
        ry = x*sin(a) + y*cos(a);
        rz = z;
    }
}

// ─── Draw cube with offset ────────────────────────
void drawCube(float x, float y, float z) {
    glBegin(GL_LINE_LOOP);
        glVertex3f(-1+x, -1+y,  1+z);
        glVertex3f( 1+x, -1+y,  1+z);
        glVertex3f( 1+x,  1+y,  1+z);
        glVertex3f(-1+x,  1+y,  1+z);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(-1+x, -1+y, -1+z);
        glVertex3f( 1+x, -1+y, -1+z);
        glVertex3f( 1+x,  1+y, -1+z);
        glVertex3f(-1+x,  1+y, -1+z);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(-1+x, -1+y,  1+z); glVertex3f(-1+x, -1+y, -1+z);
        glVertex3f( 1+x, -1+y,  1+z); glVertex3f( 1+x, -1+y, -1+z);
        glVertex3f( 1+x,  1+y,  1+z); glVertex3f( 1+x,  1+y, -1+z);
        glVertex3f(-1+x,  1+y,  1+z); glVertex3f(-1+x,  1+y, -1+z);
    glEnd();
}

// ─── Draw cube from 8 rotated points ─────────────
void drawRotatedCube() {
    // 8 original vertices of cube
    float pts[8][3] = {
        {-1,-1, 1}, { 1,-1, 1}, { 1, 1, 1}, {-1, 1, 1},  // front
        {-1,-1,-1}, { 1,-1,-1}, { 1, 1,-1}, {-1, 1,-1}   // back
    };

    // rotate all 8 points
    float r[8][3];
    for(int i = 0; i < 8; i++)
        rotate(pts[i][0], pts[i][1], pts[i][2],
               r[i][0],   r[i][1],   r[i][2]);

    // front face
    glBegin(GL_LINE_LOOP);
        glVertex3f(r[0][0], r[0][1], r[0][2]);
        glVertex3f(r[1][0], r[1][1], r[1][2]);
        glVertex3f(r[2][0], r[2][1], r[2][2]);
        glVertex3f(r[3][0], r[3][1], r[3][2]);
    glEnd();

    // back face
    glBegin(GL_LINE_LOOP);
        glVertex3f(r[4][0], r[4][1], r[4][2]);
        glVertex3f(r[5][0], r[5][1], r[5][2]);
        glVertex3f(r[6][0], r[6][1], r[6][2]);
        glVertex3f(r[7][0], r[7][1], r[7][2]);
    glEnd();

    // connecting edges
    glBegin(GL_LINES);
        glVertex3f(r[0][0],r[0][1],r[0][2]); glVertex3f(r[4][0],r[4][1],r[4][2]);
        glVertex3f(r[1][0],r[1][1],r[1][2]); glVertex3f(r[5][0],r[5][1],r[5][2]);
        glVertex3f(r[2][0],r[2][1],r[2][2]); glVertex3f(r[6][0],r[6][1],r[6][2]);
        glVertex3f(r[3][0],r[3][1],r[3][2]); glVertex3f(r[7][0],r[7][1],r[7][2]);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // original cube — white
    glColor3f(1, 1, 1);
    drawCube(0, 0, 0);

    // rotated cube — yellow
    glColor3f(1, 1, 0);
    drawRotatedCube();

    glFlush();
}

void init() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 8, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char** argv) {
    cout << "Enter angle: ";
    cin >> angle;
    cout << "Enter axis (1=X, 2=Y, 3=Z): ";
    cin >> axis;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("3D Cube Rotation");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}