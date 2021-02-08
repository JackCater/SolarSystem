#ifndef OUTPUT_H
#define OUTPUT_H

#include <fstream>
#include <iomanip>

#include"body.h"

void output(double time, body b, double e, std::ofstream& ofile)
{
    ofile << std::setiosflags(std::ios::showpoint | std::ios::uppercase);
    ofile << std::setw(15) << std::setprecision(8) << time << ",";
    ofile << std::setw(15) << std::setprecision(8) << b.x() << ",";
    ofile << std::setw(15) << std::setprecision(8) << b.y() << ",";
    ofile << std::setw(15) << std::setprecision(8) << b.vx() << ",";
    ofile << std::setw(15) << std::setprecision(8) << b.vy() << ",";
    ofile << std::setw(15) << std::setprecision(8) << e << "," << std::endl;
}  // end of function output

#endif