#include <GL/glut.h>
#include <cmath>

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
        steps = abs(dx);
    else
        steps = abs(dy);

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++)
    {
        drawPixel(round(x), round(y));
        x += xInc;
        y += yInc;
    }
}

void drawHELLO()
{
    int yTop = 300;
    int yBottom = 200;
    int midY = 250;

    // H
    ddaLine(50, yBottom, 50, yTop);
    ddaLine(80, yBottom, 80, yTop);
    ddaLine(50, midY, 80, midY);

    // E
    ddaLine(110, yBottom, 110, yTop);
    ddaLine(110, yTop, 150, yTop);
    ddaLine(110, midY, 140, midY);
    ddaLine(110, yBottom, 150, yBottom);

    // L
    ddaLine(180, yBottom, 180, yTop);
    ddaLine(180, yBottom, 220, yBottom);

    // L
    ddaLine(250, yBottom, 250, yTop);
    ddaLine(250, yBottom, 290, yBottom);

    // O
    ddaLine(320, yBottom, 320, yTop);
    ddaLine(360, yBottom, 360, yTop);
    ddaLine(320, yTop, 360, yTop);
    ddaLine(320, yBottom, 360, yBottom);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    drawHELLO();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("HELLO using DDA Line Drawing Algorithm");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

