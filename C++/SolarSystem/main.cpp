#include <iostream>
#include <fstream>
#include <iomanip>

#include "body.h"
#include "output.h"
#include "universe.h"
#include "create_universe.h"

// Three body problem solution
body x0("Body1", point3(-0.970, 0.243, 0.0), 0.1, 1, vel3(-0.466, -0.433, 0.0));
body x1("Body2", point3(0.970, -0.243, 0.0), 0.1, 1, vel3(-0.466, -0.433, 0.0));
body x2("Body3", point3(0.0, 0.0, 0.0), 0.1, 1, vel3(2.0*0.466, 2.0*0.433, 0.0));

// Test
body v0("Body1", point3(0.0, 0.0, 0.0), 0.05, 0.25, vel3(0.0, 0.0, 0.0));
body v1("Body2", point3(2.0, 2.0, 2.0), 0.05, 0.25, vel3(0.0, 0.0, 0.0));
body v2("Body3", point3(5.0, 5.0, 5.0), 0.1, 0.25, vel3(0.0, 0.1, 0.0));
body v3("Body4", point3(3.0, 3.0, 3.0), 0.05, 0.25, vel3(0.0, 0.0, 0.0));
body v4("Body5", point3(-4.0, 2.0, 0.0), 0.1, 0.25, vel3(-0.1, 0.5, 0.0));
body v5("Body6", point3(6.0, 10.0, 0.0), 0.1, 0.25, vel3(0.2, -0.5, 0.0));
body v6("Body7", point3(-2.0, 7.0, 3.0), 0.1, 0.25, vel3(0.0, 0.0, 0.0));

std::ofstream file_;

universe create_three_body(void) {
    universe u;
    u.add(&x0);
    u.add(&x1);
    u.add(&x2);
    return u;
}

int main(int argc, char* argv[]) {         
    char* outfilename{};
    // Read in output file, abort if there are too few command-line arguments    
    if (argc <= 1) {
        std::cout << "Bad Usage: " << argv[0] <<
            " no argument for filename" << std::endl;
        return -1;
    }
    else outfilename = argv[1];    
    //const char* outfilename = "Universe_Test.csv";
    file_.open(outfilename);

    data_collection data(20000, 86400.0 * 365.0, 86400.0);
    double time = 0.0;
    double dt = 86400.0 / 10.0;
    double final_time = 86400.0 * 366.0;
    int step_number = 0, written_steps = 0;
    int number_of_steps = 1000000;
    double tol = 10000;

    universe u = create_solar_system();
    output_preamble(u, file_);

    while ((time < final_time) && (step_number <= number_of_steps)) {
        int retval = NO_ERROR;
        std::cerr << "\rTime remaining: " << final_time - time- dt << ' ' << "Step no: " << step_number << "    " << std::flush;
        retval = u.step_euler(dt);
        if (retval != NO_ERROR) { 
            std::cerr << "\nERROR: " << retval << " See error.h for more\n";
            return retval; 
        } // end if

        if (step_number % 10 == 0) {
            output_no_whitespace(time / 86400.0, u, file_, ",");
            written_steps++;
        }
        step_number++;
        time += dt;
    } // end while
    std::cerr << "\nDone.\n";

    output_number_of_steps(written_steps, file_);

	return 0;
}