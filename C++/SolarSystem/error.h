// This file contains useful marcos for error handing
#ifndef ERROR_H
#define ERROR_H

/// <summary>
/// No error enum
/// </summary>
enum NO_ERROR : int {
	NO_ERROR = 0x00, // No error
};

/// <summary>
/// Body/universe related errors
/// </summary>
enum BODY_ERRORS : short {
	ERR_NO_BODY_IN_UNIVERSE = 0x01,	// The universe contains a body of nullptr
	ERR_NO_ACTING_FORCE = 0x02,		// The acting force is a nullptr
	ERR_BODIES_COLLIDED = 0x03,		// The distance between two bodies is 0
									// therefore they have collided
	ERR_UNIVERSE_NULLPTR = 0x04,	// The universe is a nullptr
	ERR_BODY_NULLPTR = 0x05,		// The acting force/body is a nullptr
};

/// <summary>
/// Calculation based errors
/// </summary>
enum CALCULATION_ERRORS : short {
	ERR_X_NAN = 0x01,	// The x value returned NaN
	ERR_Y_NAN = 0x02,	// The y value returned NaN
	ERR_Z_NAN = 0x03,	// The z value returned NaN
	ERR_VX_NAN = 0x04,	// The vx value returned NaN
	ERR_VY_NAN = 0x05,	// The vy value returned NaN
	ERR_VZ_NAN = 0x06,	// The vz value returned NaN
	ERR_AX_NAN = 0x07,	// The ax value returned NaN
	ERR_AY_NAN = 0x08,	// The ay value returned NaN
	ERR_AZ_NAN = 0x09,	// The az value returned NaN
	ERR_OUTSIDE_TOL = 0x10, // The value is outside of the tolerance
};


#endif
