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
	/// <summary>
	/// Gets the number of bodies in the universe
	/// </summary>
	/// <returns>The number of bodies in the universe</returns>
	unsigned __int64 num_of_bodies() const { return objects.size(); }

	/// <summary>
	/// Get the body in the universe at i
	/// </summary>
	/// <param name="i">The bodies index in the universe</param>
	/// <returns>A pointer to the body in the universe</returns>
	body* body_at(int i) const { return objects.at(i); }

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
		if (acting_force == nullptr) return ERR_NO_ACTING_FORCE;

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
		if (u == nullptr) return ERR_NO_BODY_IN_UNIVERSE;

		for (auto i = 0; i < u->num_of_bodies(); i++)
			if (u->body_at(i) == nullptr) return ERR_NO_ACTING_FORCE;

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
		if (acting_force == nullptr) return ERR_NO_ACTING_FORCE;

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
		if (u == nullptr) return ERR_NO_BODY_IN_UNIVERSE;

		for (auto i = 0; i < u->num_of_bodies(); i++)
			if (u->body_at(i) == nullptr) return ERR_NO_ACTING_FORCE;

		for (const auto& object : objects) {
			int retval = object->step_runge_kutta(u, dt);
			if (retval != NO_ERROR) return retval;
		} // end for
		return NO_ERROR; 
	} // end step_runge_kutta
};

/// <summary>
/// A class containing the data collection information such as 
/// time and time step, this may be useful
/// </summary>
class data_collection
{
private:
	int _number_of_steps; // Number of steps to compute
	double _final_time; // Final time
	double _dt; // Time step
	double _time; // Current time

public:
	data_collection() : _number_of_steps(1000), _final_time(1.0), _dt(_final_time / (double)_number_of_steps), _time(0.0) {}
	data_collection(int number_of_steps, double final_time) : _number_of_steps(number_of_steps), _final_time(final_time), _dt(final_time / (double)number_of_steps), _time(0.0) {}

	// Getters
	double number_of_steps() const{ return _number_of_steps; } // Get number of steps
	double final_time() const { return _final_time; } // Get final time
	double dt() const { return _dt; } // Get time step
	double time() const { return _time; } // Get time

	// Setters
	void time(double time) { _time = std::move(time); } // Set time
};

#endif // UNIVERSE_H