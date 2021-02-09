#include <iostream>
#include <fstream>
#include <iomanip>

#include"body.h"
#include"universe.h"
#include "output.h"

body sun(point3(0.0, 0.0, 0.0), solar_radius, solar_mass, vel3(0.0, 0.0, 0.0));
body earth(point3(-147095000000.0, 0.0, 0.0), earth_radius, earth_mass, vel3(0.0, -30300.0, 0.0));
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

    const char* outfilename = "TT.csv";
    file_.open(outfilename);
    double time = 0.0;
    double final_time = 365 * 86400.0;

    while (time < final_time) {
        earth.step_runge_kutta(86400.0, &sun);

        printf("x: %f\n", earth.x());   // x: -147072101026.950928
        printf("y: %f\n", earth.y());   // y: -2617784148.577663 
        printf("vx: %f\n", earth.vx()); // vx: 530.054352 
        printf("vy: %f\n", earth.vy()); // vy: -30295.283069
        output(time, earth, 0, file_);
        time += 86400.0;
    }

 

    //universe u;
    //u.add(std::make_shared<body>(sun)); u.add(std::make_shared<body>(earth));
    //fn_explicit_euler_full(earth, sun, collection, outfilename);
    //u.calculate_force(earth, sun, collection);
	return 0;
}