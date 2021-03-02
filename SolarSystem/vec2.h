// File containing some useful 2D vector identities
#ifndef VEC2_H
#define VEC2_H

#include <iostream>

class vec2 {
private:
	double e[2];	// Array containing planets/stars 2D co-ordinates

public:
	vec2() : e{ 0,0 } {}; // Default constructor
	vec2(double e0, double e1) : e{ e0,e1 } {} // Modified contructor

	// Getters
	double x() const { return e[0]; } // GetX
	double y() const { return e[1]; } // GetY

	vec2 operator-() const { return vec2(-e[0], -e[1]); } // Inversion
	double operator[](int i) const { return e[i]; } // Get value of i co-odrinate
	double& operator[](int i) { return e[i]; } // Get value of i co-ordinate

	vec2& operator+=(const vec2& v) { // Adds v to the vector
		e[0] += v.e[0];
		e[1] += v.e[1];
		return *this;
	} // end operator+=

	vec2& operator*=(const double t) { // Multiples the vector by t
		e[0] *= t;
		e[1] *= t;
		return *this;
	} // end operator *=

	vec2& operator/=(const double t) { return *this *= 1.0 / t; } // Divides the vector by t

	double length() const { return std::sqrt(length_squared()); } // Gets the vectors magnitude

	double length_squared()const { return e[0] * e[0] + e[1] * e[1]; } // Returns the vectors magnitude squared
};

// Type aliases
using point2 = vec2; // Position vector
using vel2 = vec2; // Velocity vector

// vec2 Utility Functions
inline std::ostream& operator<<(std::ostream& out, const vec2& v) { return out << v.x() << ' ' << v.y(); }
inline vec2 operator+(const vec2& u, const vec2& v) { return vec2(u.x() + v.x(), u.y() + v.y()); }
inline vec2 operator-(const vec2& u, const vec2& v) { return vec2(u.x() - v.x(), u.y() - v.y()); }
inline vec2 operator*(const vec2& u, const vec2& v) { return vec2(u.x() * v.x(), u.y() * v.y()); }
inline vec2 operator*(double t, const vec2& v) { return vec2(t * v.x(), t * v.y()); }
inline vec2 operator*(const vec2& v, double t) { return t * v; }
inline vec2 operator/(vec2 v, double t) { return (1 / t) * v; }

inline double dot(const vec2& u, const vec2& v) { // Vector dot product
	return	u.x() * v.x()
		+ u.y() * v.y();
} // end dot

inline vec2 cross_vector(const vec2& u, const vec2& v) { // Vector cross product
	return vec2(u.x() * v.y(), v.x() * u.y());
} // end cross_vector

inline double cross(const vec2& u, const vec2& v) {
	auto c = cross_vector(u, v);
	return c.x() - c.y();
} // end cross

inline vec2 unit_vector(vec2 v) { return v / v.length(); } // Unit vector

inline vec2 unit_vector_two_vectors(vec2 v, vec2 u) { return (v - u) / abs(v.length() - u.length()); } // Unit vector between two vectors

inline 	double distance(const point2& u, const point2& v) { // Absolute distance between two vectors
	return sqrt(
		((u.x() - v.x()) * (u.x() - v.x())) +
		((u.y() - v.y()) * (u.y() - v.y())));
} // end distance

inline vec2 distance_vector(const point2& u, const point2& v) { // Distance between each axis in vector
	return vec2(u.x() - v.x(),
		u.y() - v.y());
} // end distnace vector

#endif // VEC2_H