// Contains the class to create a planet or star
// Since the Runge-Kutta method to calculate the total force on a body
// includes all the planets in the universe there is cross referencing of
// header files creating circular dependancy therefore the numerical methods
// are implemented in body.cpp
#ifndef BODY_H
#define BODY_H

#include <string>

#include "vec3.h"
#include "utility.h"
#include "error.h"

// Forward decleration of universe class
class universe;

/// <summary>
/// A struct containing the rkf45 variables used to compute the rkf4, rkf5 and rkf45 methods
/// </summary>
struct rkf45_variables {
	double k1x, k1y, k1z, k1vx, k1vy, k1vz; 
	double k2x, k2y, k2z, k2vx, k2vy, k2vz;
	double k3x, k3y, k3z, k3vx, k3vy, k3vz;
	double k4x, k4y, k4z, k4vx, k4vy, k4vz;
	double k5x, k5y, k5z, k5vx, k5vy, k5vz;
	double k6x, k6y, k6z, k6vx, k6vy, k6vz;
}; // end rkf45_variables

/// <summary>
/// A class containing methods and functions for a body in space
/// </summary>
class body {
private:
	/*********************************************************
	Member variables
	*********************************************************/
	const std::string _name;	// Name of body
	point3 _centre;				// Centre of star/planet in 3D space (x, y, z)
	double _radius;				// Radius of star/planet
	double _mass;				// Mass of star/planet
	vel3 _velocity;				// Velocity of star/planet (vx, vy, vz)
	bool _include;				// Flag to determine whether the body should be included in the simulation
								// By default this is true
	
	/*********************************************************
	Private functions
	*********************************************************/
	/// <summary>
	/// Checks to see if an error has been caused during computation
	/// </summary>
	/// <param name="acting_force">The acting_force</param>
	/// <returns>The error code, see error.h for more</returns>
	int error_check(body* acting_force);

	/// <summary>
	/// Checks to see if an error has been caused during computation
	/// </summary>
	/// <param name="universe">The universe</param>
	/// <returns>The error code, see error.h for more</returns>
	int error_check(universe* universe);

	/// <summary>
	/// Computes the rk45 variables which are passed by reference
	/// </summary>
	/// <param name="acting_force">The acting force</param>
	/// <param name="variables">The rk45_variable struct</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code, see error.h for more</returns>
	int compute_rkf45_variables(body* acting_force, rkf45_variables& variables, double dt);

	/// <summary>
	/// Computes the rk45 variables which are passed by reference
	/// </summary>
	/// <param name="universe">The universe</param>
	/// <param name="variables">The rk45_variable struct</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code, see error.h for more</returns>
	int compute_rkf45_variables(universe* universe, rkf45_variables& variables, double dt);

	/// <summary>
	/// Sets the member variables of a body to 0
	/// Used when two bodies collide
	/// </summary>
	void set_to_zero() {
		this->_mass = 0;
		this->_radius = 0;
		this->_velocity = vel3(0.0, 0.0, 0.0);
		this->_include = false; // Body will no longer be included in computations
		return;
	} // end set_to_zero

public:
	/*********************************************************
	Constructors and destructors
	*********************************************************/
	/// <summary>
	/// Default constructor
	/// </summary>
	body() : _name("NULL"), _centre(point3(0, 0, 0)), _radius(0), _mass(0), _velocity(vel3(0, 0, 0)), _include(true) {}

	/// <summary>
	/// Modified constructor
	/// </summary>
	/// <param name="name">Name of body</param>
	/// <param name="centre">Position of body in 3D space</param>
	/// <param name="r">Radius of body</param>
	/// <param name="m">Mass of body</param>
	/// <param name="vel">Velocity of body in 3D vector form</param>
	body(const std::string name, point3 centre, double r, double m, vel3 vel) : _name(name), _centre(centre), _radius(r), _mass(m), _velocity(vel), _include(true) {}

	/// <summary>
	/// Destructor
	/// </summary>
	~body() {}; // Destructor

	/*********************************************************
	Getters
	*********************************************************/
	std::string get_name()	const { return _name; } // Get name of body
	double	get_x()			const { return _centre.x(); } // Get X pos
	double	get_y()			const { return _centre.y(); } // Get Y pos
	double	get_z()			const { return _centre.z(); } // Get Z pos
	point3	get_pos()		const { return _centre; } // Get position
	double	get_vx()		const { return _velocity.x(); } // Get X vel
	double	get_vy()		const { return _velocity.y(); } // Get Y vel
	double	get_vz()		const { return _velocity.z(); } // Get Z vel
	vel3	get_vel()		const { return _velocity; } // Get velocity
	double	get_radius()	const { return _radius; } // Get radius
	double	get_mass()		const { return _mass; } // Get mass
	bool	get_inlude()	const { return _include; } // Get include flag

	/*********************************************************
	Setters
	*********************************************************/
	void set_x(double x) { _centre[0] = std::move(x); } // Set X pos
	void set_y(double y) { _centre[1] = std::move(y); } // Set Y pos
	void set_z(double z) { _centre[2] = std::move(z); } // Set Z pos
	void set_pos(point3 position) { _centre = std::move(position); } // Set Position
	void set_vx(double vx) { _velocity[0] = std::move(vx); } // Set X vel
	void set_vy(double vy) { _velocity[1] = std::move(vy); } // Set Y vel
	void set_vz(double vz) { _velocity[2] = std::move(vz); } // Set Z vel
	void set_vel(vel3 vel) { _velocity = std::move(vel); } // Set velocity
														   
