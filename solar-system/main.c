#include <stdlib.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif
#include "planet.h"

#define HEX_RED(c) ((c >> 16) & 0xFF) / 255.0
#define HEX_GREEN(c) ((c >> 8) & 0xFF) / 255.0
#define HEX_BLUE(c) ((c) & 0xFF) / 255.0
#define HEX(c) HEX_RED(c), HEX_GREEN(c), HEX_BLUE(c)

#define TIMER_DELAY 1

void timer(int);
void display();
void reshape(int, int);

struct planet_system ps;

int main(int argc, char **argv) {
    struct planet sun, mercury, venus, earth, moon, mars;
    init_planet(&sun, 0xfc9a24, 695800, 0, 0, NULL);
    init_planet(&mercury, 0x99989D, 2440, 57910000, 0.01, NULL);
    init_planet(&venus, 0x6894D2, 6052, 108200000, 0.002, NULL);
    init_planet(&moon, 0xffffff, 1737.10, 384400, 0.0035 * 12, NULL);
    init_planet(&earth, 0x005db3, 6371, 149600000, 0.0035, &moon);
    init_planet(&mars, 0xD0331A, 3390, 227900000, 0.0015, NULL);
    
    init_planet_system(&ps, sun);
    add_planet(&ps, mercury);
    add_planet(&ps, venus);
    add_planet(&ps, earth);
    add_planet(&ps, mars);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Solar System");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    
    glutTimerFunc(TIMER_DELAY, timer, 0);
    glutMainLoop();
}


void timer(int a) {
    calc_planet_system_state(&ps);

    glutPostRedisplay();
    glutTimerFunc(TIMER_DELAY, timer, 0);
}

void display_planet(struct planet p) {
    glColor3f(HEX(p.color));
    glPushMatrix();
    glTranslatef(p.x, p.y, p.z);
    glRotatef(p.angle, 15, 25, 1);
    int lines = p.radius / 2.5;
    glutWireSphere(p.radius, lines, lines);
    glPopMatrix();
    
    if (p.satellite) {
        display_planet(*p.satellite);
    }
}

void display() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    display_planet(ps.center);
    
    for (int i = 0; i < ps.size; i++) {
        display_planet(ps.planets[i]);
    }
    
    glutSwapBuffers();
}


void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width, width, -height, height, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}