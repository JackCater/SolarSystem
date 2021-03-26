// Since the numerical methods method to calculate the total force on a body
// includes all the planets in the universe there is cross referencing of
// header files creating circular dependancy therefore the numerical methods
// are implemented here in body.cpp

#include "body.h"
#include "universe.h"

#pragma region private functions
/*****************************************************************************************************
PRIVATE FUNCTIONS
*****************************************************************************************************/
int body::compute_acceleration(point3 pos, double& ax, double& ay, double& az) {
	vec3 f; // Force vector
	f = -grav_constant * (this->mass / pos.length_squared()) * unit_vector(pos);
	ax += f.x();
	ay += f.y();
	az += f.z();
	
	// if the acceleration applied on a body is NaN return an error
	if (ax != ax) return ERR_AX_NAN;
	if (ay != ay) return ERR_AY_NAN;
	if (az != az) return ERR_AZ_NAN;
	return NO_ERROR;
} // end compute_acceleration

int body::error_check(body* acting_force) {
	// If two bodies have collided, 'delete' them
	// if both bodies include flags are true
	if (this->_include == true && acting_force->_include == true)
		// If the distance between two bodies in less than the two bodies radii they must have collided
		if (distance(this->_centre, acting_force->_centre) <= this->_radius + acting_force->_radius) {
			std::cerr << "\nBody: " << this->name << " and body: " << acting_force->name << " have collided\n";
			// Set member variables to zero
			this->set_to_zero();
			acting_force->set_to_zero();
			//return ERR_BODIES_COLLIDED;
		} // end if

	// If result is NaN return error
	if (this->x != this->x) return ERR_X_NAN; // According to the IEEE standard, NaN values
	if (this->y != this->y) return ERR_Y_NAN; // have the odd property that comparisons involving them are always false
	if (this->z != this->z) return ERR_Z_NAN; // that is for a double d; d != d will be true only if d is NaN
	if (this->vx != this->vx) return ERR_VX_NAN;
	if (this->vy != this->vy) return ERR_VY_NAN;
	if (this->vz != this->vz) return ERR_VZ_NAN;

	return NO_ERROR;
} // end error_check

int body::error_check(universe* u) {
	// If two bodies have collided, 'delete' them
	// Loop through the bodies in the universe
	for (auto i = 0; i < u->num_of_bodies; i++)
		// if the body calling this is not the body at i in the list and both bodies include flags are true
		if (this != u->body_at(i) && this->_include == true && u->body_at(i)->_include == true)
			// If the distance between two bodies in less than the two bodies radii they must have collided
			if (distance(this->_centre, u->body_at(i)->_centre) <= this->_radius + u->body_at(i)->_radius) {
				std::cerr << "\nBody: " << this->name << " and body: " << u->body_at(i)->name << " have collided\n";
				// Set member variables to zero
				this->set_to_zero();
				u->body_at(i)->set_to_zero();
				//return ERR_BODIES_COLLIDED;
			} // end if

	// If result is NaN return error
	if (this->x != this->x) return ERR_X_NAN; // According to the IEEE standard, NaN values
	if (this->y != this->y) return ERR_Y_NAN; // have the odd property that comparisons involving them are always false
	if (this->z != this->z) return ERR_Z_NAN; // that is for a double d; d != d will be true only if d is NaN
	if (this->vx != this->vx) return ERR_VX_NAN;
	if (this->vy != this->vy) return ERR_VY_NAN;
	if (this->vz != this->vz) return ERR_VZ_NAN;
	return NO_ERROR;
} // end error_check

