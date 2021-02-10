#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include <memory>

#include "body.h"

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

	void clear() { objects.clear(); } // Removes all planets/stars from the universe
	void add(body* object) { objects.push_back(object); } // Adds planet/star to the universe

	unsigned __int64 length() const { return objects.size(); }
	body* body_at(int i) const { return objects.at(i); }

	void total_force() {
		for (const auto& object : objects) {
			double ax, ay, az;
			object->compute_acceleration(point3(1000000000.0, 500000000.0, 0), ax, ay, az);
		}
	}
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