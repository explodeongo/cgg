#include<GL/glut.h>
#include<iostream>
#include<cmath>
using namespace std;

float rx, ry, xc, yc;

void init(){
    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,1000.0,0.0,1000.0);
}

void ellipse(){
    float x = 0;
    float y = ry;

    float p1 = ry*ry - rx*rx*ry + 0.25*rx*rx;

    glBegin(GL_POINTS);

    // Region 1
    while(2*ry*ry*x <= 2*rx*rx*y){
        glVertex2i(xc+x, yc+y);
        glVertex2i(xc+x, yc-y);
        glVertex2i(xc-x, yc+y);
        glVertex2i(xc-x, yc-y);

        if(p1 < 0){
            x++;
            p1 += 2*ry*ry*x + ry*ry;
        }
        else{
            x++;
            y--;
            p1 += 2*ry*ry*x - 2*rx*rx*y + ry*ry;
        }
    }

    // Region 2
    float p2 = ry*ry*(x+0.5)*(x+0.5) + rx*rx*(y-1)*(y-1) - rx*rx*ry*ry;

    while(y >= 0){
        glVertex2i(xc+x, yc+y);
        glVertex2i(xc+x, yc-y);
        glVertex2i(xc-x, yc+y);
        glVertex2i(xc-x, yc-y);

        if(p2 > 0){
            y--;
            p2 -= 2*rx*rx*y + rx*rx;
        }
        else{
            x++;
            y--;
            p2 += 2*ry*ry*x - 2*rx*rx*y + rx*rx;
        }
    }

    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,0.0);
    glPointSize(2.0);

    ellipse();

    glFlush();
}

int main(int argc, char** argv){
    cout<<"Enter rx and ry: ";
    cin>>rx>>ry;
    cout<<"Enter center (xc yc): ";
    cin>>xc>>yc;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("Midpoint Ellipse");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}