int body::compute_rkf45_variables(body* acting_force, rkf45_variables& v, double dt) {
	// Init retval	
	int retval = NO_ERROR;

	if (acting_force != this) {
		// Calculates Runge-Kutta variables 
		// K1
		v.k1x = this->vx, v.k1y = this->vy, v.k1z = this->vz;
		retval = acting_force->compute_acceleration(distance_vector(acting_force->pos, this->pos), v.k1vx, v.k1vy, v.k1vz);
		if (retval != NO_ERROR) return retval;

		// K2
		v.k2x = this->vx + (v.k1vx * (dt / 4.0)), v.k2y = this->vy + (v.k1vy * (dt / 4.0)), v.k2z = this->vz + (v.k1vz * (dt / 4.0));
		retval = acting_force->compute_acceleration(distance_vector(acting_force->pos, this->pos) + point3(v.k1x * (dt / 4.0), v.k1y * (dt / 4.0), v.k1z * (dt / 4.0)), v.k2vx, v.k2vy, v.k2vz);
		if (retval != NO_ERROR) return retval;

		// K3
		v.k3x = this->vx + ((3.0 * v.k1vx) / 32.0) + ((9.0 * v.k2vx) / 32.0) * ((3.0 * dt) / 8.0);
		v.k3y = this->vy + ((3.0 * v.k1vy) / 32.0) + ((9.0 * v.k2vy) / 32.0) * ((3.0 * dt) / 8.0);
		v.k3z = this->vz + ((3.0 * v.k1vz) / 32.0) + ((9.0 * v.k2vz) / 32.0) * ((3.0 * dt) / 8.0);
		retval = acting_force->compute_acceleration(distance_vector(acting_force->pos, this->pos) + point3(
			((3.0 * v.k1x) / 32.0) + ((9.0 * v.k2x) / 32.0) * ((3.0 * dt) / 8.0),
			((3.0 * v.k1y) / 32.0) + ((9.0 * v.k2y) / 32.0) * ((3.0 * dt) / 8.0),
			((3.0 * v.k1z) / 32.0) + ((9.0 * v.k2z) / 32.0) * ((3.0 * dt) / 8.0)), v.k3vx, v.k3vy, v.k3vz);
		if (retval != NO_ERROR) return retval;

		// K4
		v.k4x = this->vx + ((1932.0 * v.k1vx) / 2197.0) - ((7200.0 * v.k2vx) / 2197.0) + ((7296.0 * v.k3vx) / 2197.0) * ((12.0 * dt) / 13.0);
		v.k4y = this->vy + ((1932.0 * v.k1vy) / 2197.0) - ((7200.0 * v.k2vy) / 2197.0) + ((7296.0 * v.k3vy) / 2197.0) * ((12.0 * dt) / 13.0);
		v.k4z = this->vz + ((1932.0 * v.k1vz) / 2197.0) - ((7200.0 * v.k2vz) / 2197.0) + ((7296.0 * v.k3vz) / 2197.0) * ((12.0 * dt) / 13.0);
		retval = acting_force->compute_acceleration(distance_vector(acting_force->pos, this->pos) + point3(
			((1932.0 * v.k1x) / 2197.0) - ((7200.0 * v.k2x) / 2197.0) + ((7296.0 * v.k3x) / 2197.0) * ((12.0 * dt) / 13.0),
			((1932.0 * v.k1y) / 2197.0) - ((7200.0 * v.k2y) / 2197.0) + ((7296.0 * v.k3y) / 2197.0) * ((12.0 * dt) / 13.0),
			((1932.0 * v.k1z) / 2197.0) - ((7200.0 * v.k2z) / 2197.0) + ((7296.0 * v.k3z) / 2197.0) * ((12.0 * dt) / 13.0)), v.k4vx, v.k4vy, v.k4vz);
		if (retval != NO_ERROR) return retval;

		// K5
		v.k5x = this->vx + ((439.0 * v.k1vx) / 216.0) - (8.0 * v.k2vx) + ((3680.0 * v.k3vx) / 513.0) - ((845.0 * v.k4vx) / 4104.0) * dt;
		v.k5y = this->vy + ((439.0 * v.k1vy) / 216.0) - (8.0 * v.k2vy) + ((3680.0 * v.k3vy) / 513.0) - ((845.0 * v.k4vy) / 4104.0) * dt;
		v.k5z = this->vz + ((439.0 * v.k1vz) / 216.0) - (8.0 * v.k2vz) + ((3680.0 * v.k3vz) / 513.0) - ((845.0 * v.k4vz) / 4104.0) * dt;
		retval = acting_force->compute_acceleration(distance_vector(acting_force->pos, this->pos) + point3(
			((439.0 * v.k1x) / 216.0) - (8.0 * v.k2x) + ((3680.0 * v.k3x) / 513.0) - ((845.0 * v.k4x) / 4104.0) * dt,
			((439.0 * v.k1y) / 216.0) - (8.0 * v.k2y) + ((3680.0 * v.k3y) / 513.0) - ((845.0 * v.k4y) / 4104.0) * dt,
			((439.0 * v.k1z) / 216.0) - (8.0 * v.k2z) + ((3680.0 * v.k3z) / 513.0) - ((845.0 * v.k4z) / 4104.0) * dt), v.k5vx, v.k5vy, v.k5vz);
		if (retval != NO_ERROR) return retval;

		// K6
		v.k6x = this->vx + (-(8.0 * v.k1vx) / 27.0) + (2.0 * v.k2vx) - ((3544.0 * v.k3vx) / 2565.0) + ((1859.0 * v.k4vx) / 4104.0) - ((11.0 * v.k5vx) / 40.0) * (dt / 2.0);
		v.k6y = this->vy + (-(8.0 * v.k1vy) / 27.0) + (2.0 * v.k2vy) - ((3544.0 * v.k3vy) / 2565.0) + ((1859.0 * v.k4vy) / 4104.0) - ((11.0 * v.k5vy) / 40.0) * (dt / 2.0);
		v.k6z = this->vz + (-(8.0 * v.k1vz) / 27.0) + (2.0 * v.k2vz) - ((3544.0 * v.k3vz) / 2565.0) + ((1859.0 * v.k4vz) / 4104.0) - ((11.0 * v.k5vz) / 40.0) * (dt / 2.0);
		retval = acting_force->compute_acceleration(distance_vector(acting_force->pos, this->pos) + point3(
			(-(8.0 * v.k1x) / 27.0) + (2.0 * v.k2x) - ((3544.0 * v.k3x) / 2565.0) + ((1859.0 * v.k4x) / 4104.0) - ((11.0 * v.k5x) / 40.0) * (dt / 2.0),
			(-(8.0 * v.k1y) / 27.0) + (2.0 * v.k2y) - ((3544.0 * v.k3y) / 2565.0) + ((1859.0 * v.k4y) / 4104.0) - ((11.0 * v.k5y) / 40.0) * (dt / 2.0),
			(-(8.0 * v.k1z) / 27.0) + (2.0 * v.k2z) - ((3544.0 * v.k3z) / 2565.0) + ((1859.0 * v.k4z) / 4104.0) - ((11.0 * v.k5z) / 40.0) * (dt / 2.0)), v.k6vx, v.k6vy, v.k6vz);
		if (retval != NO_ERROR) return retval;
	} // end if

	return NO_ERROR;
} // end compute_rkf45_variables