	/*********************************************************
	Property definitions (For C# style properties)
	*********************************************************/
	__declspec(property(get = get_name)) std::string name;			// Name
	__declspec(property(get = get_x, put = set_x)) double x;		// X
	__declspec(property(get = get_y, put = set_y)) double y;		// Y
	__declspec(property(get = get_z, put = set_z)) double z;		// Z
	__declspec(property(get = get_pos, put = set_pos)) point3 pos;	// Position
	__declspec(property(get = get_vx, put = set_vx)) double vx;		// Vx
	__declspec(property(get = get_vy, put = set_vy)) double vy;		// Vy
	__declspec(property(get = get_vz, put = set_vz)) double vz;		// Vz
	__declspec(property(get = get_vec, put = set_vel)) vel3 vel;	// Veloclity
	__declspec(property(get = get_radius)) double radius;			// Radius
	__declspec(property(get = get_mass)) double mass;				// Mass
	__declspec(property(get = get_inlude)) bool include;			// Include flag

	/*********************************************************
	Method for computating acceleration
	*********************************************************/
	/// <summary>
	/// Computes the accleration on a body from one other body using Newtonian Physics
	/// </summary>
	/// <param name="pos">Distance between the two bodies</param>
	/// <param name="ax">Acceleration in the x direction</param>
	/// <param name="ay">Acceleration in the y direction</param>
	/// <param name="az">Acceleration in the z direction</param>
	/// <returns>The error code. See error.h for more info</returns>
	int compute_acceleration(point3 pos, double& ax, double& ay, double& az) {
		ax += (grav_constant * _mass * pos.x()) / ((pow(pos.x(), 2) + pow(pos.y(), 2) + pow(pos.z(), 2)) * (sqrt(pow(pos.x(), 2) + pow(pos.y(), 2) + pow(pos.z(), 2))));
		ay += (grav_constant * _mass * pos.y()) / ((pow(pos.x(), 2) + pow(pos.y(), 2) + pow(pos.z(), 2)) * (sqrt(pow(pos.x(), 2) + pow(pos.y(), 2) + pow(pos.z(), 2))));
		az += (grav_constant * _mass * pos.z()) / ((pow(pos.x(), 2) + pow(pos.y(), 2) + pow(pos.z(), 2)) * (sqrt(pow(pos.x(), 2) + pow(pos.y(), 2) + pow(pos.z(), 2))));

		// if the acceleration applied on a body is NaN return an error
		if (ax != ax) return ERR_AX_NAN;
		if (ay != ay) return ERR_AY_NAN;
		if (az != az) return ERR_AZ_NAN;
		return NO_ERROR;
	} // end compute_acceleration

	/*********************************************************
	Numerical methods - functions defined in body.cpp!!
	*********************************************************/
	/// <summary>
	/// Computes one step using the Euler method
	/// NOTE: This method only uses ONE body in the computation
	/// So usually the star is input as the acting force
	/// </summary>
	/// <param name="acting_force">The acting force, usually the star</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_euler(body* acting_force, double dt);

	/// <summary>
	/// Computes one step using the Euler method
	/// and uses all bodies in the universe
	/// </summary>
	/// <param name="u">The universe</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_euler(universe* u, double dt);

	/// <summary>
	/// Computes one step using the Runge Kutta fourth order method
	/// NOTE: This method uses ONE body in the computation
	/// So usually thr star is input at the acting force
	/// </summary>
	/// <param name="acting_force">The acting force, usually the star</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_rk4(body* acting_force, double dt);

	/// <summary>
	/// Computes one step using the Runge kutta fourth order method
	/// and uses all bodies in the universe
	/// </summary>
	/// <param name="universe">The universe</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_rk4(universe* universe, double dt);

	/// <summary>
	/// Computes one step using the Runge Kutta Fehlberg fourth order method
	/// NOTE: This method uses ONE body in the computation
	/// So usually thr star is input at the acting force
	/// </summary>
	/// <param name="acting_force">The acting force, usually the star</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code, see error.h for more</returns>
	int step_rkf4(body* acting_force, double dt);

	/// <summary>
	/// Computes one step using the Runge Kutta Fehlberg fourth order method
	/// and uses all bodies in the universe
	/// </summary>
	/// <param name="universe">The universe object</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code, see error.h for more</returns>
	int step_rkf4(universe* universe, double dt);
	
	/// <summary>
	/// Computes one step using the Runge Kutta Fehlberg fifth order method
	/// NOTE: This method uses ONE body in the computation
	/// So usually the star is input at the acting force
	/// </summary>
	/// <param name="acting_force">The acting force, usually the star</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code, see error.h for more</returns>
	int step_rkf5(body* acting_force, double dt);

	/// <summary>
	/// Computes one step using the Runge Kutta Fehlberg fourth order method
	/// and uses all bodies in the universe
	/// </summary>
	/// <param name="universe">The universe object</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code, see error.h for more</returns>
	int step_rkf5(universe* universe, double dt);
	

	/*********************************************************
	Numerical methods for adaptive time step
	Functions defined in adaptive_method.cpp!!
	*********************************************************/	
	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <param name="tolerance"></param>
	/// <param name="dt"></param>
	/// <returns></returns>
	int step_adaptive_method(body* acting_force, double tolerance, double& dt);
	int step_adaptive_method(universe* universe, double tolerance, double& scalar,  double& dt);
}; // end class body

#endif // BODY_H
