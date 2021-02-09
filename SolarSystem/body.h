// Contains the class to create a planet or star
#ifndef BODY_H
#define BODY_H

#include "vec3.h"
#include "utility.h"

class body {
private:
	point3 _centre; // Centre of star/planet in 3D space (x, y, z)
	double _radius; // Radius of star/planet
	double _mass; // Mass of star/planet
	vel3 _velocity; // Velocity of star/planet (vx, vy, vz)

public:
	body() : _centre(point3(0, 0, 0)), _radius(0), _mass(0), _velocity(vel3(0, 0, 0)) {} // Default contructor
	body(point3 centre, const double r, const double m, vel3 vel) : _centre(centre), _radius(r), _mass(m), _velocity(vel) {} // Modified constructor

	void compute_acceleration(point3 pos, double& ax, double& ay) {
		ax = (grav_constant * _mass) / (pow(pos.x(), 2) + pow(pos.y(), 2)) * -pos.x() / sqrt(pow(pos.x(), 2) + pow(pos.y(), 2));
		ay = (grav_constant * _mass) / (pow(pos.x(), 2) + pow(pos.y(), 2)) * -pos.y() / sqrt(pow(pos.x(), 2) + pow(pos.y(), 2));
		return;
	}	

	void step_euler(double dt, body* acting_force) {
		double ax, ay;
		acting_force->compute_acceleration(this->pos(), ax, ay);
		this->x(this->vx() * dt);
		this->y(this->vy() * dt);
		this->vx(ax * dt);
		this->vy(ay * dt);
		return;
	}
	
	void step_runge_kutta(double dt, body* acting_force) {
		// Declare Runge-Kutta variables
		double k1vx, k1vy, k2vx, k2vy, k3vx, k3vy, k4vx, k4vy;

		// Calculates Runge-Kutta variables 
		double k1x = this->vx(), k1y = this->vy();
		acting_force->compute_acceleration(this->pos(), k1vx, k1vy);

		double k2x = this->vx() + (k1vx * (dt / 2.0)), k2y = this->vy() + (k1vy * (dt / 2.0));
		acting_force->compute_acceleration(this->pos() + point3(k1x * (dt / 2.0), k1y * (dt / 2.0), 0.0), k2vx, k2vy);

		double k3x = this->vx() + k2vx * (dt / 2.0), k3y = this->vy() + k2vy * (dt / 2.0);
		acting_force->compute_acceleration(this->pos() + point3(k2x * (dt / 2.0), k2y * (dt / 2.0), 0.0), k3vx, k3vy);

		double k4x = this->vx() + k3vx * dt, k4y = this->vy() + k3vy * dt;
		acting_force->compute_acceleration(this->pos() + point3(k3x * dt, k3y * dt, 0.0), k4vx, k4vy);

		// Updates position and velocity
		this->x(this->x() + (dt / 6.0) * (k1x + (2.0 * k2x) + (2.0 * k3x) + k4x));
		this->y(this->y() + (dt / 6.0) * (k1y + (2.0 * k2y) + (2.0 * k3y) + k4y));
		this->vx(this->vx() + (dt / 6.0) * (k1vx + (2.0 * k2vx) + (2.0 * k3vx) + k4vx));
		this->vy(this->vy() + (dt / 6.0) * (k1vy + (2.0 * k2vy) + (2.0 * k3vy) + k4vy));

		return;
	}

	// Getters
	double	x()		const { return _centre.x();		} // Get X pos
	double	y()		const { return _centre.y();		} // Get Y pos
	double	z()		const { return _centre.z();		} // Get Z pos
	point3	pos()	const { return _centre;			} // Get position
	double	vx()	const { return _velocity.x();	} // Get X vel
	double	vy()	const { return _velocity.y();	} // Get Y vel
	double	vz()	const { return _velocity.z();	} // Get Z vel
	vel3	vel()	const { return _velocity;		} // Get velocity
	double	radius()const { return _radius;			} // Get radius
	double	mass()	const { return _mass;			} // Get mass

	// Setters
	void x(double x) { _centre[0] = std::move(x); } // Set X pos
	void y(double y) { _centre[1] = std::move(y); } // Set Y pos
	void z(double z) { _centre[2] = std::move(z); } // Set Z pos
	void pos(point3 position) { _centre = std::move(position); } // Set Position
	void vx(double vx) { _velocity[0] = std::move(vx); } // Set X vel
	void vy(double vy) { _velocity[1] = std::move(vy); } // Set Y vel
	void vz(double vz) { _velocity[2] = std::move(vz); } // Set Z vel
	void vel(vel3 vel) { _velocity = std::move(vel); } // Set velocity

	static bool fn_explicit_euler_full(body& earth) {}
};

#endif
