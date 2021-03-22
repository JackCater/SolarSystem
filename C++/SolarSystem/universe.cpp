#include "universe.h"

int universe::check_step(universe* u, double err, double tol, double& dt, std::vector<pos_vel_params> pos_vel_vec)
{
	if (err > tol) { // Reject the step
		dt /= 2;
		pos_vel_vec.clear();
		return NO_ERROR;
	} // end if
	else { // Accept the step
		for (auto i = 0; i < pos_vel_vec.size(); i++)
		{
			u->body_at(i)->update_params(pos_vel_vec.at(i)); // Update params
		}
		pos_vel_vec.clear();

		if (err * 2 < tol) { // If error is much smaller than tol
							 // We can increase the time step
			dt *= 2;
			return NO_ERROR;
		} // end if
	} // end else

	return NO_ERROR;
} // end check_step

int universe::step_euler(body* acting_force, double dt) {
	// If body is a nullptr return an error
	if (acting_force == nullptr) return ERR_BODY_NULLPTR;

	for (const auto& object : objects) {
		int retval = object->step_euler(acting_force, dt);
		if (retval != NO_ERROR) return retval;
	} // end for
	return NO_ERROR;
} // end step_euler

int universe::step_euler(universe* u, double dt) {
	// If the universe does not exist return error
	if (u == nullptr) return ERR_UNIVERSE_NULLPTR;

	// If there are no bodies in the universe return an error
	if (u->num_of_bodies == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < u->num_of_bodies; i++)
		if (u->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	// For every body in the universe compute the force felt by all other bodies
	for (const auto& object : objects) {
		int retval = object->step_euler(u, dt);
		if (retval != NO_ERROR) return retval;
	} // end for
	return NO_ERROR;
} // end step_euler

int universe::step_rk4(body* acting_force, double dt) {
	if (acting_force == nullptr) return ERR_BODY_NULLPTR;

	for (const auto& object : objects) {
		int retval = object->step_rk4(acting_force, dt);
		if (retval != NO_ERROR) return retval;
	} // end for			

	return NO_ERROR;
} // end step_rk4

int universe::step_rk4(universe* u, double dt) {
	// If the universe does not exist return error
	if (u == nullptr) return ERR_UNIVERSE_NULLPTR;

	// If there are no bodies in the universe return an error
	if (u->num_of_bodies == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < u->num_of_bodies; i++)
		if (u->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	// For every body in the universe compute the force felt by all other bodies
	for (const auto& object : objects) {
		int retval = object->step_rk4(u, dt);
		if (retval != NO_ERROR) return retval;
	} // end for
	return NO_ERROR;
} // end step_rk4

int universe::step_rkf4(body* acting_force, double dt) {
	if (acting_force == nullptr) return ERR_BODY_NULLPTR;
	for (const auto& object : objects) {
		int retval = object->step_rkf4(acting_force, dt);
		if (retval != NO_ERROR) return retval;
	} // end for			

	return NO_ERROR;
} // end step_rkf4

int universe::step_rkf4(universe* u, double dt) {
	// If the universe does not exist return error
	if (u == nullptr) return ERR_UNIVERSE_NULLPTR;

	// If there are no bodies in the universe return an error
	if (u->num_of_bodies == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < u->num_of_bodies; i++)
		if (u->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	// For every body in the universe compute the force felt by all other bodies
	for (const auto& object : objects) {
		int retval = object->step_rkf4(u, dt);
		if (retval != NO_ERROR) return retval;
	} // end for
	return NO_ERROR;
} // end step_rkf4	

int universe::step_rkf5(body* acting_force, double dt) {
	if (acting_force == nullptr) return ERR_BODY_NULLPTR;
	for (const auto& object : objects) {
		int retval = object->step_rkf5(acting_force, dt);
		if (retval != NO_ERROR) return retval;
	} // end for			

	return NO_ERROR;
} // end step_rkf5

int universe::step_rkf5(universe* u, double dt) {
	// If the universe does not exist return error
	if (u == nullptr) return ERR_UNIVERSE_NULLPTR;

	// If there are no bodies in the universe return an error
	if (u->num_of_bodies == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < u->num_of_bodies; i++)
		if (u->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	// For every body in the universe compute the force felt by all other bodies
	for (const auto& object : objects) {
		int retval = object->step_rkf5(u, dt);
		if (retval != NO_ERROR) return retval;
	} // end for
	return NO_ERROR;
} // end step_rkf5	

int universe::step_rkf45(body* acting_force, double tol, double& dt) {
	// If there is no acting force return an error
	if (acting_force == nullptr) return ERR_BODY_NULLPTR;

	for (const auto& object : objects) {
		int retval = object->step_rkf45(acting_force, tol, dt);
		if (retval != NO_ERROR) return retval;
	} // end for	

	return NO_ERROR;
} // end step_rkf45

int universe::step_rkf45(universe* u, double tol, double& dt) {
	// If the universe does not exist return error
	if (u == nullptr) return ERR_UNIVERSE_NULLPTR;

	// If there are no bodies in the universe return an error
	if (u->num_of_bodies == 0) return ERR_NO_BODY_IN_UNIVERSE;

	// If a body in the universe is a nullptr return error
	for (auto i = 0; i < u->num_of_bodies; i++)
		if (u->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

	std::vector<pos_vel_params> p_vec;
	double err = 0.0;

	// Add a pos vel params for each body
	for (auto i = 0; i < u->num_of_bodies; i++)
		p_vec.emplace_back(pos_vel_params{ 0.0 }); // Create std::vector with pos vel params for all bodies

	int i = 0;
	// For every body in the universe compute the force felt by all other bodies
	for (const auto& object : objects) {
		int retval = object->step_rkf45(u, tol, err, dt, p_vec.at(i));
		i++;
		if (retval != NO_ERROR) return retval;
	} // end for

	// Check if we want to compute the step
	u->check_step(u, err, tol, dt, p_vec);

	return NO_ERROR;
} // end step_rkf45