// Since the Runge-Kutta method to calculate the total force on a body
// includes all the planets in the universe there is cross referencing of
// header files creating circular dependancy therefore the numerical methods
// are implemented here in body.cpp

#include "body.h"
#include "universe.h"

int body::step_euler(body* acting_force, double dt) {
	// If the body object is null return error
	if (acting_force == nullptr) return ERR_BODY_NULLPTR;

	double ax, ay, az;
	int retval = acting_force->compute_acceleration(this->pos(), ax, ay, az);
	if (retval != NO_ERROR) return retval;

	this->x(this->x() + this->vx() * dt);
	this->y(this->y() + this->vy() * dt);
	this->z(this->z() + this->vz() * dt);
	this->vx(this->vx() - ax * dt);
	this->vy(this->vy() - ay * dt);
	this->vz(this->vz() - az * dt);

	// If result is NaN return error
	if (this->x() != this->x()) return ERR_X_NAN; // According to the IEEE standard, NaN values
	if (this->y() != this->y()) return ERR_Y_NAN; // have the odd property that comparisons involving them are always false
	if (this->z() != this->z()) return ERR_Z_NAN; // that is for a double d; d != d will be true only if d is NaN
	if (this->vx() != this->vx()) return ERR_VX_NAN;
	if (this->vy() != this->vy()) return ERR_VY_NAN;
	if (this->vz() != this->vz()) return ERR_VZ_NAN;
	return NO_ERROR;
} // end step_euler

