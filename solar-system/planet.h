struct planet {
    int color;
    double x;
    double y;
    double z;
    double fi;
    double fi_step;
    double angle;
    double radius;
};

void init_planet(struct planet *item, int color, double radius, double fi_step) {
    item->color = color;
    item->radius = radius;
    item->fi_step = fi_step;
    item->x = item->y = item->z = item->fi = 0;
    item->angle = 0;
}