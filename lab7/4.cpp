#include<GL/glut.h>

void init(){
    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-20,20,-20,20);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    // RECTANGLE (blue)
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0,0);
        glVertex2f(6,0);
        glVertex2f(6,4);
        glVertex2f(0,4);
    glEnd();

    // TRIANGLE (original - red)
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0,0);
        glVertex2f(2,0);
        glVertex2f(1,2);
    glEnd();

    // TRANSLATED TRIANGLE (top middle of rectangle - green)
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(2,4);   // (0+2, 0+4)
        glVertex2f(4,4);   // (2+2, 0+4)
        glVertex2f(3,6);   // (1+2, 2+4)
    glEnd();

    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("Translation");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}