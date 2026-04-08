#include<GL/glut.h>
#include<iostream>
#include<cmath>
using namespace std;

float x1, y1, x2, y2;

void init(){
    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-250.0,250.0,-250.0,250.0);
}

void drawLine(float x1, float y1, float x2, float y2){
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    // Original line
    glColor3f(1.0,0.0,0.0);
    drawLine(x1,y1,x2,y2);

    // Rotation (30 degrees)
    float angle = 30 * 3.1415 / 180;

    float xr1 = x1*cos(angle) - y1*sin(angle);
    float yr1 = x1*sin(angle) + y1*cos(angle);

    float xr2 = x2*cos(angle) - y2*sin(angle);
    float yr2 = x2*sin(angle) + y2*cos(angle);

    glColor3f(0.0,1.0,0.0);
    drawLine(xr1,yr1,xr2,yr2);

    // Translation (3,2)
    float xt1 = xr1 + 3;
    float yt1 = yr1 + 2;

    float xt2 = xr2 + 3;
    float yt2 = yr2 + 2;

    glColor3f(0.0,0.0,1.0);
    drawLine(xt1,yt1,xt2,yt2);

    glFlush();
}

int main(int argc, char** argv){

    cout<<"Enter x1 y1 x2 y2: ";
    cin>>x1>>y1>>x2>>y2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("Transformation");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}