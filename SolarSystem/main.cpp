#include <iostream>
#include <fstream>
#include <iomanip>

#include "planetary_motion.h"

body sun(point3(0, 0, 0), solar_radius, solar_mass, vel3(0, 0, 0));
body earth(point3(1, 0, 0), earth_radius, earth_mass, vec3(0, (29.29E3*orbital_period)/aphelion_distance, 0));
data_collection collection(1000, 1.0);


int main(int argc, char* argv[]) {  
    //  declarations of variables
   char* outfilename{};
    // Read in output file, abort if there are too few command-line arguments
    if (argc <= 1) {
        std::cout << "Bad Usage: " << argv[0] <<
            " read also output file on same line" << std::endl;
        return -1;
    }
    else outfilename = argv[1];

    fn_runge_kutta4_full(earth, sun, collection, outfilename);
	return 0;
}