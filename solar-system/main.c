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
#define BASE_RADIUS 170
#define PLANET_COUNT 5

void timer(int);
void display();
void reshape(int, int);

struct planet sun, mercury, venus, earth, mars;
struct planet *planets;

int main(int argc, char **argv) {
    init_planet(&sun, 0xfc9a24, 100, 0);
    init_planet(&mercury, 0x99989D, 24.39, 0.01);
    init_planet(&venus, 0x6894D2, 60.51, 0.002);
    init_planet(&earth, 0x005db3, 63.71, 0.0035);
    init_planet(&mars, 0xD0331A, 33.89, 0.0015);
    
    planets = (struct planet*) malloc(sizeof(struct planet) * PLANET_COUNT);
    planets[0] = mercury;
    planets[1] = venus;
    planets[2] = earth;
    planets[3] = mars;

    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    
    glutInitWindowSize(800, 600);
    glutCreateWindow("Solar System");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    
    glutTimerFunc(TIMER_DELAY, timer, 0);
    glutMainLoop();
}


void timer(int a) {
    int radius = 0;
    sun.angle += 0.5;
    for (int i = 0; i < PLANET_COUNT; i++, radius += 100) {
        planets[i].x = (BASE_RADIUS + radius) * cos(planets[i].fi);
        planets[i].y = (BASE_RADIUS + radius) * sin(planets[i].fi);
        planets[i].angle += 1.5;
        planets[i].fi += planets[i].fi_step;
    }
    
    glutPostRedisplay();
    glutTimerFunc(TIMER_DELAY, timer, 0);
}

void display_planet(struct planet p) {
    glColor3f(HEX(p.color));
    glPushMatrix();
    glTranslatef(p.x, p.y, p.z);
    glRotatef(p.angle, 15, 25, 1);
    glutWireSphere(p.radius / 1.5, 15, 15);
    glPopMatrix();
}

void display() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    display_planet(sun);
    
    for (int i = 0; i < PLANET_COUNT; i++) {
        display_planet(planets[i]);
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