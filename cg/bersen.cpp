#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <algorithm>

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

void bresenhamLine(int x1, int y1, int x2, int y2)
{
    cout << "Bresenham Line Pixels:\n";
    cout << "----------------------\n";

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    bool isSteep = false;

    if (dy > dx)
    {
        isSteep = true;
        swap(dx, dy);
    }

    int p = 2 * dy - dx;

    int x = x1;
    int y = y1;

    for (int i = 0; i <= dx; i++)
    {
        if (isSteep)
        {
            cout << "(" << y << ", " << x << ")\n";
            drawPixel(y, x);
        }
        else
        {
            cout << "(" << x << ", " << y << ")\n";
            drawPixel(x, y);
        }

        x += sx;

        if (p >= 0)
        {
            y += sy;
            p += 2 * (dy - dx);
        }
        else
        {
            p += 2 * dy;
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
  

    bresenhamLine(100, 100, 400, 300);   // positive slope
    bresenhamLine(100, 300, 400, 100); // negative slope
    bresenhamLine(250, 50, 250, 450);  // vertical
    bresenhamLine(50, 250, 450, 250);  // horizontal
    bresenhamLine(200, 100, 260, 400); // steep slope

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresenham Line Drawing Algorithm");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

