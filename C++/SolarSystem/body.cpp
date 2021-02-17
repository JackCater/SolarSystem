// Since the Runge-Kutta method to calculate the total force on a body
// includes all the planets in the universe there is cross referencing of
// header files creating circular dependancy therefore the numerical methods
// are implemented here in body.cpp

#include "body.h"
#include "universe.h"

void body::step_euler(body* acting_force, double dt) {
	double ax, ay, az;
	acting_force->compute_acceleration(this->pos(), ax, ay, az);
	this->x(this->x() + this->vx() * dt);
	this->y(this->y() + this->vy() * dt);
	this->z(this->z() + this->vz() * dt);
	this->vx(this->vx() + ax * dt);
	this->vy(this->vy() + ay * dt);
	this->vz(this->vz() + az * dt);

	// If result is NaN set the value to 0
	// TODO: Properly implement error handling on this
	if (this->x() != this->x()) this->x(0); // According to the IEEE standard, NaN values
	if (this->y() != this->y()) this->y(0); // have the odd property that comparisons involving them are always false
	if (this->z() != this->z()) this->z(0); // that is for a double d; d != d will be true only if d is NaN
	if (this->vx() != this->vx()) this->vx(0);
	if (this->vy() != this->vy()) this->vy(0);
	if (this->vz() != this->vz()) this->vz(0);
	return;
}

void body::step_runge_kutta(body* acting_force, double dt) {
	// Declare Runge-Kutta variables
	double k1vx, k1vy, k1vz, k2vx, k2vy, k2vz, k3vx, k3vy, k3vz, k4vx, k4vy, k4vz;

	// Calculates Runge-Kutta variables 
	double k1x = this->vx(), k1y = this->vy(), k1z = this->vz();
	acting_force->compute_acceleration(distance_vector(this->pos(), acting_force->pos()), k1vx, k1vy, k1vz);

	double k2x = this->vx() + (k1vx * (dt / 2.0)), k2y = this->vy() + (k1vy * (dt / 2.0)), k2z = this->vz() + (k1vz * (dt / 2.0));
	acting_force->compute_acceleration(distance_vector(this->pos(), acting_force->pos()) + point3(k1x * (dt / 2.0), k1y * (dt / 2.0), k1z * (dt / 2.0)), k2vx, k2vy, k2vz);

	double k3x = this->vx() + k2vx * (dt / 2.0), k3y = this->vy() + k2vy * (dt / 2.0), k3z = this->vz() + (k2vz * (dt / 2.0));
	acting_force->compute_acceleration(distance_vector(this->pos(), acting_force->pos()) + point3(k2x * (dt / 2.0), k2y * (dt / 2.0), k2z * (dt / 2.0)), k3vx, k3vy, k3vz);

	double k4x = this->vx() + k3vx * dt, k4y = this->vy() + k3vy * dt, k4z = this->vz() + k3vz * dt;
	acting_force->compute_acceleration(distance_vector(this->pos(), acting_force->pos()) + point3(k3x * dt, k3y * dt, k3z * dt), k4vx, k4vy, k4vz);

	// Updates position and velocity
	this->x(this->x() + (dt / 6.0) * (k1x + (2.0 * k2x) + (2.0 * k3x) + k4x)); // Update X
	this->y(this->y() + (dt / 6.0) * (k1y + (2.0 * k2y) + (2.0 * k3y) + k4y)); // Update Y
	this->z(this->z() + (dt / 6.0) * (k1z + (2.0 * k2z) + (2.0 * k3z) + k4z)); // Update Z
	this->vx(this->vx() + (dt / 6.0) * (k1vx + (2.0 * k2vx) + (2.0 * k3vx) + k4vx)); // Update Vx
	this->vy(this->vy() + (dt / 6.0) * (k1vy + (2.0 * k2vy) + (2.0 * k3vy) + k4vy)); // Update Vy
	this->vz(this->vz() + (dt / 6.0) * (k1vz + (2.0 * k2vz) + (2.0 * k3vz) + k4vz)); // Update Vz

	// If result is NaN set the value to 0
	// TODO: Properly implement error handling on this
	if (this->x() != this->x()) this->x(0); // According to the IEEE standard, NaN values
	if (this->y() != this->y()) this->y(0); // have the odd property that comparisons involving them are always false
	if (this->z() != this->z()) this->z(0); // that is for a double d; d != d will be true only if d is NaN
	if (this->vx() != this->vx()) this->vx(0);
	if (this->vy() != this->vy()) this->vy(0);
	if (this->vz() != this->vz()) this->vz(0);
	return;
}

