// File containing useful constants and functions
#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <limits>
#include <memory>

#include "vec3.h"

// Utility Functions
inline double degrees_to_radians(double degrees) { return degrees * 3.1415926535897932385 / 180.0; } // Converts degree to radians
inline double radians_to_degrees(double radians) { return radians * 180.0 / 3.1415926535897932385; } // Converts radians to degrees
inline double d_au_to_meters(double au_dist) { return au_dist * 1.49598e+11; } // Convert AU to meters
inline double v_au_to_meters(double au_speed) { return au_speed * 1731460; } // Convert AU/day to m/s
inline double d_meters_to_au(double meters) { return meters * 6.6845871226706E-12; } // convert meters to AU
inline double v_meters_to_au(double ms) { return ms * 5.77548e-7; } // Convert m/s to AU/day
inline point3 vec_d_au_to_meters(double x_au, double y_au, double z_au) { return point3(x_au * 1.496E+11, y_au * 1.496E+11, z_au * 1.496E+11); } // Convert AU to meters
inline vel3 vec_v_au_to_meters(double x_au, double y_au, double z_au) { return vel3(x_au * 1.731E+6, y_au * 1.731E+6, z_au * 1.731E+6); } // Convert AU/day to m/s
// inline double sphere_volume(body b) { return (4.0 / 3.0) * pi * b.radius * b.radius * b.radius; } // Calculates a spheres volume
// inline double density(body b) { return b.mass / sphere_volume(b); } // Calculated the density of a star/planet

// Constants 
const double infinity = std::numeric_limits<double>::infinity(); // infinity
const double pi = 3.1415926535897932385; // pi (rather than using M_PI from cmath)
const double au = 149597870700.0; // Astromonical unit in m
const double lightyear = 9460730472580800.0; // light year in m
const double parsec = 96939420213600000.0; // Parsec in m
const double speed_of_light = 299792458.0; // speed of light in m/s
const double c = 299792458.0; // speed of light in m/s
const double grav_constant = 1; // 6.67430E-11; // Gravitational constant in N (m/kg)^2

// Planets information all data on mass and radii from nssdc.gsfc.nasa.gov
// All data on position and velocity taken from jpl.nasa.gov on the 23rd March 2021
// The XYZ co-ordinates are with regards to the Solar System Barycentre
// Sun
const double sun_mass = 1988500E24; // Solar mass in kg
const double sun_radius = 695508000.0; // Solar radius in m
const double sun_radius_au = d_meters_to_au(sun_radius); // Sun radius in au
const double sun_x_pos_au = -7.182222352667504E-03; // X-component of position vector (au)
const double sun_y_pos_au = 5.505811651340503E-03; // Y-component of position vector (au)
const double sun_z_pos_au = 1.226850949198975E-04; // Z-component of position vector (au)
const double sun_x_vel_au = -6.241082583020532E-06; // X-component of velocity vector (au/day)
const double sun_y_vel_au = -6.526728033623864E-06; // Y-component of velocity vector (au/day)
const double sun_z_vel_au = 2.022080608868780E-07; // Z-component of velocity vector (au/day)

// Mercury
const double mercury_mass = 0.33011E24; // Mecury mass in kg
const double mercury_radius = 24397000; // Mecury radius in m
const double mercury_radius_au = d_meters_to_au(mercury_radius); // Mercury radius in au
const double mercury_x_pos_au = 8.922777525517281E-02; // X-component of position vector (au)
const double mercury_y_pos_au = -4.375500957443055E-01; // X-component of position vector (au)
const double mercury_z_pos_au = -4.492604079725495E-02; // X-component of position vector (au)
const double mercury_x_vel_au = 2.184278287770101E-02; // X-component of velocity vector (au/day)
const double mercury_y_vel_au = 7.414178541645019E-03; // Y-component of velocity vector (au/day)
const double mercury_z_vel_au = -1.397627588255176E-03; // Z-component of velocity vector (au/day)

// Venus
const double venus_mass = 4.8675E24; // Venus mass in kg
const double venus_radius = 60518000; // Venus radius in m
const double venus_radius_au = d_meters_to_au(venus_radius); // Venus radius in au
const double venus_x_pos_au = 7.181692576546067E-01; // X-component of position vector (au)
const double venus_y_pos_au = 9.743349350794047E-03; // Y-component of position vector (au)
const double venus_z_pos_au = -4.167584692402403E-02; // Z-component of position vector (au)
const double venus_x_vel_au = -2.101302331950813E-04; // X-component of velocity vector (au/day)
const double venus_y_vel_au = 2.012623962820257E-02; // Y-component of velocity vector (au/day)
const double venus_z_vel_au = 2.882627485276092E-04; // Z-component of velocity vector (au/day)

// Earth
const double earth_mass = 5.9724E24; // Earth mass in kg
const double earth_radius = 6371000; // Earth radius in m
const double earth_radius_au = d_meters_to_au(earth_radius); // Earth radius in au
const double earth_x_pos_au = -1.003004053589277; // X-component of position vector (au)
const double earth_y_pos_au = -3.437786488206762E-02; // Y-component of position vector (au)
const double earth_z_pos_au = 1.258876159315676E-04; // Z-component of position vector (au)
const double earth_x_vel_au = 4.077723515988597E-04; // X-component of velocity vector (au/day)
const double earth_y_vel_au = -1.725924750960407E-02; // Y-component of velocity vector (au/day)
const double earth_z_vel_au = 5.307601142437262E-07; // Z-component of velocity vector (au/day)

