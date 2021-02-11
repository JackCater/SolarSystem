#include <iostream>
#include <fstream>
#include <iomanip>

#include"body.h"
#include"universe.h"
#include "output.h"

body sun(point3(0.0, 0.0, 0.0), solar_radius, solar_mass, vel3(0.0, 0.0, 0.0));
body mercury(point3(-46000000000.0, 0.0, 0.0), mercury_radius, mercury_mass, vel3(0.0, -58980.0, 0.0));
body venus(point3(-107480000000.0, 0.0, 0.0), venus_radius, venus_mass, vel3(0.0, -35260.0, 0.0));
body earth(point3(-147095000000.0, 0.0, 0.0), earth_radius, earth_mass, vel3(0.0, -30300.0, 0.0));
body mars(point3(-206620000000.0, 0.0, 0.0), mars_radius, mars_mass, vel3(0.0, -26500.0, 0.0));
body jupiter(point3(-740520000000.0, 0.0, 0.0), jupiter_radius, jupiter_mass, vel3(0.0, -13720.0, 0.0));
body saturn(point3(-1352550000000.0, 0.0, 0.0), saturn_radius, saturn_mass, vel3(0.0, -10180.0, 0.0));
body uranus(point3(-2741300000000.0, 0.0, 0.0), uranus_radius, uranus_mass, vel3(0.0, -7110.0, 0.0));
body neptune(point3(-4444450000000.0, 0.0, 0.0), neptune_radius, neptune_mass, vel3());
data_collection collection(1000, 1.0);

std::ofstream file_;

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
    
    // const char* outfilename = "Universe_Test3.csv";
    file_.open(outfilename);
    double time = 0.0;
    double dt = 60.0 * 60.0 * 24.0;
    double final_time = 365.0 * 60.0 * 60.0 * 24.0 * 5.0;

    universe u;
    u.add(&sun);
    u.add(&mercury);
    u.add(&venus);
    u.add(&earth);
    u.add(&mars);
    u.add(&jupiter);
    u.add(&saturn);
    u.add(&uranus);
    u.add(&neptune);

    while (time < final_time) {
        u.total_force(dt);
        output(time, u, file_);
        time += dt;
    } 

	return 0;
}