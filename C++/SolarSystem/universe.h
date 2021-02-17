#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include <memory>

#include "body.h"

// Forward decleration
class body;

/// <summary>
/// A class to add stars or planets to the universe
/// e.g. to create a solar system
/// </summary>
class universe : public body {
private:
	std::vector<body*> objects; // List of objects in the universe

public:
	universe() {} // Default constructor
	universe(body* object) { add(object); } // Modified constructor
	~universe() {} // Destructor

	void clear() { objects.clear(); } // Removes all planets/stars from the universe
	void add(body* object) { objects.push_back(object); } // Adds planet/star to the universe

	void step_euler(body* acting_force, double dt) {
		for (const auto& object : objects)
			object->step_euler(acting_force, dt);
		return; 
	}	
	
	void step_runge_kutta(body* acting_force, double dt) {
		for (const auto& object : objects)
			object->step_runge_kutta(acting_force, dt);
		return; 
	}

	void total_force(universe* u, double dt) {
		for (const auto& object : objects)
			object->step_runge_kutta(u, dt);
	}

	// Getters
	unsigned __int64 num_of_bodies() const { return objects.size(); } // Gets number of bodies in universe
	body* body_at(int i) const { return objects.at(i); } // Gets the body at i in the list of bodies
};

/// <summary>
/// A class containing the data collection information such as 
/// time and time step
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

#endif