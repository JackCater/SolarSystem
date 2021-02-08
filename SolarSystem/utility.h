// File containing useful constants and functions
#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <limits>
#include <memory>

#include "vec3.h"

// Constants
const double infinity = std::numeric_limits<double>::infinity(); // infinity
const double pi = 3.1415926535897932385; // pi (rather than using M_PI from cmath)
const double au = 149597870700; // Astromonical unit in m
const double lightyear = 9460730472580800; // light year in m
const double speed_of_light = 299792458; // speed of light in m/s
const double c = 299792458; // speed of light in m/s
const double solar_mass = 1988500E24; // Solar mass in kg
const double solar_radius = 695508; // Solar radius in km
const double earth_mass = 5.9724E24; // Earth mass in kg
const double earth_radius = 6371; // Earth radius in km
const double grav_constant = 6.67430E-11; // Gravitational constant in N (m/kg)^2
const double orbital_period = 365.25 * 24 * 3600; // Orbital period of Earth in s
const double aphelion_distance = 152.10E9; // Aphelion distance of Earth in m

// Utility Functions
inline double degrees_to_radians(double degrees) { return degrees * pi / 180.0; } // Converts degree to radians
inline double radians_to_degrees(double radians) { return radians * 180.0 / pi; } // Converts radians to degrees
inline double sphere_volume(body b) { return (4.0 / 3.0) * pi * b.radius() * b.radius() * b.radius(); } // Calculates a spheres volume
inline double density(body b) { return b.mass() / sphere_volume(b); } // Calculated the density of a star/planet

#endif
