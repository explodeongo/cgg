#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

float oldColor[3], fillColor[3] = {0,1,0};

void getPixel(int x,int y,float color[3]){
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,color);
}

void setPixel(int x,int y){
    glColor3f(0,1,0);
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
    glFlush();
}

int same(float a[3], float b[3]){
    return (a[0]==b[0] && a[1]==b[1] && a[2]==b[2]);
}

void flood(int x,int y){
    float curr[3];
    getPixel(x,y,curr);

    if(same(curr,oldColor)){
        setPixel(x,y);

        flood(x+1,y);
        flood(x-1,y);
        flood(x,y+1);
        flood(x,y-1);
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    // draw shape
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(200,200);
        glVertex2i(400,200);
        glVertex2i(400,400);
        glVertex2i(200,400);
    glEnd();

    // get initial color
    getPixel(300,300,oldColor);

    // fill
    flood(300,300);

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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutCreateWindow("Flood Fill");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}