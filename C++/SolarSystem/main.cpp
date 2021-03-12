#include <iostream>
#include <fstream>
#include <iomanip>

#include "body.h"
#include "universe.h"
#include "output.h"

// Planets
body sun("Sun", point3(0.0, 0.0, 0.0), solar_radius, solar_mass, vel3(0.0, 0.0, 0.0));
body mercury("Mercury", point3(-46000000000.0, 0.0, 0.0), mercury_radius, mercury_mass, vel3(0.0, -58980.0, 0.0));
body venus("Venus", point3(-107480000000.0, 0.0, 0.0), venus_radius, venus_mass, vel3(0.0, -35260.0, 0.0));
body earth("Earth", point3(-147095000000.0, 0.0, 0.0), earth_radius, earth_mass, vel3(0.0, -30300.0, 0.0));
body mars("Mars", point3(-206620000000.0, 0.0, 0.0), mars_radius, mars_mass, vel3(0.0, -26500.0, 0.0));
body jupiter("Jupiter", point3(-740520000000.0, 0.0, 0.0), jupiter_radius, jupiter_mass, vel3(0.0, -13720.0, 0.0));
body saturn("Saturn", point3(-1352550000000.0, 0.0, 0.0), saturn_radius, saturn_mass, vel3(0.0, -10180.0, 0.0));
body uranus("Uranus", point3(-2741300000000.0, 0.0, 0.0), uranus_radius, uranus_mass, vel3(0.0, -7110.0, 0.0));
body neptune("Neptune", point3(-4444450000000.0, 0.0, 0.0), neptune_radius, neptune_mass, vel3(0.0, -5500.0, 0.0));
// body pluto()

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

data_collection collection(1000, 1.0);

std::ofstream file_;

universe create_solar_system(void) {
    universe u;
    u.add(&sun);
    u.add(&mercury);
    u.add(&venus);
    u.add(&earth);
    u.add(&mars);
    //u.add(&jupiter);
    //u.add(&saturn);
    //u.add(&uranus);
    //u.add(&neptune);
    return u;
}

universe create_three_body(void) {
    universe u;
    u.add(&x0);
    u.add(&x1);
    u.add(&x2);
    return u;
}

universe create_universe_earth_test(void) {
    universe u;    
    u.add(&sun);
    u.add(&earth);   
    return u;
}

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
    
    //const char* outfilename = "Universe_Test.csv";
    file_.open(outfilename);
    double time = 0.0;
    double dt = 86400.0;
    double final_time = 86400.0 * 365.0 * 10.0;
    int step_no = 0;
    double tol = 1.0;

    universe u = create_solar_system();

    file_ << "NUM_BODIES\n" << u.num_of_bodies <<"\n";
    file_ << "\nNUM_STEPS\n" << 500 << "\n";
    file_ << "\nNAMES\n";
    for (auto i = 0; i < u.num_of_bodies; i++)
        file_ << u.body_at(i)->name << "\n";    
    
    file_ << "\nMASSES\n";
    for (auto i = 0; i < u.num_of_bodies; i++)
        file_ << u.body_at(i)->mass << "\n";    
    
    file_ << "\nRADII\n";
    for (auto i = 0; i < u.num_of_bodies; i++)
        file_ << u.body_at(i)->radius << "\n";
 
    file_ << "\nTRAJECTORIES\n";
    file_ << "Step No,";
    for (auto i = 0; i < u.num_of_bodies; i++) {
        file_ << u.body_at(i)->name <<"x" << ",";
        file_ << u.body_at(i)->name <<"y" << ",";
        file_ << u.body_at(i)->name <<"z" << ",";
        file_ << u.body_at(i)->name <<"vx" << ",";
        file_ << u.body_at(i)->name <<"vy" << ",";
        file_ << u.body_at(i)->name <<"vz" << ",";
    }
    file_ << "\n";
    while (step_no < 500) {
        int retval = NO_ERROR;
        std::cerr << "\rTime remaining: " << final_time - time - dt << ' ' << "Error code: " << retval << "    " << std::flush;
        retval = u.step_rkf45(&u, tol, dt);
        if (retval != NO_ERROR) { 
            std::cerr << "\nERROR: " << retval << " See error.h for more\n";
            return retval; 
        } // end if

        output_no_whitespace(time, u, file_, ",");
        step_no++;
        time += dt;
    } // end while
    std::cerr << "\nDone.\n";

	return 0;
}