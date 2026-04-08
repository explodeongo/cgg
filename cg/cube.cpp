#include <GL/glut.h>
#include <iostream>
using namespace std;

// Translation values
float tx = 2.0, ty = 1.5, tz = -1.0;

// ─── Draw a Cube using GL_LINE_LOOP ─────────────
void drawCube() {

    // Front face
    glBegin(GL_LINE_LOOP);
        glVertex3f(-1, -1,  1);
        glVertex3f( 1, -1,  1);
        glVertex3f( 1,  1,  1);
        glVertex3f(-1,  1,  1);
    glEnd();

    // Back face
    glBegin(GL_LINE_LOOP);
        glVertex3f(-1, -1, -1);
        glVertex3f( 1, -1, -1);
        glVertex3f( 1,  1, -1);
        glVertex3f(-1,  1, -1);
    glEnd();

    // Connecting edges
    glBegin(GL_LINES);
        glVertex3f(-1, -1,  1); glVertex3f(-1, -1, -1);
        glVertex3f( 1, -1,  1); glVertex3f( 1, -1, -1);
        glVertex3f( 1,  1,  1); glVertex3f( 1,  1, -1);
        glVertex3f(-1,  1,  1); glVertex3f(-1,  1, -1);
    glEnd();
}

// ─── Display ─────────────────────────────────────
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ── Original Cube (White) ──
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);
    drawCube();

    // ── Translated Cube (Yellow) ──
    glLoadIdentity();
    glTranslatef(tx, ty, tz);   // Apply translation
    glColor3f(1.0, 1.0, 0.0);
    drawCube();

    glFlush();
}

// ─── Init ─────────────────────────────────────────
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Perspective: FOV=45, aspect=1, near=1, far=20
    gluPerspective(45.0, 1.0, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Camera: eye at (5,5,10), looking at origin
    gluLookAt(5, 5, 10,
              0, 0,  0,
              0, 1,  0);
}

// ─── Main ─────────────────────────────────────────
int main(int argc, char** argv) {
    cout << "Original Cube  : (0, 0, 0)" << endl;
    cout << "Translation    : tx=" << tx << " ty=" << ty << " tz=" << tz << endl;
    cout << "Translated to  : (" << tx << ", " << ty << ", " << tz << ")" << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("3D Translation of a Cube");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}