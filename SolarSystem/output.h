#ifndef OUTPUT_H
#define OUTPUT_H

#include <fstream>
#include <iomanip>

#include"universe.h"

void output(double time, universe u, std::ofstream& ofile)
{
    ofile << std::setiosflags(std::ios::showpoint | std::ios::uppercase);
    ofile << std::setw(15) << std::setprecision(8) << time << ",";
    for (int i = 0; i < u.length(); i++)
    {
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->x() << ",";
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->y() << ",";
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->z() << ",";
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->vx() << ",";
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->vy() << ",";
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->vz() << ",";
        ofile << ",";
        //delete b;
    }
    ofile << std::endl;
}  // end of function output

void output(double time, body b, std::ofstream& ofile)
{
    ofile << std::setiosflags(std::ios::showpoint | std::ios::uppercase);
    ofile << std::setw(15) << std::setprecision(8) << time << ",";
    ofile << std::setw(15) << std::setprecision(8) << b.x() << ",";
    ofile << std::setw(15) << std::setprecision(8) << b.y() << ",";
    ofile << std::setw(15) << std::setprecision(8) << b.z() << ",";
    ofile << std::setw(15) << std::setprecision(8) << b.vx() << ",";
    ofile << std::setw(15) << std::setprecision(8) << b.vy() << ",";
    ofile << std::setw(15) << std::setprecision(8) << b.vz() << ",";
    ofile << std::endl;
}  // end of function output

#endif