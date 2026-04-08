#include<GL/glut.h>
#include<iostream>
#include<cmath>
using namespace std;

void init(){
    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,500.0,0.0,500.0);
}

void midpoint(int r, int xc, int yc){
    int p = 1 - r;
    int x = 0;
    int y = r;

    glBegin(GL_POINTS);

    while(x <= y){
        glVertex2i(xc+x, yc+y);
        glVertex2i(xc+x, yc-y);
        glVertex2i(xc-x, yc+y);
        glVertex2i(xc-x, yc-y);
        glVertex2i(xc+y, yc+x);
        glVertex2i(xc-y, yc+x);
        glVertex2i(xc+y, yc-x);
        glVertex2i(xc-y, yc-x);

        if(p < 0){
            p = p + 2*x + 3;
        }
        else{
            p = p + 2*(x - y) + 5;
            y--;
        }
        x++;
    }

    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glPointSize(3.0);

    midpoint(100, 250, 250);

    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("Midpoint Circle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}