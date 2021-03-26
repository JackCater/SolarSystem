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

	/*********************************************************
	Private Functions
	*********************************************************/	
	/// <summary>
	/// Checks to see if the step will be accepted and updated parameters
	/// </summary>
	/// <param name="universe">The universe object</param>
	/// <param name="err">The error from the calculation</param>
	/// <param name="tol">The acceptable tolerance on the error</param>
	/// <param name="dt">The time step</param>
	/// <param name="pos_vel_vec">The std::vector containing the position and velocity parameters</param>
	/// <returns>The error code, see error.h for more</returns>
	int check_step(double err, double tol, double& dt, std::vector<pos_vel_params> pos_vel_vec);

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
	void add(body* object) { objects.emplace_back(object); }

	/*********************************************************
	Getters
	*********************************************************/
	unsigned __int64 get_num_of_bodies() const { return objects.size(); } // Get the number of bodies in the vector list
	body* body_at(int i) const { return objects.at(i); } // Get the body at i in the vector list

	/*********************************************************
	Property definitions (For C# style properties)
	*********************************************************/
	__declspec(property(get = get_num_of_bodies)) unsigned __int64 num_of_bodies;	// Number of bodies in universe

	/*********************************************************
	Methods for computation - defined in universe.cpp!!
	*********************************************************/
	/// <summary>
	/// Computes the next step of the simulation using the Euler method
	/// for all planets in the universe but with only ONE body being the acting force
	/// </summary>
	/// <param name="acting_force">The body being the acting force, usually a star</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_euler(body* acting_force, double dt);
	
	/// <summary>
	/// Computes the next step in the simulation using the Euler method
	/// for all planets in the universe with all bodies acting as a force
	/// </summary>
	/// <param name="dt">The time step</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_euler(double dt);
	
	/// <summary>
	/// Computes the next step of the simulation using the Runge Kutta fourth order method
	/// for all planets in the universe but with only ONE body being the acting force
	/// </summary>
	/// <param name="acting_force">The body being the acting force, usually a star</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_rk4(body* acting_force, double dt);

	/// <summary>
	/// Computes the next step in the simulation using the Runge Kutta fourth order method
	/// for all planets in the universe with all bodies acting as a force
	/// </summary>
	/// <param name="dt">The time step</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_rk4(double dt);
	  
	/// <summary>
	/// Computes the next step of the simulation using the Runge Kutta Fehlberg fourth order method
	/// for all planets in the universe but with only ONE body being the acting force
	/// </summary>
	/// <param name="acting_force">The body being the acting force, usually a star</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_rkf4(body* acting_force, double dt);

	/// <summary>
	/// Computes the next step in the simulation using the Runge Kutta Fehlberg fourth order method
	/// for all planets in the universe with all bodies acting as a force
	/// </summary>
	/// <param name="dt">The time step</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_rkf4(double dt);
	/// <summary>
	/// Computes the next step of the simulation using the Runge Kutta Fehlberg fifth order method
	/// for all planets in the universe but with only ONE body being the acting force
	/// </summary>
	/// <param name="acting_force">The body being the acting force, usually a star</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_rkf5(body* acting_force, double dt);

	/// <summary>
	/// Computes the next step in the simulation using the Runge Kutta Fehlberg fifth order method
	/// for all planets in the universe with all bodies acting as a force
	/// </summary>
	/// <param name="dt">The time step</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_rkf5(double dt);
	  
	/// <summary>
	/// Computes the next step of the simulation using the Runge Kutta Fehlberg fifth order method with an adaptive time step
	/// for all planets in the universe but with only ONE body being the acting force
	/// </summary>
	/// <param name="acting_force">The body being the acting force, usually a star</param>
	/// <param name="dt">The time step, for the adaptive method this needs to be passed by reference</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_rkf45(body* acting_force, double tol, double& dt);

	/// <summary>
	/// Computes the next step in the simulation using the Runge Kutta Fehlberg fifth order method with an adaptive time step
	/// for all planets in the universe with all bodies acting as a force
	/// </summary>
	/// <param name="dt">The time step, for the adaptive method this needs to be passed by reference</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_rkf45(double tol, double& dt);
}; // end class universe

/// <summary>
/// A class containing the data collection information such as 
/// time and time step, this may be useful instead of defining it all in main
/// just contruct the data_collection class containing this info
/// </summary>
class data_collection
{
private:
	const int _max_number_of_steps; // Number of steps to compute
	int _step_number; // The current step number
	const double _final_time; // Final time
	double _dt; // Time step
	double _time; // Current time

public:
	/// <summary>
	/// Default constructor
	/// Number of steps = 1000,
	/// Final time = 1 year (86400 * 365 seconds),
	/// dt = 1 day (86400s),
	/// time = 0 (intially),
	/// </summary>
	data_collection() : _max_number_of_steps(1000), _step_number(0), _final_time(86400.0 * 365.0), _dt(86400.0), _time(0.0) {}

	/// <summary>
	/// Modified constructor
	/// time = 0 (initially)
	/// </summary>
	/// <param name="number_of_steps">The number of steps to compute</param>
	/// <param name="final_time">The time to stop the computation</param>
	/// <param name="dt">The time step</param>
	data_collection(int number_of_steps, double final_time, double dt) : _max_number_of_steps(number_of_steps), _step_number(0), _final_time(final_time), _dt(dt), _time(0.0) {}

	// Getters
	int number_of_steps() const{ return _max_number_of_steps; } // Get number of steps
	int step_number() const { return _step_number; } // Get current step number
	double final_time() const { return _final_time; } // Get final time
	double get_dt() const { return _dt; } // Get time step
	double time() const { return _time; } // Get time

	// Setters
	void step_number(int step_no) { _step_number = std::move(step_no); } // Set step number
	void set_dt(double dt) { _dt = std::move(dt); } // Set time step
	void time(double time) { _time = std::move(time); } // Set time
	
	// Property definition
	__declspec(property(get = get_dt, put = set_dt)) double dt;		// dt
}; // end class data_collection

#endif // UNIVERSE_H