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
const double parsec = 96939420213600000; // Parsec in m
const double speed_of_light = 299792458; // speed of light in m/s
const double c = 299792458; // speed of light in m/s
const double grav_constant = 6.67430E-11; // Gravitational constant in N (m/kg)^2

// Planets information all data from nssdc.gsfc.nasa.gov
// Sun
const double solar_mass = 1988500E24; // Solar mass in kg
const double solar_radius = 695508000; // Solar radius in m
// Mercury
const double mercury_mass = 0.33011E24; // Mecury mass in kg
const double mercury_radius = 24397000; // Mecury radius in m
// Venus
const double venus_mass = 4.8675E24; // Venus mass in kg
const double venus_radius = 60518000; // Venus radius in m
// Earth
const double earth_mass = 5.9724E24; // Earth mass in kg
const double earth_radius = 6371000; // Earth radius in m
const double orbital_period = 365.25 * 24 * 3600; // Orbital period of Earth in s
const double aphelion_distance = 152.099E9; // Aphelion distance of Earth in m
const double aphelion_velocity = 29.29E3; // Aphelion velocity of Earth in m/s
// Moon
const double moon_mass = 0.07346E24; // Moon mass in kg
const double moon_radius = 17381000; // Moon radius in m
// Mars
const double mars_mass = 0.64171E24; // Mars mass in kg
const double mars_radius = 33962000; // Mars radius in m
// Jupiter
const double jupiter_mass = 1898.19E24; // Jupiter mass in kg
const double jupiter_radius = 71492000; // Jupiter radius in m
// Saturn
const double saturn_mass = 568.34E24; // Saturn mass in kg
const double saturn_radius = 60268000; // Saturn radius in m
// Uranus
const double uranus_mass = 86.813E24; // Uranus mass in kg
const double uranus_radius = 25559000; // Uranus radius in m
// Neptune
const double neptune_mass = 102.413E24; // Neptune mass in kg
const double neptune_radius = 24764000; // Neptune radis in m
// Pluto
const double pluto_mass = 0.01303E14; // Pluto mass in kg
const double pluto_radius = 1188000; // Pluto mass in m

// Utility Functions
inline double degrees_to_radians(double degrees) { return degrees * pi / 180.0; } // Converts degree to radians
inline double radians_to_degrees(double radians) { return radians * 180.0 / pi; } // Converts radians to degrees
// inline double sphere_volume(body b) { return (4.0 / 3.0) * pi * b.radius * b.radius * b.radius; } // Calculates a spheres volume
// inline double density(body b) { return b.mass / sphere_volume(b); } // Calculated the density of a star/planet

#endif // UTILITY_H
