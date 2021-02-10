#include <iostream>
#include <fstream>
#include <iomanip>

#include"body.h"
#include"universe.h"
#include "output.h"

body sun(point3(0.0, 0.0, 0.0), solar_radius, solar_mass, vel3(0.0, 0.0, 0.0));
body mercury(point3(-46000000000.0, 0.0, 0.0), mercury_radius, mercury_mass, vel3(0.0, -58980.0, 0.0));
body venus(point3(-1074800000.0, 0.0, 0.0), venus_radius, venus_mass, vel3(0.0, -35260.0, 0.0));
body earth(point3(-147095000000.0, 0.0, 0.0), earth_radius, earth_mass, vel3(0.0, -30300.0, 0.0));
body mars(point3(-2066200000.0, 0.0, 0.0), mars_radius, mars_mass, vel3(0.0, -26500.0, 0.0));
body jupiter(point3(-740520000000.0, 0.0, 0.0), jupiter_radius, jupiter_mass, vel3(0.0, -13720.0, 0.0));
data_collection collection(1000, 1.0);

std::ofstream file_;

int main(int argc, char* argv[]) {  
    //  declarations of variables
    /*
    char* outfilename{};
    // Read in output file, abort if there are too few command-line arguments
    if (argc <= 1) {
        std::cout << "Bad Usage: " << argv[0] <<
            " read also output file on same line" << std::endl;
        //return -1;
    }
    else outfilename = argv[1];
    */

    const char* outfilename = "Universe_Test.csv";
    file_.open(outfilename);
    double time = 0.0;
    double final_time = 365 * 86400.0 * 5;

    universe u;
    u.add(&sun);
    u.add(&mercury);
    u.add(&venus);
    u.add(&earth);
    u.add(&mars);
    u.add(&jupiter);

    while (time < final_time) {
        mercury.step_runge_kutta(&sun, 86400.0);
        venus.step_runge_kutta(&sun, 86400.0);
        earth.step_runge_kutta(&sun, 86400.0);
        mars.step_runge_kutta(&sun, 86400.0);
        jupiter.step_runge_kutta(&sun, 86400.0);
        output(time, u, file_);
        time += 86400.0;
    } 

	return 0;
}