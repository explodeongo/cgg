#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <iostream>
using namespace std;

int ww = 600, wh = 600;

float boundaryColor[3] = {1.0,0.0,0.0}; // red
float fillColor[3] = {0.0,1.0,0.0};     // green

void getPixel(int x, int y, float color[3]){
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,color);
}

void setPixel(int x, int y){
    glColor3fv(fillColor);
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
    glFlush();
}

int sameColor(float a[3], float b[3]){
    return (a[0]==b[0] && a[1]==b[1] && a[2]==b[2]);
}

void boundaryFill(int x, int y){
    float current[3];
    getPixel(x,y,current);

    if(!sameColor(current,boundaryColor) && !sameColor(current,fillColor)){
        setPixel(x,y);

        boundaryFill(x+1,y);
        boundaryFill(x-1,y);
        boundaryFill(x,y+1);
        boundaryFill(x,y-1);
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    // draw boundary
    glColor3fv(boundaryColor);
    glBegin(GL_LINE_LOOP);
        glVertex2i(200,200);
        glVertex2i(400,200);
        glVertex2i(400,400);
        glVertex2i(200,400);
    glEnd();

    // fill
    boundaryFill(300,300);

    glFlush();
}

void init(){
    glClearColor(0,0,0,1);
  
    glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0,600,0,600);
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitWindowSize(600,600);
    glutCreateWindow("Boundary Fill");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}