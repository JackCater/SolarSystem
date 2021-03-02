// File containing some useful 3D vector identities
#ifndef VEC3_H
#define VEC3_H

#include <iostream>

class vec3 {
private:
	double e[3];	// Array containing planets/stars 3D co-ordinates

public:
	vec3() : e{ 0,0,0 } {}; // Default constructor
	vec3(double e0, double e1, double e2) : e{ e0,e1,e2 } {} // Modified contructor

	// Getters
	double x() const { return e[0]; } // GetX
	double y() const { return e[1]; } // GetY
	double z() const { return e[2]; } // GetZ

	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); } // Inversion
	double operator[](int i) const { return e[i]; } // Get value of i co-odrinate
	double& operator[](int i) { return e[i]; } // Get value of i co-ordinate

	vec3& operator+=(const vec3& v) { // Adds v to the vector
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	} // end operator+=

	vec3& operator*=(const double t) { // Multiples the vector by t
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	} // end operator *=

	vec3& operator/=(const double t) { return *this *= 1.0 / t; } // Divides the vector by t

	double length() const { return std::sqrt(length_squared()); } // Gets the vectors magnitude

	double length_squared()const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; } // Returns the vectors magnitude squared
};

// Type aliases
using point3 = vec3; // Position vector
using vel3 = vec3; // Velocity vector

// vec3 Utility Functions
inline std::ostream& operator<<(std::ostream& out, const vec3& v) { return out << v.x() << ' ' << v.y() << ' ' << v.z(); }
inline vec3 operator+(const vec3& u, const vec3& v) { return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z()); }
inline vec3 operator-(const vec3& u, const vec3& v) { return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z()); }
inline vec3 operator*(const vec3& u, const vec3& v) { return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z()); }
inline vec3 operator*(double t, const vec3& v) { return vec3(t * v.x(), t * v.y(), t * v.z()); }
inline vec3 operator*(const vec3& v, double t) { return t * v; }
inline vec3 operator/(vec3 v, double t) { return (1 / t) * v; }

inline double dot(const vec3& u, const vec3& v) { // Vector dot product
	return	u.x() * v.x()
		+ u.y() * v.y()
		+ u.z() * v.z();
} // end dot

inline vec3 cross_vector(const vec3& u, const vec3& v) { // Vector cross product
	return vec3(u.y() * v.z() - u.z() * v.y(),
		u.z() * v.x() - u.x() * v.z(),
		u.x() * v.y() - u.y() * v.x());
} // end cross_vector

inline double cross(const vec3& u, const vec3& v) {
	vec3 c = cross_vector(u, v);
	return c.x() - c.y() + c.z();
} // end cross

inline vec3 unit_vector(vec3 v) { return v / v.length(); } // Unit vector

inline vec3 unit_vector_two_vectors(vec3 v, vec3 u) { return (v - u) / abs(v.length() - u.length()); } // Unit vector between two vectors

inline 	double distance(const point3& u, const point3& v) { // Absolute distance between two vectors
	return sqrt(
		((u.x() - v.x()) * (u.x() - v.x())) +
		((u.y() - v.y()) * (u.y() - v.y())) +
		((u.z() - v.z()) * (u.z() - v.z())));
} // end distance

inline vec3 distance_vector(const point3& u, const point3& v) { // Distance between each axis in vector
	return vec3(u.x() - v.x(),
		u.y() - v.y(),
		u.z() - v.z());
} // end distance_vector

#endif // VEC3_H