#include "body.h"
#include "universe.h"

int body::step_adaptive_method(body* acting_force, double tol, double& dt) {
	// If there are no body return error 
	if (acting_force == nullptr) return ERR_BODY_NULLPTR;

	// Init retval
	int retval = NO_ERROR;

	// Compute K variables
	rkf45_variables v{ 0.0 }; // Init all rkf45 variables to 0.0
	retval = compute_rkf45_variables(acting_force, v, dt); // Calculate RKF45 variables
	if (retval != NO_ERROR) return retval;

	// This computes y and z variables for the RKF45 method then calculates the optimal step size
	// The optimal step size can be determined by multiplying the scalar 's' by the current step size 'dt'
	// Since the time step is now variable, it is passed by referance 
	// rkf4 variables
	double y_x = dt * (((25.0 * v.k1x) / 216.0) + ((1408.0 * v.k3x) / 2565.0) + ((2197.0 * v.k4x) / 4101.0) - (v.k5x / 5.0));
	double y_y = dt * (((25.0 * v.k1y) / 216.0) + ((1408.0 * v.k3y) / 2565.0) + ((2197.0 * v.k4y) / 4101.0) - (v.k5y / 5.0));
	double y_z = dt * (((25.0 * v.k1z) / 216.0) + ((1408.0 * v.k3z) / 2565.0) + ((2197.0 * v.k4z) / 4101.0) - (v.k5z / 5.0));
	double y_vx = dt * (((25.0 * v.k1vx) / 216.0) + ((1408.0 * v.k3vx) / 2565.0) + ((2197.0 * v.k4vx) / 4101.0) - (v.k5vx / 5.0));
	double y_vy = dt * (((25.0 * v.k1vy) / 216.0) + ((1408.0 * v.k3vy) / 2565.0) + ((2197.0 * v.k4vy) / 4101.0) - (v.k5vy / 5.0));
	double y_vz = dt * (((25.0 * v.k1vz) / 216.0) + ((1408.0 * v.k3vz) / 2565.0) + ((2197.0 * v.k4vz) / 4101.0) - (v.k5vz / 5.0));

	// rkf5 variables
	double z_x = dt * (((16.0 * v.k1x) / 135.0) + ((6656.0 * v.k3x) / 12825.0) + ((28561.0 * v.k4x) / 56430.0) - ((9.0 * v.k5x) / 50.0) + ((2.0 * v.k6x) / 55.0));
	double z_y = dt * (((16.0 * v.k1y) / 135.0) + ((6656.0 * v.k3y) / 12825.0) + ((28561.0 * v.k4y) / 56430.0) - ((9.0 * v.k5y) / 50.0) + ((2.0 * v.k6y) / 55.0));
	double z_z = dt * (((16.0 * v.k1z) / 135.0) + ((6656.0 * v.k3z) / 12825.0) + ((28561.0 * v.k4z) / 56430.0) - ((9.0 * v.k5z) / 50.0) + ((2.0 * v.k6z) / 55.0));
	double z_vx = dt * (((16.0 * v.k1vx) / 135.0) + ((6656.0 * v.k3vx) / 12825.0) + ((28561.0 * v.k4vx) / 56430.0) - ((9.0 * v.k5vx) / 50.0) + ((2.0 * v.k6vx) / 55.0));
	double z_vy = dt * (((16.0 * v.k1vy) / 135.0) + ((6656.0 * v.k3vy) / 12825.0) + ((28561.0 * v.k4vy) / 56430.0) - ((9.0 * v.k5vy) / 50.0) + ((2.0 * v.k6vy) / 55.0));
	double z_vz = dt * (((16.0 * v.k1vz) / 135.0) + ((6656.0 * v.k3vz) / 12825.0) + ((28561.0 * v.k4vz) / 56430.0) - ((9.0 * v.k5vz) / 50.0) + ((2.0 * v.k6vz) / 55.0));

	// Update velocity and position
	this->x += z_x;
	this->y += z_y;
	this->z += z_z;
	this->vx -= z_vx;
	this->vy -= z_vy;
	this->vz -= z_vz;

	// Calculate y total and z total to compute the difference. Needed to calculate the scalar value
	double y_tot = y_x + y_y + y_z + y_vx + y_vy + y_vz;
	double z_tot = z_x + z_y + z_z + z_vx + z_vy + z_vz;

	// Calculate the scalar value
	// s = (tol h)/(2 |z - y|) ^ 1/4
	double s = pow((tol * dt) / (2 * abs(z_tot - y_tot)), 1.0 / 4.0);

	// Update time step
	dt = s * dt;

	// Check for errors
	retval = error_check(acting_force);
	if (retval != NO_ERROR) return retval;

	return NO_ERROR;

}int body::step_adaptive_method(universe* u, double tol, double& s, double& dt) {
	// If the universe does not exist return error
	if (u == nullptr) return ERR_UNIVERSE_NULLPTR;

	// If there are no bodies in the universe return an error
	if (u->num_of_bodies == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < u->num_of_bodies; i++)
		if (u->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	// Init retval
	int retval = NO_ERROR;

	// Compute K variables
	rkf45_variables v{ 0.0 }; // Init all rkf45 variables to 0.0
	retval = compute_rkf45_variables(u, v, dt); // Calculate RKF45 variables
	if (retval != NO_ERROR) return retval;

	// This computes y and z variables for the RKF45 method then calculates the optimal step size
	// The optimal step size can be determined by multiplying the scalar 's' by the current step size 'dt'
	// Since the time step is now variable, it is passed by referance 
	// rkf4 variables
	double y_x = dt * (((25.0 * v.k1x) / 216.0) + ((1408.0 * v.k3x) / 2565.0) + ((2197.0 * v.k4x) / 4101.0) - (v.k5x / 5.0));
	double y_y = dt * (((25.0 * v.k1y) / 216.0) + ((1408.0 * v.k3y) / 2565.0) + ((2197.0 * v.k4y) / 4101.0) - (v.k5y / 5.0));
	double y_z = dt * (((25.0 * v.k1z) / 216.0) + ((1408.0 * v.k3z) / 2565.0) + ((2197.0 * v.k4z) / 4101.0) - (v.k5z / 5.0));
	double y_vx = dt * (((25.0 * v.k1vx) / 216.0) + ((1408.0 * v.k3vx) / 2565.0) + ((2197.0 * v.k4vx) / 4101.0) - (v.k5vx / 5.0));
	double y_vy = dt * (((25.0 * v.k1vy) / 216.0) + ((1408.0 * v.k3vy) / 2565.0) + ((2197.0 * v.k4vy) / 4101.0) - (v.k5vy / 5.0));
	double y_vz = dt * (((25.0 * v.k1vz) / 216.0) + ((1408.0 * v.k3vz) / 2565.0) + ((2197.0 * v.k4vz) / 4101.0) - (v.k5vz / 5.0));

	// rkf5 variables
	double z_x = dt * (((16.0 * v.k1x) / 135.0) + ((6656.0 * v.k3x) / 12825.0) + ((28561.0 * v.k4x) / 56430.0) - ((9.0 * v.k5x) / 50.0) + ((2.0 * v.k6x) / 55.0));
	double z_y = dt * (((16.0 * v.k1y) / 135.0) + ((6656.0 * v.k3y) / 12825.0) + ((28561.0 * v.k4y) / 56430.0) - ((9.0 * v.k5y) / 50.0) + ((2.0 * v.k6y) / 55.0));
	double z_z = dt * (((16.0 * v.k1z) / 135.0) + ((6656.0 * v.k3z) / 12825.0) + ((28561.0 * v.k4z) / 56430.0) - ((9.0 * v.k5z) / 50.0) + ((2.0 * v.k6z) / 55.0));
	double z_vx = dt * (((16.0 * v.k1vx) / 135.0) + ((6656.0 * v.k3vx) / 12825.0) + ((28561.0 * v.k4vx) / 56430.0) - ((9.0 * v.k5vx) / 50.0) + ((2.0 * v.k6vx) / 55.0));
	double z_vy = dt * (((16.0 * v.k1vy) / 135.0) + ((6656.0 * v.k3vy) / 12825.0) + ((28561.0 * v.k4vy) / 56430.0) - ((9.0 * v.k5vy) / 50.0) + ((2.0 * v.k6vy) / 55.0));
	double z_vz = dt * (((16.0 * v.k1vz) / 135.0) + ((6656.0 * v.k3vz) / 12825.0) + ((28561.0 * v.k4vz) / 56430.0) - ((9.0 * v.k5vz) / 50.0) + ((2.0 * v.k6vz) / 55.0));

	// Update velocity and position
	this->x += z_x;
	this->y += z_y;
	this->z += z_z;
	this->vx -= z_vx;
	this->vy -= z_vy;
	this->vz -= z_vz;

	// Calculate y total and z total to compute the difference. Needed to calculate the scalar value
	double y_tot = y_x + y_y + y_z + y_vx + y_vy + y_vz;
	double z_tot = z_x + z_y + z_z + z_vx + z_vy + z_vz;

	// Calculate the scalar value
	// s = (tol h)/(2 |z - y|) ^ 1/4
	s = pow((tol * dt) / (2 * abs(z_tot - y_tot)), 1.0 / 4.0);

	// Check for errors
	retval = error_check(u);
	if (retval != NO_ERROR) return retval;

	return NO_ERROR;
}