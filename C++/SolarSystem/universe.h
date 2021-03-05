#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include <memory>

#include "body.h"
#include "error.h"

// Forward decleration
class body;

/// <summary>
/// A class to add stars or planets to the universe
/// e.g. to create a solar system
/// </summary>
class universe : public body {
private:
	/*********************************************************
	Member variables
	*********************************************************/
	std::vector<body*> objects; // List of objects in the universe

public:
	/*********************************************************
	Constructors and destructors
	*********************************************************/
	/// <summary>
	/// Default constructor
	/// Constructs an empty universe
	/// </summary>
	universe() {}

	/// <summary>
	/// Modified constructor
	/// </summary>
	/// <param name="object">The body in the universe</param>
	universe(body* object) { add(object); } // Modified constructor
	
	/// <summary>
	/// Destructor
	/// </summary>
	~universe() {} // Destructor

	/// <summary>
	/// Removes all planets/stars from the universe
	/// </summary>
	void clear() { objects.clear(); }

	/// <summary>
	/// Adds planet/star to the universe
	/// </summary>
	/// <param name="object">The planet/star</param>
	void add(body* object) { objects.push_back(object); }

	/*********************************************************
	Getters
	*********************************************************/
	unsigned __int64 num_of_bodies() const { return objects.size(); } // Get the number of bodies in the vector list
	body* body_at(int i) const { return objects.at(i); } // Get the body at i in the vector list

	/*********************************************************
	Methods for computation
	*********************************************************/
	/// <summary>
	/// Computes the next step of the simulation using the Euler method
	/// for all planets in the universe but with only ONE body being the acting force
	/// </summary>
	/// <param name="acting_force">The body being the acting force, usually a star</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_euler(body* acting_force, double dt) {
		// If body is a nullptr return an error
		if (acting_force == nullptr) return ERR_BODY_NULLPTR;

		for (const auto& object : objects) {
			int retval = object->step_euler(acting_force, dt);
			if (retval != NO_ERROR) return retval;
		} // end for
		return NO_ERROR; 
	} // end step_euler
	
	/// <summary>
	/// Computes the next step in the simulation using the Euler method
	/// for all planets in the universe with all bodies acting as a force
	/// </summary>
	/// <param name="u">The universe</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_euler(universe* u, double dt) {
		// If the universe does not exist return error
		if (u == nullptr) return ERR_UNIVERSE_NULLPTR;

		// If there are no bodies in the universe return an error
		if (u->num_of_bodies() == 0) return ERR_NO_BODY_IN_UNIVERSE;

		// If a body in the universe is a nullptr return error
		for (auto i = 0; i < u->num_of_bodies(); i++)
			if (u->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

		// For every body in the universe compute the force felt by all other bodies
		for (const auto& object : objects) { 
			int retval = object->step_euler(u, dt); 
			if (retval != NO_ERROR) return retval;
		} // end for
		return NO_ERROR; 
	} // end step_euler
	
	/// <summary>
	/// Computes the next step of the simulation using the Runge Kutta method
	/// for all planets in the universe but with only ONE body being the acting force
	/// </summary>
	/// <param name="acting_force">The body being the acting force, usually a star</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_runge_kutta(body* acting_force, double dt) {
		if (acting_force == nullptr) return ERR_BODY_NULLPTR;

		for (const auto& object : objects) {
			int retval = object->step_runge_kutta(acting_force, dt);
			if (retval != NO_ERROR) return retval;
		} // end for			

		return NO_ERROR; 
	} // end step_runge_kutta

	/// <summary>
	/// Computes the next step in the simulation using the Runge Kutta method
	/// for all planets in the universe with all bodies acting as a force
	/// </summary>
	/// <param name="u">The universe</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_runge_kutta(universe* u, double dt) { 
		// If the universe does not exist return error
		if (u == nullptr) return ERR_UNIVERSE_NULLPTR;

		// If there are no bodies in the universe return an error
		if (u->num_of_bodies() == 0) return ERR_NO_BODY_IN_UNIVERSE;

		// If a body in the universe is a nullptr return error
		for (auto i = 0; i < u->num_of_bodies(); i++)
			if (u->body_at(i) == nullptr) return ERR_BODY_NULLPTR;

		// For every body in the universe compute the force felt by all other bodies
		for (const auto& object : objects) {
			int retval = object->step_runge_kutta(u, dt);
			if (retval != NO_ERROR) return retval;
		} // end for
		return NO_ERROR; 
	} // end step_runge_kutta
}; // end class universe

/// <summary>
/// A class containing the data collection information such as 
/// time and time step, this may be useful instead of defining it all in main
/// just contruct the data_collection class containing this info
/// </summary>
class data_collection
{
private:
	int _number_of_steps; // Number of steps to compute
	double _final_time; // Final time
	double _dt; // Time step
	double _time; // Current time

public:
	/// <summary>
	/// Default constructor
	/// Number of steps = 1000
	/// Final time = 1
	/// dt = number of steps / final time
	/// time = 0 (intially)
	/// </summary>
	data_collection() : _number_of_steps(1000), _final_time(1.0), _dt(_final_time / (double)_number_of_steps), _time(0.0) {}

	/// <summary>
	/// Modified constructor
	/// dt = number of steps / final time
	/// time = 0 (initially)
	/// </summary>
	/// <param name="number_of_steps">The number of steps to compute</param>
	/// <param name="final_time">The time to stop the computation</param>
	data_collection(int number_of_steps, double final_time) : _number_of_steps(number_of_steps), _final_time(final_time), _dt(final_time / (double)number_of_steps), _time(0.0) {}

	// Getters
	double number_of_steps() const{ return _number_of_steps; } // Get number of steps
	double final_time() const { return _final_time; } // Get final time
	double dt() const { return _dt; } // Get time step
	double time() const { return _time; } // Get time

	// Setters
	void time(double time) { _time = std::move(time); } // Set time
}; // end class data_collection

#endif // UNIVERSE_H