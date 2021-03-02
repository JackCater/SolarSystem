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
/// A class containing methods and functions for a body in space
/// </summary>
class body {
private:
	std::string _name; // Name of body
	point3 _centre; // Centre of star/planet in 3D space (x, y, z)
	double _radius; // Radius of star/planet
	double _mass; // Mass of star/planet
	vel3 _velocity; // Velocity of star/planet (vx, vy, vz)

public:
	/// <summary>
	/// Default constructor
	/// </summary>
	body() : _name("NULL"), _centre(point3(0, 0, 0)), _radius(0), _mass(0), _velocity(vel3(0, 0, 0)) {}

	/// <summary>
	/// Modified constructor
	/// </summary>
	/// <param name="name">Name of body</param>
	/// <param name="centre">Position of body in 3D space</param>
	/// <param name="r">Radius of body</param>
	/// <param name="m">Mass of body</param>
	/// <param name="vel">Velocity of body in 3D vector form</param>
	body(const std::string name, point3 centre, const double r, const double m, vel3 vel) : _name(name), _centre(centre), _radius(r), _mass(m), _velocity(vel) {}

	/// <summary>
	/// Destructor
	/// </summary>
	~body() {}; // Destructor

	/// <summary>
	/// Computes the accleration on a body from one other body
	/// </summary>
	/// <param name="pos">Distance between the two bodies</param>
	/// <param name="ax">Acceleration in the x direction</param>
	/// <param name="ay">Acceleration in the y direction</param>
	/// <param name="az">Acceleration in the z direction</param>
	/// <returns>The error code. See error.h for more info</returns>
	int compute_acceleration(point3 pos, double& ax, double& ay, double& az) {
		if (pos.length() == 0) return ERR_BODIES_COLLIDED; // If the distance between two bodies is 0 then they must have collided
		ax += (grav_constant * _mass) / (pow(pos.x(), 2) + pow(pos.y(), 2) + pow(pos.z(), 2)) * (-pos.x() / sqrt(pow(pos.x(), 2) + pow(pos.y(), 2) + pow(pos.z(), 2)));
		ay += (grav_constant * _mass) / (pow(pos.x(), 2) + pow(pos.y(), 2) + pow(pos.z(), 2)) * (-pos.y() / sqrt(pow(pos.x(), 2) + pow(pos.y(), 2) + pow(pos.z(), 2)));
		az += (grav_constant * _mass) / (pow(pos.x(), 2) + pow(pos.y(), 2) + pow(pos.z(), 2)) * (-pos.z() / sqrt(pow(pos.x(), 2) + pow(pos.y(), 2) + pow(pos.z(), 2)));

		if (ax != ax) return ERR_AX_NAN;
		if (ay != ay) return ERR_AY_NAN;
		if (az != az) return ERR_AZ_NAN;
		return NO_ERROR;
	}

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
	/// Computes one step using the Runge Kutta method
	/// NOTE: This method uses ONE body in the computation
	/// So usually thr star is input at the acting force
	/// </summary>
	/// <param name="acting_force">The acting force, usually the star</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_runge_kutta(body* acting_force, double dt);

	/// <summary>
	/// Computes one step using the Runge kutta method
	/// and uses all bodies in the universe
	/// </summary>
	/// <param name="universe">The universe</param>
	/// <param name="dt">The time step</param>
	/// <returns>The error code. See error.h for more info</returns>
	int step_runge_kutta(universe* universe, double dt);
	
	// Getters
	std::string name()	const { return _name;			} // Get name of body
	double	x()			const { return _centre.x();		} // Get X pos
	double	y()			const { return _centre.y();		} // Get Y pos
	double	z()			const { return _centre.z();		} // Get Z pos
	point3	pos()		const { return _centre;			} // Get position
	double	vx()		const { return _velocity.x();	} // Get X vel
	double	vy()		const { return _velocity.y();	} // Get Y vel
	double	vz()		const { return _velocity.z();	} // Get Z vel
	vel3	vel()		const { return _velocity;		} // Get velocity
	double	radius()	const { return _radius;			} // Get radius
	double	mass()		const { return _mass;			} // Get mass

	// Setters
	void x(double x)			{ _centre[0] = std::move(x);		} // Set X pos
	void y(double y)			{ _centre[1] = std::move(y);		} // Set Y pos
	void z(double z)			{ _centre[2] = std::move(z);		} // Set Z pos
	void pos(point3 position)	{ _centre = std::move(position);	} // Set Position
	void vx(double vx)			{ _velocity[0] = std::move(vx);		} // Set X vel
	void vy(double vy)			{ _velocity[1] = std::move(vy);		} // Set Y vel
	void vz(double vz)			{ _velocity[2] = std::move(vz);		} // Set Z vel
	void vel(vel3 vel)			{ _velocity = std::move(vel);		} // Set velocity
};

#endif // BODY_H