int body::step_euler(universe* u, double dt) {
	// If the universe does not exist return error
	if (u == nullptr) return ERR_UNIVERSE_NULLPTR;
	
	// If there are no bodies in the universe return an error
	if (u->num_of_bodies() == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < u->num_of_bodies(); i++)
		if (u->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	// Initialise local variables
	double ax{}, ay{}, az{};
	// Loop through the bodies in the universe
	for (auto i = 0; i < u->num_of_bodies(); i++)
		// if the body calling this is not the body at i in the list and both bodies include flags are true
		if (this != u->body_at(i) && this->_include == true && u->body_at(i)->_include == true) {
			int retval = u->body_at(i)->compute_acceleration(this->pos(), ax, ay, az);
			if (retval != NO_ERROR) return retval;
		} // end if

	this->x(this->x() + this->vx() * dt);
	this->y(this->y() + this->vy() * dt);
	this->z(this->z() + this->vz() * dt);
	this->vx(this->vx() - ax * dt);
	this->vy(this->vy() - ay * dt);
	this->vz(this->vz() - az * dt);

	// If result is NaN return error
	if (this->x() != this->x()) return ERR_X_NAN; // According to the IEEE standard, NaN values
	if (this->y() != this->y()) return ERR_Y_NAN; // have the odd property that comparisons involving them are always false
	if (this->z() != this->z()) return ERR_Z_NAN; // that is for a double d; d != d will be true only if d is NaN
	if (this->vx() != this->vx()) return ERR_VX_NAN;
	if (this->vy() != this->vy()) return ERR_VY_NAN;
	if (this->vz() != this->vz()) return ERR_VZ_NAN;
	return NO_ERROR;
} // end step_euler

int body::step_runge_kutta(body* acting_force, double dt) {
	// If there are no body return error 
	if (acting_force == nullptr) return ERR_BODY_NULLPTR;

	// Declare Runge-Kutta variables
	double k1vx = 0, k1vy = 0, k1vz = 0, k2vx = 0, k2vy = 0, k2vz = 0, k3vx = 0, k3vy = 0, k3vz = 0, k4vx = 0, k4vy = 0, k4vz = 0;
	int retval = NO_ERROR;

	// Calculates Runge-Kutta variables 
	// K1
	double k1x = this->vx(), k1y = this->vy(), k1z = this->vz();
	retval = acting_force->compute_acceleration(distance_vector(this->pos(), acting_force->pos()), k1vx, k1vy, k1vz);
	if (retval != NO_ERROR) return retval;

	// K2
	double k2x = this->vx() + (k1vx * (dt / 2.0)), k2y = this->vy() + (k1vy * (dt / 2.0)), k2z = this->vz() + (k1vz * (dt / 2.0));
	retval = acting_force->compute_acceleration(distance_vector(this->pos(), acting_force->pos()) + point3(k1x * (dt / 2.0), k1y * (dt / 2.0), k1z * (dt / 2.0)), k2vx, k2vy, k2vz);
	if (retval != NO_ERROR) return retval;

	// K3
	double k3x = this->vx() + k2vx * (dt / 2.0), k3y = this->vy() + k2vy * (dt / 2.0), k3z = this->vz() + (k2vz * (dt / 2.0));
	retval = acting_force->compute_acceleration(distance_vector(this->pos(), acting_force->pos()) + point3(k2x * (dt / 2.0), k2y * (dt / 2.0), k2z * (dt / 2.0)), k3vx, k3vy, k3vz);
	if (retval != NO_ERROR) return retval;

	// K4
	double k4x = this->vx() + k3vx * dt, k4y = this->vy() + k3vy * dt, k4z = this->vz() + k3vz * dt;
	retval = acting_force->compute_acceleration(distance_vector(this->pos(), acting_force->pos()) + point3(k3x * dt, k3y * dt, k3z * dt), k4vx, k4vy, k4vz);
	if (retval != NO_ERROR) return retval;

	// Updates position and velocity
	this->x(this->x() + (dt / 6.0) * (k1x + (2.0 * k2x) + (2.0 * k3x) + k4x)); // Update X
	this->y(this->y() + (dt / 6.0) * (k1y + (2.0 * k2y) + (2.0 * k3y) + k4y)); // Update Y
	this->z(this->z() + (dt / 6.0) * (k1z + (2.0 * k2z) + (2.0 * k3z) + k4z)); // Update Z
	this->vx(this->vx() - (dt / 6.0) * (k1vx + (2.0 * k2vx) + (2.0 * k3vx) + k4vx)); // Update Vx
	this->vy(this->vy() - (dt / 6.0) * (k1vy + (2.0 * k2vy) + (2.0 * k3vy) + k4vy)); // Update Vy
	this->vz(this->vz() - (dt / 6.0) * (k1vz + (2.0 * k2vz) + (2.0 * k3vz) + k4vz)); // Update Vz

	// If result is NaN return error
	if (this->x() != this->x()) return ERR_X_NAN; // According to the IEEE standard, NaN values
	if (this->y() != this->y()) return ERR_Y_NAN; // have the odd property that comparisons involving them are always false
	if (this->z() != this->z()) return ERR_Z_NAN; // that is for a double d; d != d will be true only if d is NaN
	if (this->vx() != this->vx()) return ERR_VX_NAN;
	if (this->vy() != this->vy()) return ERR_VY_NAN;
	if (this->vz() != this->vz()) return ERR_VZ_NAN;
	return NO_ERROR;
} // end step_ruge_kutta

int body::step_runge_kutta(universe* u, double dt) {
	// If the universe does not exist return error
	if (u == nullptr) return ERR_UNIVERSE_NULLPTR;

	// If there are no bodies in the universe return an error
	if (u->num_of_bodies() == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < u->num_of_bodies(); i++)
		if (u->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	// Declare and initialise Runge-Kutta variables
	double k1vx = 0, k1vy = 0, k1vz = 0, k2vx = 0, k2vy = 0, k2vz = 0, k3vx = 0, k3vy = 0, k3vz = 0, k4vx = 0, k4vy = 0, k4vz = 0;
	int retval = NO_ERROR;

	// Calculates Runge-Kutta variables 
	// The position variables are dependant on only the current velocity of a body
	// The velocity variables are dependant on the force due to all bodies in the universe

	// K1
	double k1x = this->vx(), k1y = this->vy(), k1z = this->vz();
	// Loop through the bodies in the universe
	for (auto i = 0; i < u->num_of_bodies(); i++)
		// if the body calling this is not the body at i in the list and both bodies include flags are true
		if (this != u->body_at(i) && this->_include == true && u->body_at(i)->_include == true) {
			// Compute acceleration
			u->body_at(i)->compute_acceleration(distance_vector(this->pos(), u->body_at(i)->pos()), k1vx, k1vy, k1vz);
			if (retval != NO_ERROR) return retval;
		} // end if

	// Because k2x depends on k1vx they all have to be computed in different for loops
	// K2
	double k2x = this->vx() + (k1vx * (dt / 2.0)), k2y = this->vy() + (k1vy * (dt / 2.0)), k2z = this->vz() + (k1vz * (dt / 2.0));
	// Loop through the bodies in the universe
	for (auto i = 0; i < u->num_of_bodies(); i++)
		// if the body calling this is not the body at i in the list and both bodies include flags are true
		if (this != u->body_at(i) && this->_include == true && u->body_at(i)->_include == true) {
			// Compute acceleration
			u->body_at(i)->compute_acceleration(distance_vector(this->pos(), u->body_at(i)->pos()) + point3(k1x * (dt / 2.0), k1y * (dt / 2.0), k1z * (dt / 2.0)), k2vx, k2vy, k2vz);
			if (retval != NO_ERROR) return retval;
		} // end if
	
	// K3
	double k3x = this->vx() + k2vx * (dt / 2.0), k3y = this->vy() + k2vy * (dt / 2.0), k3z = this->vz() + (k2vz * (dt / 2.0));
	// Loop through the bodies in the universe
	for (auto i = 0; i < u->num_of_bodies(); i++)
		// if the body calling this is not the body at i in the list and both bodies include flags are true
		if (this != u->body_at(i) && this->_include == true && u->body_at(i)->_include == true) {
			// Compute acceleration
			u->body_at(i)->compute_acceleration(distance_vector(this->pos(), u->body_at(i)->pos()) + point3(k2x * (dt / 2.0), k2y * (dt / 2.0), k2z * (dt / 2.0)), k3vx, k3vy, k3vz);
			if (retval != NO_ERROR) return retval;
		} // end if
	
	// K4
	double k4x = this->vx() + k3vx * dt, k4y = this->vy() + k3vy * dt, k4z = this->vz() + k3vz * dt;
	// Loop through the bodies in the universe
	for (auto i = 0; i < u->num_of_bodies(); i++)
		// if the body calling this is not the body at i in the list and both bodies include flags are true
		if (this != u->body_at(i) && this->_include == true && u->body_at(i)->_include == true) {
			// Compute acceleration
			u->body_at(i)->compute_acceleration(distance_vector(this->pos(), u->body_at(i)->pos()) + point3(k3x * dt, k3y * dt, k3z * dt), k4vx, k4vy, k4vz);
			if (retval != NO_ERROR) return retval;
		} // end if 

	// Updates position and velocity
	this->x(this->x() + (dt / 6.0) * (k1x + (2.0 * k2x) + (2.0 * k3x) + k4x)); // Update X
	this->y(this->y() + (dt / 6.0) * (k1y + (2.0 * k2y) + (2.0 * k3y) + k4y)); // Update Y
	this->z(this->z() + (dt / 6.0) * (k1z + (2.0 * k2z) + (2.0 * k3z) + k4z)); // Update Z
	this->vx(this->vx() - (dt / 6.0) * (k1vx + (2.0 * k2vx) + (2.0 * k3vx) + k4vx)); // Update Vx
	this->vy(this->vy() - (dt / 6.0) * (k1vy + (2.0 * k2vy) + (2.0 * k3vy) + k4vy)); // Update Vy
	this->vz(this->vz() - (dt / 6.0) * (k1vz + (2.0 * k2vz) + (2.0 * k3vz) + k4vz)); // Update Vz

	// If two bodies have collided, 'delete' them
	// Loop through the bodies in the universe
	for (auto i = 0; i < u->num_of_bodies(); i++)
		// if the body calling this is not the body at i in the list and both bodies include flags are true
		if (this != u->body_at(i) && this->_include == true && u->body_at(i)->_include == true)
			// If the distance between two bodies in less than the two bodies radii they must have collided
			if (distance(this->_centre, u->body_at(i)->_centre) <= this->_radius + u->body_at(i)->_radius) {
				// Set member variables to zero
				this->set_to_zero();
				u->body_at(i)->set_to_zero();
				//return ERR_BODIES_COLLIDED;
			} // end if

	// If result is NaN return error
	if (this->x() != this->x()) return ERR_X_NAN; // According to the IEEE standard, NaN values
	if (this->y() != this->y()) return ERR_Y_NAN; // have the odd property that comparisons involving them are always false
	if (this->z() != this->z()) return ERR_Z_NAN; // that is for a double d; d != d will be true only if d is NaN
	if (this->vx() != this->vx()) return ERR_VX_NAN;
	if (this->vy() != this->vy()) return ERR_VY_NAN;
	if (this->vz() != this->vz()) return ERR_VZ_NAN;
	return NO_ERROR;
} // end step_runge_kutta
