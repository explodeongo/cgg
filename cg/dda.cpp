#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}

void ddaLine(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps;

    if (abs(dx) > abs(dy))
    {
      steps = abs(dx);
    }
    else
    {
      steps = abs(dy);
    }

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1;
    float y = y1;

    cout << "DDA Line Pixels:\n";
    cout << "-----------------\n";

    for (int i = 0; i <= steps; i++)
    {
        int xi = round(x);
        int yi = round(y);

        drawPixel(xi, yi);

        x += xInc;
        y += yInc;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

   ddaLine(100, 100, 400, 300);   // positive slope
    ddaLine(100, 300, 400, 100); // negative slope
   ddaLine(250, 50, 250, 450);  // vertical
    ddaLine(50, 250, 450, 250);  // horizontal
   ddaLine(200, 100, 260, 400); // steep slope

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA Line Drawing Algorithm");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