// Moon
const double moon_mass = 0.07346E24; // Moon mass in kg
const double moon_radius = 1737.4E3; // Moon radius in m
const double moon_radius_au = d_meters_to_au(moon_radius); // Moon radius in au
const double moon_x_pos_au = -1.003814404464745E+00; // X-component of position vector (au)
const double moon_y_pos_au = -3.188956686612084E-02; // Y-component of position vector (au)
const double moon_z_pos_au = 2.578958832688566E-04; // Z-component of position vector (au)
const double moon_x_vel_au = -1.267296306713540E-04; // X-component of velocity vector (au/day)
const double moon_y_vel_au = -1.747277319114132E-02; // Y-component of velocity vector (au/day)
const double moon_z_vel_au = 4.052634098149138E-05; // Z-component of velocity vector (au/day)

// Mars
const double mars_mass = 0.64171E24; // Mars mass in kg
const double mars_radius = 33962000; // Mars radius in m
const double mars_radius_au = d_meters_to_au(mars_radius); // Mars radius in au
const double mars_x_pos_au = -4.513699247646418E-01; // X-component of position vector (au)
const double mars_y_pos_au = 1.548921638632211E+00; // Y-component of position vector (au)
const double mars_z_pos_au = 4.336268260066646E-02; // Z-component of position vector (au)
const double mars_x_vel_au = -1.292502071646612E-02; // X-component of velocity vector (au/day)
const double mars_y_vel_au = -2.688693020441130E-03; // Y-component of velocity vector (au/day)
const double mars_z_vel_au = 2.609004905139733E-04; // Z-component of velocity vector (au/day)

// Jupiter
const double jupiter_mass = 1898.19E24; // Jupiter mass in kg
const double jupiter_radius = 71492000; // Jupiter radius in m
const double jupiter_radius_au = d_meters_to_au(jupiter_radius); // Jupiter radius in au
const double jupiter_x_pos_au = 3.494236625948482E+00; // X-component of position vector (au)
const double jupiter_y_pos_au = -3.659406856813893E+00; // Y-component of position vector (au)
const double jupiter_z_pos_au = -6.299397117921929E-02; // Z-component of position vector (au)
const double jupiter_x_vel_au = 5.364744416315402E-03; // X-component of velocity vector (au/day)
const double jupiter_y_vel_au = 5.568069244395276E-03; // Y-component of velocity vector (au/day)
const double jupiter_z_vel_au = -1.431120097750253E-04; // Z-component of velocity vector (au/day)

// Saturn
const double saturn_mass = 568.34E24; // Saturn mass in kg
const double saturn_radius = 60268000; // Saturn radius in m
const double saturn_radius_au = d_meters_to_au(saturn_radius); // Saturn radius in au
const double saturn_x_pos_au = 5.830547171502189E+00; // X-component of position vector (au)
const double saturn_y_pos_au = -8.080797192441453E+00; // Y-component of position vector (au)
const double saturn_z_pos_au = -9.162294219469201E-02; // Z-component of position vector (au)
const double saturn_x_vel_au = 4.212674258253219E-03; // X-component of velocity vector (au/day)
const double saturn_y_vel_au = 3.251775014007405E-03; // Y-component of velocity vector (au/day)
const double saturn_z_vel_au = -2.246251662821705E-04; // Z-component of velocity vector (au/day)

// Uranus
const double uranus_mass = 86.813E24; // Uranus mass in kg
const double uranus_radius = 25559000; // Uranus radius in m
const double uranus_radius_au = d_meters_to_au(uranus_radius); // Uranus radius in au
const double uranus_x_pos_au = 1.513821556732031E+01; // X-component of position vector (au)
const double uranus_y_pos_au = 1.269843001645291E+01; // Y-component of position vector (au)
const double uranus_z_pos_au = -1.489551479554878E-01; // Z-component of position vector (au)
const double uranus_x_vel_au = -2.556625739264284E-03; // X-component of velocity vector (au/day)
const double uranus_y_vel_au = 2.830081826800493E-03; // Y-component of velocity vector (au/day)
const double uranus_z_vel_au = 4.352701256744704E-05; // Z-component of velocity vector (au/day)

// Neptune
const double neptune_mass = 102.413E24; // Neptune mass in kg
const double neptune_radius = 24764000; // Neptune radis in m
const double neptune_radius_au = d_meters_to_au(neptune_radius); // Neptune radius in au
const double neptune_x_pos_au = 2.949553918020323E+01; // X-component of position vector (au)
const double neptune_y_pos_au = -4.973764614399107E+00; // Y-component of position vector (au)
const double neptune_z_pos_au = -5.773300047210381E-01; // Z-component of position vector (au)
const double neptune_x_vel_au = 5.008440721345403E-04; // X-component of velocity vector (au/day)
const double neptune_y_vel_au = 3.113667140492153E-03; // Y-component of velocity vector (au/day)
const double neptune_z_vel_au = -7.578503582209985E-05; // Z-component of velocity vector (au/day)

// Pluto
const double pluto_mass = 0.01303E14; // Pluto mass in kg
const double pluto_radius = 1188000; // Pluto mass in m
const double pluto_radius_au = d_meters_to_au(pluto_radius); // Pluto radius in au
const double pluto_x_pos_au = 1.429134898790048E+01; // X-component of position vector (au)
const double pluto_y_pos_au = -3.110156489194914E+01; // Y-component of position vector (au)
const double pluto_z_pos_au = -8.058582029520671E-01; // Z-component of position vector (au)
const double pluto_x_vel_au = 2.921696248625394E-03; // X-component of velocity vector (au/day)
const double pluto_y_vel_au = 6.390507591300039E-04; // Y-component of velocity vector (au/day)
const double pluto_z_vel_au = -9.017007012589499E-04; // Z-component of velocity vector (au/day)

#endif // UTILITY_H
