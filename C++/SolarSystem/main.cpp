#include <iostream>
#include <fstream>
#include <iomanip>

#include "body.h"
#include "output.h"
#include "universe.h"
#include "create_universe.h"

std::ofstream file_;

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

    double time = 0.0;
    double dt = 0.001;
    double final_time = 10;
    unsigned int step_number = 0, written_steps = 0;
    unsigned int number_of_steps = 1000000;
    double tol = 0.00005;

    universe u = create_three_body();
    output_preamble(u, file_);

    while ((time < final_time) && (step_number <= number_of_steps)) {
        int retval = NO_ERROR;
        std::cerr << "\rTime remaining: " << final_time - time- dt << ' ' << "Step no: " << step_number << "           " << std::flush;
        retval = u.step_rk4(dt);
        if (retval != NO_ERROR) { 
            std::cerr << "\nERROR: " << retval << " See error.h for more\n";
            return retval; 
        } // end if

        if (step_number % 1 == 0) {
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