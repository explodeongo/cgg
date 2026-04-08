#include<GL/glut.h>
#include<iostream>
using namespace std;

float x1, y1, x2, y2;

void init(){
    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-250,250,-250,250);
}

void drawLine(float x1, float y1, float x2, float y2){
    glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    // ORIGINAL
    glColor3f(1.0,0.0,0.0);
    drawLine(x1,y1,x2,y2);

    // REFLECTION ABOUT X-AXIS
    glColor3f(0.0,1.0,0.0);
    drawLine(x1,-y1,x2,-y2);

    // REFLECTION ABOUT Y-AXIS
    glColor3f(0.0,0.0,1.0);
    drawLine(-x1,y1,-x2,y2);

    glFlush();
}

int main(int argc, char** argv){

    cout<<"Enter x1 y1 x2 y2: ";
    cin>>x1>>y1>>x2>>y2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("Reflection");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}