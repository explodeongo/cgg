#include <GL/glut.h>
#include <iostream>
using namespace std;

// ─── Region Codes ───────────────────────────────
#define INSIDE  0  // 0000
#define LEFT    1  // 0001
#define RIGHT   2  // 0010
#define BOTTOM  4  // 0100
#define TOP     8  // 1000

// ─── Clipping Window ────────────────────────────
float xmin = 100, xmax = 400;
float ymin = 100, ymax = 400;

// ─── Step 1: Assign Region Code to a Point ──────
int regionCode(float x, float y) {
    int code = INSIDE;

    if (x < xmin) code |= LEFT;
    else if (x > xmax) code |= RIGHT;

    if (y < ymin) code |= BOTTOM;
    else if (y > ymax) code |= TOP;

    return code;
}

// ─── Step 2: Cohen-Sutherland Clip & Draw ───────
void cohenSutherland(float x1, float y1, float x2, float y2) {

    int c1 = regionCode(x1, y1);
    int c2 = regionCode(x2, y2);

    while (true) {

        // Case 1: Both inside → accept
        if (!(c1 | c2)) {
            glColor3f(0, 1, 0);  // green = clipped line
            glBegin(GL_LINES);
                glVertex2f(x1, y1);
                glVertex2f(x2, y2);
            glEnd();
            return;
        }

        // Case 2: Both in same outside region → reject
        if (c1 & c2) return;

        // Case 3: Partially inside → clip
        float x, y;

        // Pick the outside point
        int outside = (c1 != 0) ? c1 : c2;

        // Find intersection with boundary
        if (outside & TOP) {
            x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
            y = ymax;
        }
        else if (outside & BOTTOM) {
            x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
            y = ymin;
        }
        else if (outside & RIGHT) {
            y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
            x = xmax;
        }
        else { // LEFT
            y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
            x = xmin;
        }

        // Replace outside point with intersection
        if (outside == c1) {
            x1 = x; y1 = y;
            c1 = regionCode(x1, y1);
        } else {
            x2 = x; y2 = y;
            c2 = regionCode(x2, y2);
        }
    }
}

// ─── Display ────────────────────────────────────
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping window
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin, ymin);
        glVertex2f(xmax, ymin);
        glVertex2f(xmax, ymax);
        glVertex2f(xmin, ymax);
    glEnd();

    // Draw original lines in red
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
        glVertex2f(50,  50);  glVertex2f(470, 300); // partially inside
        glVertex2f(50, 450);  glVertex2f(470, 450); // completely outside
        glVertex2f(150, 150); glVertex2f(350, 350); // completely inside
    glEnd();

    // Draw clipped lines in green
    cohenSutherland(50,  50,  470, 300); // partial → clipped
    cohenSutherland(50,  450, 470, 450); // outside → rejected
    cohenSutherland(150, 150, 350, 350); // inside  → accepted as-is

    glFlush();
}

// ─── Init ────────────────────────────────────────
void init() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

// ─── Main ────────────────────────────────────────
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cohen-Sutherland Line Clipping");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}