int body::compute_rkf45_variables(universe* u, rkf45_variables& v, double dt) {
	// Init retval
	int retval = NO_ERROR;

	// Calculates Runge-Kutta variables 
	// K1
	v.k1x = this->vx, v.k1y = this->vy, v.k1z = this->vz;
	// Loop through the bodies in the universe
	for (auto i = 0; i < u->num_of_bodies; i++)
		// if the body calling this is not the body at i in the list and both bodies include flags are true
		if (this != u->body_at(i) && this->_include == true && u->body_at(i)->_include == true) {
			// Compute acceleration
			retval = u->body_at(i)->compute_acceleration(distance_vector(u->body_at(i)->pos, this->pos), v.k1vx, v.k1vy, v.k1vz);
			if (retval != NO_ERROR) return retval;
		} // end if

	// K2
	v.k2x = this->vx + (v.k1vx * (dt / 4.0)), v.k2y = this->vy + (v.k1vy * (dt / 4.0)), v.k2z = this->vz + (v.k1vz * (dt / 4.0));
	// Loop through the bodies in the universe
	for (auto i = 0; i < u->num_of_bodies; i++)
		// if the body calling this is not the body at i in the list and both bodies include flags are true
		if (this != u->body_at(i) && this->_include == true && u->body_at(i)->_include == true) {
			// Compute acceleration
			retval = u->body_at(i)->compute_acceleration(distance_vector(u->body_at(i)->pos, this->pos) + point3(v.k1x * (dt / 4.0), v.k1y * (dt / 4.0), v.k1z * (dt / 4.0)), v.k2vx, v.k2vy, v.k2vz);
			if (retval != NO_ERROR) return retval;
		} // end if

	// K3
	v.k3x = this->vx + (((3.0 * v.k1vx) / 32.0) + ((9.0 * v.k2vx) / 32.0)) * ((3.0 * dt) / 8.0);
	v.k3y = this->vy + (((3.0 * v.k1vy) / 32.0) + ((9.0 * v.k2vy) / 32.0)) * ((3.0 * dt) / 8.0);
	v.k3z = this->vz + (((3.0 * v.k1vz) / 32.0) + ((9.0 * v.k2vz) / 32.0)) * ((3.0 * dt) / 8.0);
	// Loop through the bodies in the universe
	for (auto i = 0; i < u->num_of_bodies; i++)
		// if the body calling this is not the body at i in the list and both bodies include flags are true
		if (this != u->body_at(i) && this->_include == true && u->body_at(i)->_include == true) {
			// Compute acceleration
			retval = u->body_at(i)->compute_acceleration(distance_vector(u->body_at(i)->pos, this->pos) + point3(
				((((3.0 * v.k1x) / 32.0) + ((9.0 * v.k2x) / 32.0)) * ((3.0 * dt) / 8.0)),
				((((3.0 * v.k1y) / 32.0) + ((9.0 * v.k2y) / 32.0)) * ((3.0 * dt) / 8.0)),
				((((3.0 * v.k1z) / 32.0) + ((9.0 * v.k2z) / 32.0)) * ((3.0 * dt) / 8.0))), v.k3vx, v.k3vy, v.k3vz);
			if (retval != NO_ERROR) return retval;
		} // end if

	// K4
	v.k4x = this->vx + (((1932.0 * v.k1vx) / 2197.0) - ((7200.0 * v.k2vx) / 2197.0) + ((7296.0 * v.k3vx) / 2197.0)) * ((12.0 * dt) / 13.0);
	v.k4y = this->vy + (((1932.0 * v.k1vy) / 2197.0) - ((7200.0 * v.k2vy) / 2197.0) + ((7296.0 * v.k3vy) / 2197.0)) * ((12.0 * dt) / 13.0);
	v.k4z = this->vz + (((1932.0 * v.k1vz) / 2197.0) - ((7200.0 * v.k2vz) / 2197.0) + ((7296.0 * v.k3vz) / 2197.0)) * ((12.0 * dt) / 13.0);
	// Loop through the bodies in the universe
	for (auto i = 0; i < u->num_of_bodies; i++)
		// if the body calling this is not the body at i in the list and both bodies include flags are true
		if (this != u->body_at(i) && this->_include == true && u->body_at(i)->_include == true) {
			// Compute acceleration
			retval = u->body_at(i)->compute_acceleration(distance_vector(u->body_at(i)->pos, this->pos) + point3(
				((((1932.0 * v.k1x) / 2197.0) - ((7200.0 * v.k2x) / 2197.0) + ((7296.0 * v.k3x) / 2197.0)) * ((12.0 * dt) / 13.0)),
				((((1932.0 * v.k1y) / 2197.0) - ((7200.0 * v.k2y) / 2197.0) + ((7296.0 * v.k3y) / 2197.0)) * ((12.0 * dt) / 13.0)),
				((((1932.0 * v.k1z) / 2197.0) - ((7200.0 * v.k2z) / 2197.0) + ((7296.0 * v.k3z) / 2197.0)) * ((12.0 * dt) / 13.0))), v.k4vx, v.k4vy, v.k4vz);
			if (retval != NO_ERROR) return retval;
		} // end if

	// K5
	v.k5x = this->vx + (((439.0 * v.k1vx) / 216.0) - (8.0 * v.k2vx) + ((3680.0 * v.k3vx) / 513.0) - ((845.0 * v.k4vx) / 4104.0)) * dt;
	v.k5y = this->vy + (((439.0 * v.k1vy) / 216.0) - (8.0 * v.k2vy) + ((3680.0 * v.k3vy) / 513.0) - ((845.0 * v.k4vy) / 4104.0)) * dt;
	v.k5z = this->vz + (((439.0 * v.k1vz) / 216.0) - (8.0 * v.k2vz) + ((3680.0 * v.k3vz) / 513.0) - ((845.0 * v.k4vz) / 4104.0)) * dt;
	// Loop through the bodies in the universe
	for (auto i = 0; i < u->num_of_bodies; i++)
		// if the body calling this is not the body at i in the list and both bodies include flags are true
		if (this != u->body_at(i) && this->_include == true && u->body_at(i)->_include == true) {
			// Compute acceleration
			retval = u->body_at(i)->compute_acceleration(distance_vector(u->body_at(i)->pos, this->pos) + point3(
				((((439.0 * v.k1x) / 216.0) - (8.0 * v.k2x) + ((3680.0 * v.k3x) / 513.0) - ((845.0 * v.k4x) / 4104.0)) * dt),
				((((439.0 * v.k1y) / 216.0) - (8.0 * v.k2y) + ((3680.0 * v.k3y) / 513.0) - ((845.0 * v.k4y) / 4104.0)) * dt),
				((((439.0 * v.k1z) / 216.0) - (8.0 * v.k2z) + ((3680.0 * v.k3z) / 513.0) - ((845.0 * v.k4z) / 4104.0)) * dt)), v.k5vx, v.k5vy, v.k5vz);
			if (retval != NO_ERROR) return retval;
		} // end if

	// K6
	v.k6x = this->vx + (-(8.0 * v.k1vx) / 27.0) + (2.0 * v.k2vx) - ((3544.0 * v.k3vx) / 2565.0) + ((1859.0 * v.k4vx) / 4104.0) - ((11.0 * v.k5vx) / 40.0) * (dt / 2.0);
	v.k6y = this->vy + (-(8.0 * v.k1vy) / 27.0) + (2.0 * v.k2vy) - ((3544.0 * v.k3vy) / 2565.0) + ((1859.0 * v.k4vy) / 4104.0) - ((11.0 * v.k5vy) / 40.0) * (dt / 2.0);
	v.k6z = this->vz + (-(8.0 * v.k1vz) / 27.0) + (2.0 * v.k2vz) - ((3544.0 * v.k3vz) / 2565.0) + ((1859.0 * v.k4vz) / 4104.0) - ((11.0 * v.k5vz) / 40.0) * (dt / 2.0);
	// Loop through the bodies in the universe
	for (auto i = 0; i < u->num_of_bodies; i++)
		// if the body calling this is not the body at i in the list and both bodies include flags are true
		if (this != u->body_at(i) && this->_include == true && u->body_at(i)->_include == true) {
			// Compute acceleration
			retval = u->body_at(i)->compute_acceleration(distance_vector(u->body_at(i)->pos, this->pos) + point3(
				(-(8.0 * v.k1x) / 27.0) + (2.0 * v.k2x) - ((3544.0 * v.k3x) / 2565.0) + ((1859.0 * v.k4x) / 4104.0) - ((11.0 * v.k5x) / 40.0) * (dt / 2.0),
				(-(8.0 * v.k1y) / 27.0) + (2.0 * v.k2y) - ((3544.0 * v.k3y) / 2565.0) + ((1859.0 * v.k4y) / 4104.0) - ((11.0 * v.k5y) / 40.0) * (dt / 2.0),
				(-(8.0 * v.k1z) / 27.0) + (2.0 * v.k2z) - ((3544.0 * v.k3z) / 2565.0) + ((1859.0 * v.k4z) / 4104.0) - ((11.0 * v.k5z) / 40.0) * (dt / 2.0)), v.k6vx, v.k6vy, v.k6vz);
			if (retval != NO_ERROR) return retval;
		} // end if

	return NO_ERROR;
} // end compute_rkf45_variables

