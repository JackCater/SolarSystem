// Contains the class to create a planet or star
#ifndef BODY_H
#define BODY_H

#include "vec3.h"

class body {
private:
	point3 _centre; // Centre of star/planet in 3D space (x, y, z)
	double _radius; // Radius of star/planet
	double _mass; // Mass of star/planet
	vel3 _velocity; // Velocity of star/planet (vx, vy, vz)

public:
	body() : _centre(point3(0, 0, 0)), _radius(0), _mass(0), _velocity(vel3(0,0,0)) {} // Default contructor
	body(point3 centre, const double r, const double m, vel3 vel) : _centre(centre), _radius(r), _mass(m), _velocity(vel) {} // Modified constructor

	// Getters
	double x() const { return _centre.x(); } // Get X pos
	double y() const { return _centre.y(); } // Get Y pos
	double z() const { return _centre.z(); } // Get Z pos
	point3 pos() const { return _centre; } // Get position
	double vx() const { return _velocity.x(); } // Get X vel
	double vy() const { return _velocity.y(); } // Get Y vel
	double vz() const { return _velocity.z(); } // Get Z vel
	vel3 vel() const { return _velocity; } // Get velocity
	double radius() const { return _radius; } // Get radius
	double mass() const { return _mass; } // Get mass

	// Setters
	void x(double x) { _centre[0] = std::move(x); } // Set X pos
	void z(double z) { _centre[2] = std::move(z); } // Set Z pos
	void pos(point3 position) { _centre = std::move(position); } // Set Position
	void y(double y) { _centre[1] = std::move(y); } // Set Y pos
	void vx(double vx) { _velocity[0] = std::move(vx); } // Set X vel
	void vy(double vy) { _velocity[1] = std::move(vy); } // Set Y vel
	void vz(double vz) { _velocity[2] = std::move(vz); } // Set Z vel
	void vel(vel3 vel) { _velocity = std::move(vel); } // Set velocity
};

#endif
