#ifndef FORCE_H
#define FORCE_H

#include "body.h"

const double constant = (grav_constant * solar_mass * orbital_period * orbital_period) / (aphelion_distance * aphelion_distance * aphelion_distance); // GMT^2/R^3 used with equations of motion

struct data {
    double dx;
    double dy;
    double dvx;
    double dvy;
    double E;
};

class force {
public:
    static data calculate_force(body& b1, body& b2) {
        double r = distance(b1.pos(), b1.pos());
        data d{
            d.dx = b1.vx(),
            d.dy = b1.vy(),
            d.dvx = -(constant * b1.x()) / (r * r * r),
            d.dvy = -(constant * b1.y()) / (r * r * r),
            d.E = 0.5 * (b1.vx() * b1.vx() + b1.vy() * b1.vy()) - (constant / r) };
        return d;
    }
};

#endif