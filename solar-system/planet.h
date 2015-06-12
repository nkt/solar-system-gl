#include <stdlib.h>

#define RADIUS_RATIO 100
#define DISTANCE_RATIO 250000
#define CENTER_RADIUS_RATIO ((DISTANCE_RATIO / RADIUS_RATIO) * 1.5)

struct planet {
    int color;
    double x;
    double y;
    double z;
    double fi;
    double fi_step;
    double angle;
    double radius;
    double distance;
};

void init_planet(struct planet *item, int color, double radius, double distance, double fi_step) {
    item->color = color;
    item->radius = radius;
    item->fi_step = fi_step;
    item->x = item->y = item->z = item->fi = 0;
    item->angle = 0;
    item->distance = distance;
}


struct planet_system {
    struct planet center;
    struct planet *planets;
    int size;
};

void init_planet_system(struct planet_system *item, struct planet center) {
    center.radius /= CENTER_RADIUS_RATIO;
    item->center = center;
    item->size = 0;
    item->planets = NULL;
}

void add_planet(struct planet_system *item, struct planet new_planet) {
    item->size++;
    item->planets = (struct planet *) realloc(item->planets, sizeof(struct planet) * item->size);
    new_planet.radius /= RADIUS_RATIO;
    new_planet.distance /= DISTANCE_RATIO;
    item->planets[item->size - 1] = new_planet;
}

void calc_planet_system_state(struct planet_system *item) {
    item->center.angle += 0.5;
    for (int i = 0; i < item->size; i++) {
        item->planets[i].x = item->planets[i].distance * cos(item->planets[i].fi);
        item->planets[i].y = item->planets[i].distance * sin(item->planets[i].fi);
        item->planets[i].angle += 1.5;
        item->planets[i].fi += item->planets[i].fi_step;
    }
}