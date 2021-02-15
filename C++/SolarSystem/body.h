// Contains the class to create a planet or star
#ifndef BODY_H
#define BODY_H

#include <string>

#include "vec3.h"
#include "utility.h"

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

	void compute_acceleration(point3 pos, double& ax, double& ay, double& az) {
		ax = (grav_constant * _mass) / (pow(pos.x(), 2) + pow(pos.y(), 2) + pow(pos.z(), 2)) * (-pos.x() / sqrt(pow(pos.x(), 2) + pow(pos.y(), 2) + pow(pos.z(), 2)));
		ay = (grav_constant * _mass) / (pow(pos.x(), 2) + pow(pos.y(), 2) + pow(pos.z(), 2)) * (-pos.y() / sqrt(pow(pos.x(), 2) + pow(pos.y(), 2) + pow(pos.z(), 2)));
		az = (grav_constant * _mass) / (pow(pos.x(), 2) + pow(pos.y(), 2) + pow(pos.z(), 2)) * (-pos.z() / sqrt(pow(pos.x(), 2) + pow(pos.y(), 2) + pow(pos.z(), 2)));
		return;
	}

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

	void step_euler(body* acting_force, double dt) {
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
	
	void step_runge_kutta(body* acting_force, double dt) {
		// Declare Runge-Kutta variables
		double k1vx, k1vy, k1vz, k2vx, k2vy, k2vz, k3vx, k3vy, k3vz, k4vx, k4vy, k4vz;

		// Calculates Runge-Kutta variables 
		double k1x = this->vx(), k1y = this->vy(), k1z = this->vz();
		acting_force->compute_acceleration(this->pos(), k1vx, k1vy, k1vz);

		double k2x = this->vx() + (k1vx * (dt / 2.0)), k2y = this->vy() + (k1vy * (dt / 2.0)), k2z = this->vz() + (k1vz * (dt / 2.0));
		acting_force->compute_acceleration(this->pos() + point3(k1x * (dt / 2.0), k1y * (dt / 2.0), k1z * (dt / 2.0)), k2vx, k2vy, k2vz);

		double k3x = this->vx() + k2vx * (dt / 2.0), k3y = this->vy() + k2vy * (dt / 2.0), k3z = this->vz() + (k2vz * (dt / 2.0));
		acting_force->compute_acceleration(this->pos() + point3(k2x * (dt / 2.0), k2y * (dt / 2.0), k2z * (dt / 2.0)), k3vx, k3vy, k3vz);

		double k4x = this->vx() + k3vx * dt, k4y = this->vy() + k3vy * dt, k4z = this->vz() + k3vz * dt;
		acting_force->compute_acceleration(this->pos() + point3(k3x * dt, k3y * dt, k3z * dt), k4vx, k4vy, k4vz);

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

#endif
