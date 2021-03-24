#ifndef OUTPUT_H
#define OUTPUT_H

#include <fstream>
#include <iomanip>

#include"universe.h"

// Outputs number of steps
void output_number_of_steps(int step_no, std::ofstream& ofile) {
    ofile << "\nNUM_STEPS\n" << step_no;
    return;
} // end output_number_of_steps

// Outputs information on names and masses etc...
void output_preamble(universe u, std::ostream& ofile) {
    ofile << "NUM_BODIES\n" << u.num_of_bodies << "\n";
    ofile << "\nNAMES\n";
    for (auto i = 0; i < u.num_of_bodies; i++)
        ofile << u.body_at(i)->name << "\n";

    ofile << "\nMASSES\n";
    for (auto i = 0; i < u.num_of_bodies; i++)
        ofile << u.body_at(i)->mass << "\n";

    ofile << "\nRADII\n";
    for (auto i = 0; i < u.num_of_bodies; i++)
        ofile << u.body_at(i)->radius << "\n";

    ofile << "\nTRAJECTORIES\n";
    ofile << "Step No,";
    for (auto i = 0; i < u.num_of_bodies; i++) {
        ofile << u.body_at(i)->name << "x" << ",";
        ofile << u.body_at(i)->name << "y" << ",";
        ofile << u.body_at(i)->name << "z" << ",";
        ofile << u.body_at(i)->name << "vx" << ",";
        ofile << u.body_at(i)->name << "vy" << ",";
        ofile << u.body_at(i)->name << "vz" << ",";
    } // end for
    ofile << "\n";
    return;
} // end output_preamble

// Outputs the step number and position/velocity info on all bodies in the universe
void output(double step_number, universe u, std::ofstream& ofile) {
    ofile << std::setiosflags(std::ios::showpoint | std::ios::uppercase);
    ofile << std::setprecision(8) << step_number << " ";
    for (int i = 0; i < u.num_of_bodies; i++)
    {
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->x << " ";
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->y << " ";
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->z << " ";
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->vx << " ";
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->vy << " ";
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->vz;
    }
    ofile << std::endl;
}  // end output

void output(double step_number, universe u, std::ofstream& ofile, const char* seperator) {
    ofile << std::setiosflags(std::ios::showpoint | std::ios::uppercase);
    ofile << std::setprecision(8) << step_number << seperator;
    for (int i = 0; i < u.num_of_bodies; i++)
    {
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->x << seperator;
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->y << seperator;
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->z << seperator;
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->vx << seperator;
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->vy << seperator;
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->vz << seperator;
    }
    ofile << std::endl;
}  // end output

void output_no_whitespace(double step_number, universe u, std::ofstream& ofile, const char* seperator) {
    ofile << std::setiosflags(std::ios::showpoint | std::ios::uppercase);
    ofile << std::setprecision(8) << step_number << seperator;
    for (int i = 0; i < u.num_of_bodies; i++)
    {
        ofile << std::setprecision(8) << u.body_at(i)->x << seperator;
        ofile << std::setprecision(8) << u.body_at(i)->y << seperator;
        ofile << std::setprecision(8) << u.body_at(i)->z << seperator;
        ofile << std::setprecision(8) << u.body_at(i)->vx << seperator;
        ofile << std::setprecision(8) << u.body_at(i)->vy << seperator;
        ofile << std::setprecision(8) << u.body_at(i)->vz << seperator;
    }
    ofile << std::endl;
}  // end output


void output(double step_number, body b, std::ofstream& ofile) {
    ofile << std::setiosflags(std::ios::showpoint | std::ios::uppercase);
    ofile << std::setw(15) << std::setprecision(8) << step_number << " ";
    ofile << std::setw(15) << std::setprecision(8) << b.x << " ";
    ofile << std::setw(15) << std::setprecision(8) << b.y << " ";
    ofile << std::setw(15) << std::setprecision(8) << b.z << " ";
    ofile << std::setw(15) << std::setprecision(8) << b.vx << " ";
    ofile << std::setw(15) << std::setprecision(8) << b.vy << " ";
    ofile << std::setw(15) << std::setprecision(8) << b.vz << " ";
    ofile << std::endl;
}  // end output

void output(double step_number, body b, std::ofstream& ofile, const char* seperator) {
    ofile << std::setiosflags(std::ios::showpoint | std::ios::uppercase);
    ofile << std::setw(15) << std::setprecision(8) << step_number << seperator;
    ofile << std::setw(15) << std::setprecision(8) << b.x << seperator;
    ofile << std::setw(15) << std::setprecision(8) << b.y << seperator;
    ofile << std::setw(15) << std::setprecision(8) << b.z << seperator;
    ofile << std::setw(15) << std::setprecision(8) << b.vx << seperator;
    ofile << std::setw(15) << std::setprecision(8) << b.vy << seperator;
    ofile << std::setw(15) << std::setprecision(8) << b.vz << seperator;
    ofile << std::endl;
}  // end output

#endif // OUTPUT_H