int body::step_adaptive_method(body* acting_force, double& error, double dt, pos_vel_params& p) {
	// If there are no body return error 
	if (acting_force == nullptr) return ERR_BODY_NULLPTR;

	// Init retval
	int retval = NO_ERROR;
	// Compute K variables
	rkf45_variables v{ 0.0 }; // Init all rkf45 variables to 0.0

	retval = compute_rkf45_variables(acting_force, v, dt); // Calculate RKF45 variables
	if (retval != NO_ERROR) return retval;

	// This computes y and z variables for the RKF45 method then calculates the optimal step size
	// Since the time step is now variable, it is passed by reference 
	// rkf4 variables
	double y_x = dt * (((25.0 * v.k1x) / 216.0) + ((1408.0 * v.k3x) / 2565.0) + ((2197.0 * v.k4x) / 4101.0) - (v.k5x / 5.0));
	double y_y = dt * (((25.0 * v.k1y) / 216.0) + ((1408.0 * v.k3y) / 2565.0) + ((2197.0 * v.k4y) / 4101.0) - (v.k5y / 5.0));
	double y_z = dt * (((25.0 * v.k1z) / 216.0) + ((1408.0 * v.k3z) / 2565.0) + ((2197.0 * v.k4z) / 4101.0) - (v.k5z / 5.0));
	double y_vx = dt * (((25.0 * v.k1vx) / 216.0) + ((1408.0 * v.k3vx) / 2565.0) + ((2197.0 * v.k4vx) / 4101.0) - (v.k5vx / 5.0));
	double y_vy = dt * (((25.0 * v.k1vy) / 216.0) + ((1408.0 * v.k3vy) / 2565.0) + ((2197.0 * v.k4vy) / 4101.0) - (v.k5vy / 5.0));
	double y_vz = dt * (((25.0 * v.k1vz) / 216.0) + ((1408.0 * v.k3vz) / 2565.0) + ((2197.0 * v.k4vz) / 4101.0) - (v.k5vz / 5.0));

	// rkf5 variables
	p.x = dt * (((16.0 * v.k1x) / 135.0) + ((6656.0 * v.k3x) / 12825.0) + ((28561.0 * v.k4x) / 56430.0) - ((9.0 * v.k5x) / 50.0) + ((2.0 * v.k6x) / 55.0));
	p.y = dt * (((16.0 * v.k1y) / 135.0) + ((6656.0 * v.k3y) / 12825.0) + ((28561.0 * v.k4y) / 56430.0) - ((9.0 * v.k5y) / 50.0) + ((2.0 * v.k6y) / 55.0));
	p.z = dt * (((16.0 * v.k1z) / 135.0) + ((6656.0 * v.k3z) / 12825.0) + ((28561.0 * v.k4z) / 56430.0) - ((9.0 * v.k5z) / 50.0) + ((2.0 * v.k6z) / 55.0));
	p.vx = dt * (((16.0 * v.k1vx) / 135.0) + ((6656.0 * v.k3vx) / 12825.0) + ((28561.0 * v.k4vx) / 56430.0) - ((9.0 * v.k5vx) / 50.0) + ((2.0 * v.k6vx) / 55.0));
	p.vy = dt * (((16.0 * v.k1vy) / 135.0) + ((6656.0 * v.k3vy) / 12825.0) + ((28561.0 * v.k4vy) / 56430.0) - ((9.0 * v.k5vy) / 50.0) + ((2.0 * v.k6vy) / 55.0));
	p.vz = dt * (((16.0 * v.k1vz) / 135.0) + ((6656.0 * v.k3vz) / 12825.0) + ((28561.0 * v.k4vz) / 56430.0) - ((9.0 * v.k5vz) / 50.0) + ((2.0 * v.k6vz) / 55.0));

	// Calculate y total and z total to compute the difference
	double y_tot = y_x + y_y + y_z + y_vx + y_vy + y_vz;
	double z_tot = p.x + p.y + p.z + p.vx + p.vy + p.vz;

	// Calculate error value
	error = abs(z_tot - y_tot);

	// Check for errors
	retval = error_check(acting_force);
	if (retval != NO_ERROR) return retval;

	return NO_ERROR;
} // end step_adaptive_method

