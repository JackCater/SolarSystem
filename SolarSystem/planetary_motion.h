#ifndef PLANETARY_MOTION_H
#define PLANETARY_MOTION_H

#include "universe.h"
#include "output.h"

std::ofstream file;

inline data RHS(body& earth, body& sun, double x, double y, double vx, double vy); // function definition
inline bool fn_explicit_euler(body& earth, body& sun, data_collection& collection); // function definition
inline bool fn_explicit_euler_full(body& earth, body& sun, data_collection& collection, char* file_name); // function definition
inline bool fn_runge_kutta4_full(body& earth, body& sun, data_collection& collection, char* file_name); // function definition

inline double dx(double x, double y, double vx, double vy) { return vx; }
inline double dy(double x, double y, double vx, double vy) { return vy; }
inline double du(double x, double y, double vx, double vy) { return -(constant * x) / pow(sqrt((x * x) + (y * y)),3); }
inline double dv(double x, double y, double vx, double vy) { return -(constant * y) / pow(sqrt((x * x) + (y * y)),3); }


/*
inline data RHS(body& earth, body& sun, double x, double y, double vx, double vy) {
    double r;
}*/

inline bool fn_explicit_euler(body& earth, body& sun, data_collection& c) {
    data d = force::calculate_force(earth, sun);

    earth.x(earth.x() + d.dx * c.dt());
    earth.y(earth.y() + d.dy * c.dt());
    earth.vx(earth.vx() + d.dvx * c.dt());
    earth.vy(earth.vy() + d.dvy * c.dt());
    c.time(c.time() + c.dt());

    return true;
}

inline bool fn_explicit_euler_full(body& earth, body& sun, data_collection& c, char* file_name) {
    file.open(file_name);

    while (c.time() <= c.final_time()) {
        data d = force::calculate_force(earth, sun);

        earth.x(earth.x() + d.dx * c.dt());
        earth.y(earth.y() + d.dy * c.dt());
        earth.vx(earth.vx() + d.dvx * c.dt());
        earth.vy(earth.vy() + d.dvy * c.dt());
        c.time(c.time() + c.dt());
        output(c.time(), earth, d.E, file);   // write to file 
    }
    file.close();
    return true;
}

inline bool fn_runge_kutta4_full(body& earth, body& sun, data_collection& c, char* file_name) {
    file.open(file_name);
    while (c.time() <= c.final_time()) {
        double k_x1 = c.dt() * dx(earth.x(), earth.y(), earth.vx(), earth.vy());
        double k_y1 = c.dt() * dy(earth.x(), earth.y(), earth.vx(), earth.vy());
        double k_vx1 = c.dt() * du(earth.x(), earth.y(), earth.vx(), earth.vy());
        double k_vy1 = c.dt() * dv(earth.x(), earth.y(), earth.vx(), earth.vy());
        
        double k_x2 = c.dt() * dx(earth.x() + k_x1 * 0.5, earth.y() + k_y1 * 0.5, earth.vx() + k_vx1 * 0.5, earth.vy() + k_vy1 * 0.5);
        double k_y2 = c.dt() * dy(earth.x() + k_x1 * 0.5, earth.y() + k_y1 * 0.5, earth.vx() + k_vx1 * 0.5, earth.vy() + k_vy1 * 0.5);
        double k_vx2 = c.dt() * du(earth.x() + k_x1 * 0.5, earth.y() + k_y1 * 0.5, earth.vx() + k_vx1 * 0.5, earth.vy() + k_vy1 * 0.5);
        double k_vy2 = c.dt() * dv(earth.x() + k_x1 * 0.5, earth.y() + k_y1 * 0.5, earth.vx() + k_vx1 * 0.5, earth.vy() + k_vy1 * 0.5);
        
        double k_x3 = c.dt() * dx(earth.x() + k_x2 * 0.5, earth.y() + k_y2 * 0.5, earth.vx() + k_vx2 * 0.5, earth.vy() + k_vy2 * 0.5);
        double k_y3 = c.dt() * dy(earth.x() + k_x2 * 0.5, earth.y() + k_y2 * 0.5, earth.vx() + k_vx2 * 0.5, earth.vy() + k_vy2 * 0.5);
        double k_vx3 = c.dt() * du(earth.x() + k_x2 * 0.5, earth.y() + k_y2 * 0.5, earth.vx() + k_vx2 * 0.5, earth.vy() + k_vy2 * 0.5);
        double k_vy3 = c.dt() * dv(earth.x() + k_x2 * 0.5, earth.y() + k_y2 * 0.5, earth.vx() + k_vx2 * 0.5, earth.vy() + k_vy2 * 0.5);
        
        double k_x4 = c.dt() * dx(earth.x() + k_x3, earth.y() + k_y3, earth.vx() + k_vx3, earth.vy() + k_vy3);
        double k_y4 = c.dt() * dy(earth.x() + k_x3, earth.y() + k_y3, earth.vx() + k_vx3, earth.vy() + k_vy3);
        double k_vx4 = c.dt() * du(earth.x() + k_x3, earth.y() + k_y3, earth.vx() + k_vx3, earth.vy() + k_vy3);
        double k_vy4 = c.dt() * dv(earth.x() + k_x3, earth.y() + k_y3, earth.vx() + k_vx3, earth.vy() + k_vy3);

        earth.x(earth.x() + k_x1 / 6.0 + k_x2 / 3.0 + k_x2 / 3.0 + k_x4 / 6.0);
        earth.y(earth.y() + k_y1 / 6.0 + k_y2 / 3.0 + k_y2 / 3.0 + k_y4 / 6.0);
        earth.vx(earth.vx() + k_vx1 / 6.0 + k_vx2 / 3.0 + k_vx2 / 3.0 + k_vx4 / 6.0);
        earth.vy(earth.vy() + k_vy1 / 6.0 + k_vy2 / 3.0 + k_vy2 / 3.0 + k_vy4 / 6.0);

        double e = 0.5 * (earth.vx() * earth.vx() + earth.vy() * earth.vy()) - constant / (sqrt(earth.x() * earth.x() + earth.y() * earth.y()));

        c.time(c.time() + c.dt());
        output(c.time(), earth, e, file);   // write to file 

    }
    file.close();
    return true;
}

#endif
