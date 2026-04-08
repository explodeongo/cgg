#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <cmath>

int ww = 600, wh = 600;

float boundaryColor[3] = {1,0,0}; // red
float fillColor[3] = {0,1,0};     // green

// get pixel color
void getPixel(int x,int y,float color[3]){
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,color);
}

// set pixel
void setPixel(int x,int y){
    glColor3fv(fillColor);
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
    glFlush();
}

// compare colors (with tolerance)
int sameColor(float a[3], float b[3]){
    return (fabs(a[0]-b[0])<0.01 &&
            fabs(a[1]-b[1])<0.01 &&
            fabs(a[2]-b[2])<0.01);
}

// boundary fill (8-connected)
void boundaryFill(int x,int y){
    float current[3];
    getPixel(x,y,current);

    if(!sameColor(current,boundaryColor) &&
       !sameColor(current,fillColor)){

        setPixel(x,y);

        boundaryFill(x+1,y);
        boundaryFill(x-1,y);
        boundaryFill(x,y+1);
        boundaryFill(x,y-1);

        boundaryFill(x+1,y+1);
        boundaryFill(x-1,y-1);
        boundaryFill(x-1,y+1);
        boundaryFill(x+1,y-1);
    }
}

// draw polygon
void drawPolygon(){
    glColor3fv(boundaryColor);
    glBegin(GL_LINE_LOOP);
        glVertex2i(200,200);
        glVertex2i(400,200);
        glVertex2i(400,400);
        glVertex2i(200,400);
    glEnd();
}

// mouse click
void mouse(int button,int state,int x,int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        int yy = wh - y; // convert coordinate
        boundaryFill(x,yy);
    }
}

// display
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon();
    glFlush();
}

// init
void init(){
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,ww,0,wh);
}

// main
int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(ww,wh);
    glutCreateWindow("Boundary Fill");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
}