int body::step_adaptive_method(universe* u, double& error, double dt, pos_vel_params& p) {
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
	// Since the time step is now variable, it is passed by reference 
	// rkf4 variables
	double y_x = dt * (((25.0 * v.k1x) / 216.0) + ((1408.0 * v.k3x) / 2565.0) + ((2197.0 * v.k4x) / 4101.0) - (v.k5x / 5.0));
	double y_y = dt * (((25.0 * v.k1y) / 216.0) + ((1408.0 * v.k3y) / 2565.0) + ((2197.0 * v.k4y) / 4101.0) - (v.k5y / 5.0));
	double y_z = dt * (((25.0 * v.k1z) / 216.0) + ((1408.0 * v.k3z) / 2565.0) + ((2197.0 * v.k4z) / 4101.0) - (v.k5z / 5.0));
	double y_vx = dt * (((25.0 * v.k1vx) / 216.0) + ((1408.0 * v.k3vx) / 2565.0) + ((2197.0 * v.k4vx) / 4101.0) - (v.k5vx / 5.0));
	double y_vy = dt * (((25.0 * v.k1vy) / 216.0) + ((1408.0 * v.k3vy) / 2565.0) + ((2197.0 * v.k4vy) / 4101.0) - (v.k5vy / 5.0));
	double y_vz = dt * (((25.0 * v.k1vz) / 216.0) + ((1408.0 * v.k3vz) / 2565.0) + ((2197.0 * v.k4vz) / 4101.0) - (v.k5vz / 5.0));

	// rkf5 variables
	p.x = dt * (((16.0 * v.k1x) / 135.0) + ((6656.0 * v.k3x) / 12825.0) + ((28561.0 * v.k4x) / 56430.0) - ((9.0 * v.k5x) / 50.0) + ((2.0 * v.k6x) / 55.0));
	p.y = dt * (((16.0 * v.k1y) / 135.0) + ((6656.0 * v.k3y) / 12825.0) + ((28561.0 * v.k4y) / 56430.0) - ((9.0 * v.k5y) / 50.0) + ((2.0 * v.k6y) / 55.0));
	p.z = dt * (((16.0 * v.k1z) / 135.0) + ((6656.0 * v.k3z) / 12825.0) + ((28561.0 * v.k4z) / 56430.0) - ((9.0 * v.k5z) / 50.0) + ((2.0 * v.k6z) / 55.0));
	p.vx = dt * (((16.0 * v.k1vx) / 135.0) + ((6656.0 * v.k3vx) / 12825.0) + ((28561.0 * v.k4vx) / 56430.0) - ((9.0 * v.k5vx) / 50.0) + ((2.0 * v.k6vx) / 55.0));
	p.vy = dt * (((16.0 * v.k1vy) / 135.0) + ((6656.0 * v.k3vy) / 12825.0) + ((28561.0 * v.k4vy) / 56430.0) - ((9.0 * v.k5vy) / 50.0) + ((2.0 * v.k6vy) / 55.0));
	p.vz = dt * (((16.0 * v.k1vz) / 135.0) + ((6656.0 * v.k3vz) / 12825.0) + ((28561.0 * v.k4vz) / 56430.0) - ((9.0 * v.k5vz) / 50.0) + ((2.0 * v.k6vz) / 55.0));

	// Calculate y total and z total to compute the difference
	double y_tot = y_x + y_y + y_z + y_vx + y_vy + y_vz;
	double z_tot = p.x + p.y + p.z + p.vx + p.vy + p.vz;

	// Calculate the error between two measurements
	error += abs(z_tot - y_tot);

	// Check for errors
	retval = error_check(u);
	if (retval != NO_ERROR) return retval;

	return NO_ERROR;
} // end step_adapative_method

int body::update_params(pos_vel_params params) {
	this->x += params.x;
	this->y += params.y;
	this->z += params.z;
	this->vx -= params.vx;
	this->vy -= params.vy;
	this->vz -= params.vz;
	return NO_ERROR;
} // end update_params

void body::set_to_zero() {
	this->_mass = 0;
	this->_radius = 0;
	this->_velocity = vel3(0.0, 0.0, 0.0);
	this->_include = false; // Body will no longer be included in computations
	return;
} // end set_to_zero

int body::check_step(double err, double tol, double& dt, pos_vel_params p)
{
	if (err > tol) { // Reject the step
		dt /= 2;
		return NO_ERROR;
	} // end if
	else { // Accept the step
		this->update_params(p);
		if (err * 2 < tol) { // If error is much smaller than tol
							 // We can increase the time step
			dt *= 2;
			return NO_ERROR;
		} // end if
	} // end else

	return NO_ERROR;
} // end check_step
#pragma endregion

#pragma region public functions
/*****************************************************************************************************
PUBLIC FUNCTIONS
*****************************************************************************************************/
int body::step_euler(body* acting_force, double dt) {
	// If the body object is null return error
	if (acting_force == nullptr) return ERR_BODY_NULLPTR;

	int retval = NO_ERROR;
	if (this != acting_force) {
		double ax, ay, az;
		retval = acting_force->compute_acceleration(this->pos, ax, ay, az);
		if (retval != NO_ERROR) return retval;

		this->x += this->vx * dt;
		this->y += this->vy * dt;
		this->z += this->vz * dt;
		this->vx -= ax * dt;
		this->vy -= ay * dt;
		this->vz -= az * dt;
	} // end if
	// Check for errors
	retval = error_check(acting_force);
	if (retval != NO_ERROR) return retval;

	return NO_ERROR;
} // end step_euler

