#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

#define PI 3.14159

float angle;
int axis;

void rotate(float x,float y,float z,float &xr,float &yr,float &zr){
    float a = angle * PI / 180;

    if(axis == 1){
        xr = x;
        yr = y*cos(a) - z*sin(a);
        zr = y*sin(a) + z*cos(a);
    }
    else if(axis == 2){
        xr = x*cos(a) + z*sin(a);
        yr = y;
        zr = -x*sin(a) + z*cos(a);
    }
    else{
        xr = x*cos(a) - y*sin(a);
        yr = x*sin(a) + y*cos(a);
        zr = z;
    }
}

void drawCube(float p[8][3]){
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<4;i++) glVertex3f(p[i][0],p[i][1],p[i][2]);
    glEnd();

    glBegin(GL_LINE_LOOP);
        for(int i=4;i<8;i++) glVertex3f(p[i][0],p[i][1],p[i][2]);
    glEnd();

    glBegin(GL_LINES);
        for(int i=0;i<4;i++){
            glVertex3f(p[i][0],p[i][1],p[i][2]);
            glVertex3f(p[i+4][0],p[i+4][1],p[i+4][2]);
        }
    glEnd();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(5,5,8, 0,0,0, 0,1,0);

    float pts[8][3] = {
        {-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1},
        {-1,-1,-1},{1,-1,-1},{1,1,-1},{-1,1,-1}
    };

    glColor3f(1,1,1);
    drawCube(pts);

    float r[8][3];
    for(int i=0;i<8;i++){
        rotate(pts[i][0],pts[i][1],pts[i][2],
               r[i][0],r[i][1],r[i][2]);
    }

    glColor3f(1,1,0);
    drawCube(r);

    glFlush();
}

void init(){
    glClearColor(0,0,0,1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,1,1,50);
}

int main(int argc,char** argv){
    cout<<"Enter angle: ";
    cin>>angle;
    cout<<"Axis (1=X 2=Y 3=Z): ";
    cin>>axis;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // ❌ no depth
    glutInitWindowSize(500,500);
    glutCreateWindow("3D Rotation");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}