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

/* -------- DDA with Line Style --------
   style = 1 → Dotted line
   style = 2 → Dash-dot line
--------------------------------------*/
void ddaStyledLine(int x1, int y1, int x2, int y2, int style)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps;
    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1;
    float y = y1;

    int patternCount = 0;

    for (int i = 0; i <= steps; i++)
    {
        int xi = round(x);
        int yi = round(y);

        if (style == 1)
        {
            // DOTTED: draw every alternate pixel
            if (i % 2 == 0)
                drawPixel(xi, yi);
        }
        else if (style == 2)
        {
            // DASH-DOT: 3 draw, 1 skip, 1 draw, 1 skip
            if (patternCount < 3)            // dash
                drawPixel(xi, yi);
            else if (patternCount == 4)      // dot
                drawPixel(xi, yi);

            patternCount = (patternCount + 1) % 6;
        }

        x += xInc;
        y += yInc;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    // (a) Dotted line
    ddaStyledLine(50, 350, 450, 350, 1);

    // (b) Dash-dot line
    ddaStyledLine(50, 250, 450, 250, 2);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Dotted and Dash-Dot Line Drawing");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