int body::step_euler(universe* u, double dt) {
	// Initialise retval
	int retval = NO_ERROR;
	// If the universe does not exist return error
	if (u == nullptr) return ERR_UNIVERSE_NULLPTR;
	
	// If there are no bodies in the universe return an error
	if (u->num_of_bodies == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < u->num_of_bodies; i++)
		if (u->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	// Initialise local variables
	double ax{}, ay{}, az{};
	// Loop through the bodies in the universe
	for (auto i = 0; i < u->num_of_bodies; i++)
		// if the body calling this is not the body at i in the list and both bodies include flags are true
		if (this != u->body_at(i) && this->_include == true && u->body_at(i)->_include == true) {
			retval = u->body_at(i)->compute_acceleration(this->pos, ax, ay, az);
			if (retval != NO_ERROR) return retval;
		} // end if

	this->x += this->vx * dt;
	this->y += this->vy * dt;
	this->z += this->vz * dt;
	this->vx += ax * dt;
	this->vy += ay * dt;
	this->vz += az * dt;

	// Check for errors
	retval = error_check(u);
	if (retval != NO_ERROR) return retval;

	return NO_ERROR;
} // end step_euler

int body::step_rk4(body* acting_force, double dt) {
	// If there are no body return error 
	if (acting_force == nullptr) return ERR_BODY_NULLPTR;
	int retval = NO_ERROR;

	if (this != acting_force) {
		// Declare Runge-Kutta variables
		double k1vx = 0.0, k1vy = 0.0, k1vz = 0.0, k2vx = 0.0, k2vy = 0.0, k2vz = 0.0, k3vx = 0.0, k3vy = 0.0, k3vz = 0.0, k4vx = 0.0, k4vy = 0.0, k4vz = 0.0;

		// Calculates Runge-Kutta variables 
		// K1
		double k1x = this->vx, k1y = this->vy, k1z = this->vz;
		retval = acting_force->compute_acceleration(distance_vector(acting_force->pos, this->pos), k1vx, k1vy, k1vz);
		if (retval != NO_ERROR) return retval;

		// K2
		double k2x = this->vx + (k1vx * (dt / 2.0)), k2y = this->vy + (k1vy * (dt / 2.0)), k2z = this->vz + (k1vz * (dt / 2.0));
		retval = acting_force->compute_acceleration(distance_vector(acting_force->pos, this->pos) + point3(k1x * (dt / 2.0), k1y * (dt / 2.0), k1z * (dt / 2.0)), k2vx, k2vy, k2vz);
		if (retval != NO_ERROR) return retval;

		// K3
		double k3x = this->vx + k2vx * (dt / 2.0), k3y = this->vy + k2vy * (dt / 2.0), k3z = this->vz + (k2vz * (dt / 2.0));
		retval = acting_force->compute_acceleration(distance_vector(acting_force->pos, this->pos) + point3(k2x * (dt / 2.0), k2y * (dt / 2.0), k2z * (dt / 2.0)), k3vx, k3vy, k3vz);
		if (retval != NO_ERROR) return retval;

		// K4
		double k4x = this->vx + k3vx * dt, k4y = this->vy + k3vy * dt, k4z = this->vz + k3vz * dt;
		retval = acting_force->compute_acceleration(distance_vector(acting_force->pos, this->pos) + point3(k3x * dt, k3y * dt, k3z * dt), k4vx, k4vy, k4vz);
		if (retval != NO_ERROR) return retval;

		// Updates position and velocity
		this->x += (dt / 6.0) * (k1x + (2.0 * k2x) + (2.0 * k3x) + k4x); // Update X
		this->y += (dt / 6.0) * (k1y + (2.0 * k2y) + (2.0 * k3y) + k4y); // Update Y
		this->z += (dt / 6.0) * (k1z + (2.0 * k2z) + (2.0 * k3z) + k4z); // Update Z
		this->vx -= (dt / 6.0) * (k1vx + (2.0 * k2vx) + (2.0 * k3vx) + k4vx); // Update Vx
		this->vy -= (dt / 6.0) * (k1vy + (2.0 * k2vy) + (2.0 * k3vy) + k4vy); // Update Vy
		this->vz -= (dt / 6.0) * (k1vz + (2.0 * k2vz) + (2.0 * k3vz) + k4vz); // Update Vz
	} // end if

	// Check errors
	retval = error_check(acting_force);
	if (retval != NO_ERROR) return retval;

	return NO_ERROR;
} // end step_rk4

int body::step_rk4(universe* u, double dt) {
	// If the universe does not exist return error
	if (u == nullptr) return ERR_UNIVERSE_NULLPTR;

	// If there are no bodies in the universe return an error
	if (u->num_of_bodies == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < u->num_of_bodies; i++)
		if (u->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	// Declare and initialise Runge-Kutta variables
	double k1vx = 0, k1vy = 0, k1vz = 0, k2vx = 0, k2vy = 0, k2vz = 0, k3vx = 0, k3vy = 0, k3vz = 0, k4vx = 0, k4vy = 0, k4vz = 0;
	int retval = NO_ERROR;

	// Calculates Runge-Kutta variables 
	// The position variables are dependant on only the current velocity of a body
	// The velocity variables are dependant on the force due to all bodies in the universe

	// K1
	double k1x = this->vx, k1y = this->vy, k1z = this->vz;
	// Loop through the bodies in the universe
	for (auto i = 0; i < u->num_of_bodies; i++)
		// if the body calling this is not the body at i in the list and both bodies include flags are true
		if (this != u->body_at(i) && this->_include == true && u->body_at(i)->_include == true) {
			// Compute acceleration
			u->body_at(i)->compute_acceleration(distance_vector(u->body_at(i)->pos, this->pos), k1vx, k1vy, k1vz);
			if (retval != NO_ERROR) return retval;
		} // end if

	// Because k2x depends on k1vx they all have to be computed in different for loops
	// K2
	double k2x = this->vx + (k1vx * (dt / 2.0)), k2y = this->vy + (k1vy * (dt / 2.0)), k2z = this->vz + (k1vz * (dt / 2.0));
	// Loop through the bodies in the universe
	for (auto i = 0; i < u->num_of_bodies; i++)
		// if the body calling this is not the body at i in the list and both bodies include flags are true
		if (this != u->body_at(i) && this->_include == true && u->body_at(i)->_include == true) {
			// Compute acceleration
			u->body_at(i)->compute_acceleration(distance_vector(u->body_at(i)->pos, this->pos) + point3(k1x * (dt / 2.0), k1y * (dt / 2.0), k1z * (dt / 2.0)), k2vx, k2vy, k2vz);
			if (retval != NO_ERROR) return retval;
		} // end if
	
	// K3
	double k3x = this->vx + k2vx * (dt / 2.0), k3y = this->vy + k2vy * (dt / 2.0), k3z = this->vz + (k2vz * (dt / 2.0));
	// Loop through the bodies in the universe
	for (auto i = 0; i < u->num_of_bodies; i++)
		// if the body calling this is not the body at i in the list and both bodies include flags are true
		if (this != u->body_at(i) && this->_include == true && u->body_at(i)->_include == true) {
			// Compute acceleration
			u->body_at(i)->compute_acceleration(distance_vector(u->body_at(i)->pos, this->pos) + point3(k2x * (dt / 2.0), k2y * (dt / 2.0), k2z * (dt / 2.0)), k3vx, k3vy, k3vz);
			if (retval != NO_ERROR) return retval;
		} // end if
	
	// K4
	double k4x = this->vx + k3vx * dt, k4y = this->vy + k3vy * dt, k4z = this->vz + k3vz * dt;
	// Loop through the bodies in the universe
	for (auto i = 0; i < u->num_of_bodies; i++)
		// if the body calling this is not the body at i in the list and both bodies include flags are true
		if (this != u->body_at(i) && this->_include == true && u->body_at(i)->_include == true) {
			// Compute acceleration
			u->body_at(i)->compute_acceleration(distance_vector(u->body_at(i)->pos, this->pos) + point3(k3x * dt, k3y * dt, k3z * dt), k4vx, k4vy, k4vz);
			if (retval != NO_ERROR) return retval;
		} // end if 

	// Updates position and velocity
	this->x += (dt / 6.0) * (k1x + (2.0 * k2x) + (2.0 * k3x) + k4x); // Update X
	this->y += (dt / 6.0) * (k1y + (2.0 * k2y) + (2.0 * k3y) + k4y); // Update Y
	this->z += (dt / 6.0) * (k1z + (2.0 * k2z) + (2.0 * k3z) + k4z); // Update Z
	this->vx -= (dt / 6.0) * (k1vx + (2.0 * k2vx) + (2.0 * k3vx) + k4vx); // Update Vx
	this->vy -= (dt / 6.0) * (k1vy + (2.0 * k2vy) + (2.0 * k3vy) + k4vy); // Update Vy
	this->vz -= (dt / 6.0) * (k1vz + (2.0 * k2vz) + (2.0 * k3vz) + k4vz); // Update Vz

	// Check to see if there's an error
	retval = error_check(u);
	if (retval != NO_ERROR) return retval;
	
	return NO_ERROR;
} // end step_rk4

int body::step_rkf4(body* acting_force, double dt) {
	// If there are no body return error 
	if (acting_force == nullptr) return ERR_BODY_NULLPTR;

	// Init retval
	int retval = NO_ERROR;
	if (this != acting_force) {
		// Compute K variables
		rkf45_variables v{ 0.0 }; // Init all rkf45 variables to 0.0
		retval = compute_rkf45_variables(acting_force, v, dt);
		if (retval != NO_ERROR) return retval;

		// Update velocity and position
		this->x += dt * (((25.0 * v.k1x) / 216.0) + ((1408.0 * v.k3x) / 2565.0) + ((2197.0 * v.k4x) / 4101.0) - (v.k5x / 5.0));
		this->y += dt * (((25.0 * v.k1y) / 216.0) + ((1408.0 * v.k3y) / 2565.0) + ((2197.0 * v.k4y) / 4101.0) - (v.k5y / 5.0));
		this->z += dt * (((25.0 * v.k1z) / 216.0) + ((1408.0 * v.k3z) / 2565.0) + ((2197.0 * v.k4z) / 4101.0) - (v.k5z / 5.0));
		this->vx -= dt * (((25.0 * v.k1vx) / 216.0) + ((1408.0 * v.k3vx) / 2565.0) + ((2197.0 * v.k4vx) / 4101.0) - (v.k5vx / 5.0));
		this->vy -= dt * (((25.0 * v.k1vy) / 216.0) + ((1408.0 * v.k3vy) / 2565.0) + ((2197.0 * v.k4vy) / 4101.0) - (v.k5vy / 5.0));
		this->vz -= dt * (((25.0 * v.k1vz) / 216.0) + ((1408.0 * v.k3vz) / 2565.0) + ((2197.0 * v.k4vz) / 4101.0) - (v.k5vz / 5.0));
	} // end if

	// Check for errors
	retval = error_check(acting_force);
	if (retval != NO_ERROR) return retval;

	return NO_ERROR;
} // end step_rkf4

int body::step_rkf4(universe* u, double dt) {
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
	retval = compute_rkf45_variables(u, v, dt);

	// Update velocity and position
	this->x += dt * (((25.0 * v.k1x) / 216.0) + ((1408.0 * v.k3x) / 2565.0) + ((2197.0 * v.k4x) / 4101.0) - (v.k5x / 5.0));
	this->y += dt * (((25.0 * v.k1y) / 216.0) + ((1408.0 * v.k3y) / 2565.0) + ((2197.0 * v.k4y) / 4101.0) - (v.k5y / 5.0));
	this->z += dt * (((25.0 * v.k1z) / 216.0) + ((1408.0 * v.k3z) / 2565.0) + ((2197.0 * v.k4z) / 4101.0) - (v.k5z / 5.0));
	this->vx -= dt * (((25.0 * v.k1vx) / 216.0) + ((1408.0 * v.k3vx) / 2565.0) + ((2197.0 * v.k4vx) / 4101.0) - (v.k5vx / 5.0));
	this->vy -= dt * (((25.0 * v.k1vy) / 216.0) + ((1408.0 * v.k3vy) / 2565.0) + ((2197.0 * v.k4vy) / 4101.0) - (v.k5vy / 5.0));
	this->vz -= dt * (((25.0 * v.k1vz) / 216.0) + ((1408.0 * v.k3vz) / 2565.0) + ((2197.0 * v.k4vz) / 4101.0) - (v.k5vz / 5.0));
	
	// Check for errors
	retval = error_check(u);
	if (retval != NO_ERROR) return retval;
	return NO_ERROR;
} // end step_rkf4

int body::step_rkf5(body* acting_force, double dt) {
	// If there are no body return error 
	if (acting_force == nullptr) return ERR_BODY_NULLPTR;

	// Init retval
	int retval = NO_ERROR;

	if (this != acting_force) {
		// Compute K variables
		rkf45_variables v{ 0.0 };
		if (this != acting_force)
			retval = compute_rkf45_variables(acting_force, v, dt);
		if (retval != NO_ERROR) return retval;

		// Update velocity and position
		this->x += dt * (((16.0 * v.k1x) / 135.0) + ((6656.0 * v.k3x) / 12825.0) + ((28561.0 * v.k4x) / 56430.0) - ((9.0 * v.k5x) / 50.0) + ((2.0 * v.k6x) / 55.0));
		this->y += dt * (((16.0 * v.k1y) / 135.0) + ((6656.0 * v.k3y) / 12825.0) + ((28561.0 * v.k4y) / 56430.0) - ((9.0 * v.k5y) / 50.0) + ((2.0 * v.k6y) / 55.0));
		this->z += dt * (((16.0 * v.k1z) / 135.0) + ((6656.0 * v.k3z) / 12825.0) + ((28561.0 * v.k4z) / 56430.0) - ((9.0 * v.k5z) / 50.0) + ((2.0 * v.k6z) / 55.0));
		this->vx -= dt * (((16.0 * v.k1vx) / 135.0) + ((6656.0 * v.k3vx) / 12825.0) + ((28561.0 * v.k4vx) / 56430.0) - ((9.0 * v.k5vx) / 50.0) + ((2.0 * v.k6vx) / 55.0));
		this->vy -= dt * (((16.0 * v.k1vy) / 135.0) + ((6656.0 * v.k3vy) / 12825.0) + ((28561.0 * v.k4vy) / 56430.0) - ((9.0 * v.k5vy) / 50.0) + ((2.0 * v.k6vy) / 55.0));
		this->vz -= dt * (((16.0 * v.k1vz) / 135.0) + ((6656.0 * v.k3vz) / 12825.0) + ((28561.0 * v.k4vz) / 56430.0) - ((9.0 * v.k5vz) / 50.0) + ((2.0 * v.k6vz) / 55.0));
	} // end if

	// Check for errors
	retval = error_check(acting_force);
	if (retval != NO_ERROR) return retval;

	return NO_ERROR;
} // end step_rkf5

int body::step_rkf5(universe* u, double dt) {
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
	rkf45_variables v{ 0.0 };
	retval = compute_rkf45_variables(u, v, dt);

	// Update velocity and position
	this->x += dt * (((16.0 * v.k1x) / 135.0) + ((6656.0 * v.k3x) / 12825.0) + ((28561.0 * v.k4x) / 56430.0) - ((9.0 * v.k5x) / 50.0) + ((2.0 * v.k6x) / 55.0));
	this->y += dt * (((16.0 * v.k1y) / 135.0) + ((6656.0 * v.k3y) / 12825.0) + ((28561.0 * v.k4y) / 56430.0) - ((9.0 * v.k5y) / 50.0) + ((2.0 * v.k6y) / 55.0));
	this->z += dt * (((16.0 * v.k1z) / 135.0) + ((6656.0 * v.k3z) / 12825.0) + ((28561.0 * v.k4z) / 56430.0) - ((9.0 * v.k5z) / 50.0) + ((2.0 * v.k6z) / 55.0));
	this->vx -= dt * (((16.0 * v.k1vx) / 135.0) + ((6656.0 * v.k3vx) / 12825.0) + ((28561.0 * v.k4vx) / 56430.0) - ((9.0 * v.k5vx) / 50.0) + ((2.0 * v.k6vx) / 55.0));
	this->vy -= dt * (((16.0 * v.k1vy) / 135.0) + ((6656.0 * v.k3vy) / 12825.0) + ((28561.0 * v.k4vy) / 56430.0) - ((9.0 * v.k5vy) / 50.0) + ((2.0 * v.k6vy) / 55.0));
	this->vz -= dt * (((16.0 * v.k1vz) / 135.0) + ((6656.0 * v.k3vz) / 12825.0) + ((28561.0 * v.k4vz) / 56430.0) - ((9.0 * v.k5vz) / 50.0) + ((2.0 * v.k6vz) / 55.0));

	// Check for errors
	retval = error_check(u);
	if (retval != NO_ERROR) return retval;
	return NO_ERROR;
} // end step_rkf5

int body::step_rkf45(body* acting_force, double tol, double& err, double& dt, pos_vel_params& p) {
	// Init retval
	int retval = NO_ERROR;
	if (this != acting_force) {
		retval = step_adaptive_method(acting_force, err, dt, p);
		if (retval != NO_ERROR) return retval;
	} // end if

	retval = error_check(acting_force);
	if (retval != NO_ERROR) return retval;

	return NO_ERROR;
} // end step_rkf45

int body::step_rkf45(body* acting_force, double tol, double& dt) {
	// Init retval
	int retval = NO_ERROR;
	if (this != acting_force) {
		double err = 0.0;
		pos_vel_params p{ 0.0 };
		retval = step_adaptive_method(acting_force, err, dt, p);
		if (retval != NO_ERROR) return retval;

		if (err > tol) { // Reject the step
			dt /= 2;
			return NO_ERROR;
		} // end if
		else { // Accept the step
			this->update_params(p);
			if (err * 2 < tol) { // If error is much smaller than tol
								 // We can increase the time step
				dt *= 2;
				return NO_ERROR;
			} // end if
		} // end else
	} // end if

	retval = error_check(acting_force);
	if (retval != NO_ERROR) return retval;

	return NO_ERROR;
} // end step_rkf45

int body::step_rkf45(universe* u, double tol, double& err, double& dt, pos_vel_params& p) {
	// If the universe does not exist return error
	if (u == nullptr) return ERR_UNIVERSE_NULLPTR;

	// If there are no bodies in the universe return an error
	if (u->num_of_bodies == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < u->num_of_bodies; i++)
		if (u->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	// Init retval
	int retval = NO_ERROR;	
	retval = step_adaptive_method(u, err, dt, p);	
	if (retval != NO_ERROR) return retval;

	return NO_ERROR;
} // end step_rkf45
#pragma endregion
