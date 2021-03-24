#ifndef CREATE_UNIVERSE_H
#define CREATE_UNIVERSE_H

#include "universe.h"

// Planets
body sun("Sun", vec_d_au_to_meters(sun_x_pos_au, sun_y_pos_au, sun_z_pos_au), sun_radius, sun_mass, vec_v_au_to_meters(sun_x_vel_au, sun_y_vel_au, sun_z_vel_au));
body mercury("Mercury", vec_d_au_to_meters(mercury_x_pos_au, mercury_y_pos_au, mercury_z_pos_au), mercury_radius, mercury_mass, vec_v_au_to_meters(mercury_x_vel_au, mercury_y_vel_au, mercury_z_vel_au));
body venus("Venus", vec_d_au_to_meters(venus_x_pos_au, venus_y_pos_au, venus_z_pos_au), venus_radius, venus_mass, vec_v_au_to_meters(venus_x_vel_au, venus_y_vel_au, venus_z_vel_au));
body earth("Earth", vec_d_au_to_meters(earth_x_pos_au, earth_y_pos_au, earth_z_pos_au), earth_radius, earth_mass, vec_v_au_to_meters(earth_x_vel_au, earth_y_vel_au, earth_z_vel_au));
body moon("Moon", vec_d_au_to_meters(moon_x_pos_au, moon_y_pos_au, moon_z_pos_au), moon_radius, moon_mass, vec_v_au_to_meters(moon_x_vel_au, moon_y_vel_au, moon_z_vel_au));
body mars("Mars", vec_d_au_to_meters(mars_x_pos_au, mars_y_pos_au, mars_z_pos_au), mars_radius, mars_mass, vec_v_au_to_meters(mars_x_vel_au, mars_y_vel_au, mars_z_vel_au));
body jupiter("Jupiter", vec_d_au_to_meters(jupiter_x_pos_au, jupiter_y_pos_au, jupiter_z_pos_au), jupiter_radius, jupiter_mass, vec_v_au_to_meters(jupiter_x_vel_au, jupiter_y_vel_au, jupiter_z_vel_au));
body saturn("Saturn", vec_d_au_to_meters(saturn_x_pos_au, saturn_y_pos_au, saturn_z_pos_au), saturn_radius, saturn_mass, vec_v_au_to_meters(saturn_x_vel_au, saturn_y_vel_au, saturn_z_vel_au));
body uranus("Uranus", vec_d_au_to_meters(uranus_x_pos_au, uranus_y_pos_au, uranus_z_pos_au), uranus_radius, uranus_mass, vec_v_au_to_meters(uranus_x_vel_au, uranus_y_vel_au, uranus_z_vel_au));
body neptune("Neptune", vec_d_au_to_meters(neptune_x_pos_au, neptune_y_pos_au, neptune_z_pos_au), neptune_radius, neptune_mass, vec_v_au_to_meters(neptune_x_vel_au, neptune_y_vel_au, neptune_z_vel_au));
body pluto("Pluto", vec_d_au_to_meters(pluto_x_pos_au, pluto_y_pos_au, pluto_z_pos_au), pluto_radius, pluto_mass, vec_v_au_to_meters(pluto_x_vel_au, pluto_y_vel_au, pluto_z_vel_au));

universe create_solar_system(void) {
    // Create universe
    universe u;
    u.add(&sun);
    u.add(&mercury);
    u.add(&venus);
    u.add(&earth);
    u.add(&mars);
    u.add(&jupiter);
    u.add(&saturn);
    u.add(&uranus);
    u.add(&neptune);
    u.add(&pluto);
    return u;
} // end create_solar_system

#endif // CREATE_UNIVERSE_H
