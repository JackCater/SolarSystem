// This file contains useful marcos for error handing
#ifndef ERROR_H
#define ERROR_H

// No error
#define NO_ERROR				0	// No error

// Body/universe related errors
#define ERR_NO_BODY_IN_UNIVERSE	1	// The universe contains a body of nullptr
#define ERR_NO_ACTING_FORCE		2	// The acting force is a nullptr
#define ERR_BODIES_COLLIDED		3	// The distance between two bodies is 0
									// therefore they have collided
#define ERR_UNIVERSE_NULLPTR	4	// The universe is a nullptr
#define ERR_BODY_NULLPTR		5	// The acting force/body is a nullptr

// Calculation based errors
#define ERR_X_NAN				10	// The x value return NaN
#define ERR_Y_NAN				11	// The y value return NaN
#define ERR_Z_NAN				12	// The z value return NaN
#define ERR_VX_NAN				13	// The vx value return NaN
#define ERR_VY_NAN				14	// The vy value return NaN
#define ERR_VZ_NAN				15	// The vz value return NaN
#define ERR_AX_NAN				16	// The ax value return NaN
#define ERR_AY_NAN				17	// The ay value return NaN
#define ERR_AZ_NAN				18	// The az value return NaN

#endif
