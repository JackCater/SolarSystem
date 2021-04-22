#include "universe.h"

int universe::check_step(double err, double tol, double& dt, std::vector<pos_vel_params> pos_vel_vec) {
	if (err > tol) { // Reject the step
		dt /= 2; // Half the time step
		pos_vel_vec.clear(); // Remove elements from array
		return NO_ERROR;
	} // end if
	else { // Accept the step
		for (auto i = 0; i < pos_vel_vec.size(); i++) {
			this->body_at(i)->update_params(pos_vel_vec.at(i)); // Update params
		}
		pos_vel_vec.clear(); // Remove elements from array

		if (err * 2 < tol) { // If error is much smaller than tol
							 // We can increase the time step
			dt *= 2;
			return NO_ERROR;
		} // end if
	} // end else

	return NO_ERROR;
} // end check_step

int universe::step_euler(body* acting_force, double dt) {
	// If the universe does not exist return error
	if (this == nullptr) return ERR_UNIVERSE_NULLPTR;

	// If there are no bodies in the universe return an error
	if (this->num_of_bodies == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < this->num_of_bodies; i++)
		if (this->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	if (acting_force == nullptr) return ERR_BODY_NULLPTR;

	for (const auto& object : objects)
		if (object != acting_force) {
			int retval = object->step_euler(acting_force, dt);
			if (retval != NO_ERROR) return retval;
		} // end if			

	return NO_ERROR;
} // end step_euler

int universe::step_euler(double dt) {
	// If the universe does not exist return error
	if (this == nullptr) return ERR_UNIVERSE_NULLPTR;

	// If there are no bodies in the universe return an error
	if (this->num_of_bodies == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < this->num_of_bodies; i++)
		if (this->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	// For every body in the universe compute the force felt by all other bodies
	for (const auto& object : objects) {
		int retval = object->step_euler(this, dt);
		if (retval != NO_ERROR) return retval;
	} // end for
	return NO_ERROR;
} // end step_euler

int universe::step_rk4(body* acting_force, double dt) {
	// If the universe does not exist return error
	if (this == nullptr) return ERR_UNIVERSE_NULLPTR;

	// If there are no bodies in the universe return an error
	if (this->num_of_bodies == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < this->num_of_bodies; i++)
		if (this->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	if (acting_force == nullptr) return ERR_BODY_NULLPTR;

	for (const auto& object : objects)
		if (object != acting_force) {
			int retval = object->step_rk4(acting_force, dt);
			if (retval != NO_ERROR) return retval;
		} // end if			

	return NO_ERROR;
} // end step_rk4

int universe::step_rk4(double dt) {
	// If the universe does not exist return error
	if (this == nullptr) return ERR_UNIVERSE_NULLPTR;

	// If there are no bodies in the universe return an error
	if (this->num_of_bodies == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < this->num_of_bodies; i++)
		if (this->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	// For every body in the universe compute the force felt by all other bodies
	for (const auto& object : objects) {
		int retval = object->step_rk4(this, dt);
		if (retval != NO_ERROR) return retval;
	} // end for
	return NO_ERROR;
} // end step_rk4

int universe::step_rkf4(body* acting_force, double dt) {
	// If the universe does not exist return error
	if (this == nullptr) return ERR_UNIVERSE_NULLPTR;

	// If there are no bodies in the universe return an error
	if (this->num_of_bodies == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < this->num_of_bodies; i++)
		if (this->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	if (acting_force == nullptr) return ERR_BODY_NULLPTR;

	for (const auto& object : objects)
		if (object != acting_force) {
			int retval = object->step_rkf4(acting_force, dt);
			if (retval != NO_ERROR) return retval;
		} // end if			

	return NO_ERROR;
} // end step_rkf4

int universe::step_rkf4(double dt) {
	// If the universe does not exist return error
	if (this == nullptr) return ERR_UNIVERSE_NULLPTR;

	// If there are no bodies in the universe return an error
	if (this->num_of_bodies == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < this->num_of_bodies; i++)
		if (this->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	// For every body in the universe compute the force felt by all other bodies
	for (const auto& object : objects) {
		int retval = object->step_rkf4(this, dt);
		if (retval != NO_ERROR) return retval;
	} // end for
	return NO_ERROR;
} // end step_rkf4	

int universe::step_rkf5(body* acting_force, double dt) {
	// If the universe does not exist return error
	if (this == nullptr) return ERR_UNIVERSE_NULLPTR;

	// If there are no bodies in the universe return an error
	if (this->num_of_bodies == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < this->num_of_bodies; i++)
		if (this->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	if (acting_force == nullptr) return ERR_BODY_NULLPTR;

	for (const auto& object : objects) 
		if (object != acting_force) {
			int retval = object->step_rkf5(acting_force, dt);
			if (retval != NO_ERROR) return retval;
	} // end if			

	return NO_ERROR;
} // end step_rkf5

int universe::step_rkf5(double dt) {
	// If the universe does not exist return error
	if (this == nullptr) return ERR_UNIVERSE_NULLPTR;

	// If there are no bodies in the universe return an error
	if (this->num_of_bodies == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < this->num_of_bodies; i++)
		if (this->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	// For every body in the universe compute the force felt by all other bodies
	for (const auto& object : objects) {
		int retval = object->step_rkf5(this, dt);
		if (retval != NO_ERROR) return retval;
	} // end for
	return NO_ERROR;
} // end step_rkf5	

int universe::step_rkf45(body* acting_force, double tol, double& dt) {
	// If the universe does not exist return error
	if (this == nullptr) return ERR_UNIVERSE_NULLPTR;

	// If there are no bodies in the universe return an error
	if (this->num_of_bodies == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < this->num_of_bodies; i++)
		if (this->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	std::vector<pos_vel_params> p_vec;
	double err = 0.0;

	// Add a pos vel params for each body
	for (auto i = 0; i < this->num_of_bodies; i++)
		p_vec.emplace_back(pos_vel_params{ 0.0 }); // Create std::vector with pos vel params for all bodies

	// For every body in the universe compute the force felt by all other bodies
	int i = 0;
	for (const auto& object : objects) {
		if (object != acting_force) {
			int retval = object->step_rkf45(acting_force, tol, err, dt, p_vec.at(i));
			if (retval != NO_ERROR) return retval;
		} // end if	
		i++;
	} // end for

	// Check if we want to compute the step
	for (auto i = 0; i < this->num_of_bodies; i++)
		if(this->body_at(i) != acting_force)
			this->body_at(i)->check_step(err, tol, dt, p_vec.at(i));

	return NO_ERROR;
} // end step_rkf45

int universe::step_rkf45(double tol, double& dt) {
	// If the universe does not exist return error
	if (this == nullptr) return ERR_UNIVERSE_NULLPTR;

	// If there are no bodies in the universe return an error
	if (this->num_of_bodies == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < this->num_of_bodies; i++)
		if (this->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	std::vector<pos_vel_params> p_vec;
	double err = 0.0;

	// Add a pos vel params for each body
	for (auto i = 0; i < this->num_of_bodies; i++)
		p_vec.emplace_back(pos_vel_params{ 0.0 }); // Create std::vector with pos vel params for all bodies

	int i = 0;
	// For every body in the universe compute the force felt by all other bodies
	for (const auto& object : objects) {
		int retval = object->step_rkf45(this, tol, err, dt, p_vec.at(i));
		if (retval != NO_ERROR) return retval;
		i++;
	} // end for

	// Check if we want to compute the step
	this->check_step(err, tol, dt, p_vec);

	return NO_ERROR;
} // end step_rkf45