void body::step_runge_kutta(universe* u, double dt) {
	// Declare Runge-Kutta variables
	double k1vx{}, k1vy{}, k1vz{}, k2vx{}, k2vy{}, k2vz{}, k3vx{}, k3vy{}, k3vz{}, k4vx{}, k4vy{}, k4vz{};

	// Calculates Runge-Kutta variables 
	// The position variables are dependant on only the current velocity of a body
	// The velocity variables are dependant on the force due to all bodies in the universe
	double k1x = this->vx(), k1y = this->vy(), k1z = this->vz();
	for (size_t i = 0; i < u->num_of_bodies(); i++) 
		if (this != u->body_at(i)) 
			u->body_at(i)->compute_acceleration(distance_vector(this->pos(), u->body_at(i)->pos()), k1vx, k1vy, k1vz);

	// Because k2x depends on k1vx they all have to be computed in different for loops
	double k2x = this->vx() + (k1vx * (dt / 2.0)), k2y = this->vy() + (k1vy * (dt / 2.0)), k2z = this->vz() + (k1vz * (dt / 2.0));
	for (size_t i = 0; i < u->num_of_bodies(); i++) 
		if (this != u->body_at(i)) 
			u->body_at(i)->compute_acceleration(distance_vector(this->pos(), u->body_at(i)->pos()) + point3(k1x * (dt / 2.0), k1y * (dt / 2.0), k1z * (dt / 2.0)), k2vx, k2vy, k2vz);
	
	double k3x = this->vx() + k2vx * (dt / 2.0), k3y = this->vy() + k2vy * (dt / 2.0), k3z = this->vz() + (k2vz * (dt / 2.0));
	for (size_t i = 0; i < u->num_of_bodies(); i++) 
		if (this != u->body_at(i)) 
			u->body_at(i)->compute_acceleration(distance_vector(this->pos(), u->body_at(i)->pos()) + point3(k2x * (dt / 2.0), k2y * (dt / 2.0), k2z * (dt / 2.0)), k3vx, k3vy, k3vz);
	
	double k4x = this->vx() + k3vx * dt, k4y = this->vy() + k3vy * dt, k4z = this->vz() + k3vz * dt;
	for (size_t i = 0; i < u->num_of_bodies(); i++) 
		if (this != u->body_at(i)) 
			u->body_at(i)->compute_acceleration(distance_vector(this->pos(), u->body_at(i)->pos()) + point3(k3x * dt, k3y * dt, k3z * dt), k4vx, k4vy, k4vz);

	// Updates position and velocity
	this->x(this->x() + (dt / 6.0) * (k1x + (2.0 * k2x) + (2.0 * k3x) + k4x)); // Update X
	this->y(this->y() + (dt / 6.0) * (k1y + (2.0 * k2y) + (2.0 * k3y) + k4y)); // Update Y
	this->z(this->z() + (dt / 6.0) * (k1z + (2.0 * k2z) + (2.0 * k3z) + k4z)); // Update Z
	this->vx(this->vx() + (dt / 6.0) * (k1vx + (2.0 * k2vx) + (2.0 * k3vx) + k4vx)); // Update Vx
	this->vy(this->vy() + (dt / 6.0) * (k1vy + (2.0 * k2vy) + (2.0 * k3vy) + k4vy)); // Update Vy
	this->vz(this->vz() + (dt / 6.0) * (k1vz + (2.0 * k2vz) + (2.0 * k3vz) + k4vz)); // Update Vz

	// If result is NaN set the value to 0
	// TODO: Properly implement error handling on this
	if (this->x() != this->x()) this->x(0); // According to the IEEE standard, NaN values
	if (this->y() != this->y()) this->y(0); // have the odd property that comparisons involving them are always false
	if (this->z() != this->z()) this->z(0); // that is for a double d; d != d will be true only if d is NaN
	if (this->vx() != this->vx()) this->vx(0);
	if (this->vy() != this->vy()) this->vy(0);
	if (this->vz() != this->vz()) this->vz(0);
	return;
}