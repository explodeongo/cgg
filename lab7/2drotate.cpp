#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

#define PI 3.14159

float x1, y1, x2, y2, x3, y3;
float angle, px, py;  // px, py = fixed point

// rotate point about fixed point (px, py)
void rotate(float x, float y, float &xr, float &yr) {
    float a = angle * PI / 180;

    // step 1 - shift to origin
    x = x - px;
    y = y - py;

    // step 2 - rotate
    xr = x*cos(a) - y*sin(a);
    yr = x*sin(a) + y*cos(a);

    // step 3 - shift back
    xr = xr + px;
    yr = yr + py;
}

void draw(float a1, float b1, float a2, float b2, float a3, float b3) {
    glBegin(GL_LINE_LOOP);
        glVertex2f(a1, b1);
        glVertex2f(a2, b2);
        glVertex2f(a3, b3);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 1, 1);
    draw(x1, y1, x2, y2, x3, y3);

    float rx1, ry1, rx2, ry2, rx3, ry3;
    rotate(x1, y1, rx1, ry1);
    rotate(x2, y2, rx2, ry2);
    rotate(x3, y3, rx3, ry3);

    glColor3f(1, 1, 0);
    draw(rx1, ry1, rx2, ry2, rx3, ry3);

    glFlush();
}

void init() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50, 50, -50, 50);
}

int main(int argc, char** argv) {
    cout << "Enter triangle: ";
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    cout << "Enter angle: ";
    cin >> angle;
    cout << "Enter fixed point: ";
    cin >> px >> py;   // for origin just enter 0 0

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Rotation");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}