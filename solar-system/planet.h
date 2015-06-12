#include <stdlib.h>

#define RADIUS_RATIO 100
#define DISTANCE_RATIO 250000
#define CENTER_RADIUS_RATIO ((DISTANCE_RATIO / RADIUS_RATIO) * 1.5)
#define SATELLITE_DISTANCE_RATIO (DISTANCE_RATIO / 80)
#define SATELLITE_RADIUS_RATIO (RADIUS_RATIO / 1.2)

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
    struct planet *satellite;
};

void init_planet(
                 struct planet *item,
                 int color,
                 double radius,
                 double distance,
                 double fi_step,
                 struct planet *satellite
) {
    item->color = color;
    item->radius = radius;
    item->distance = distance;
    item->fi_step = fi_step;
    if (satellite) {
        satellite->radius /= SATELLITE_RADIUS_RATIO;
        satellite->distance /= SATELLITE_DISTANCE_RATIO;
    }
    item->satellite = satellite;
    item->x = 0;
    item->y = 0;
    item->z = 1;
    item->fi = 0;
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
        struct planet *curr = &item->planets[i];
        curr->x = curr->distance * cos(curr->fi);
        curr->y = curr->distance * sin(curr->fi);
        curr->angle += 1.5;
        curr->fi += curr->fi_step;
        if (curr->satellite) {
            curr->satellite->x = curr->x + curr->satellite->distance * cos(curr->satellite->fi);
            curr->satellite->y = curr->y + curr->satellite->distance * sin(curr->satellite->fi);
            curr->satellite->fi += curr->satellite->fi_step;
        }
    }
}