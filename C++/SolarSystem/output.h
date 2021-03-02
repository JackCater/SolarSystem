#ifndef OUTPUT_H
#define OUTPUT_H

#include <fstream>
#include <iomanip>

#include"universe.h"

void output(double step_number, universe u, std::ofstream& ofile)
{
    ofile << std::setiosflags(std::ios::showpoint | std::ios::uppercase);
    ofile << std::setprecision(8) << step_number << " ";
    for (int i = 0; i < u.num_of_bodies(); i++)
    {
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->x() << " ";
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->y() << " ";
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->z() << " ";
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->vx() << " ";
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->vy() << " ";
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->vz();
    }
    ofile << std::endl;
}  // end of function output

void output(double step_number, universe u, std::ofstream& ofile, const char* seperator)
{
    ofile << std::setiosflags(std::ios::showpoint | std::ios::uppercase);
    ofile << std::setprecision(8) << step_number << seperator;
    for (int i = 0; i < u.num_of_bodies(); i++)
    {
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->x() << seperator;
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->y() << seperator;
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->z() << seperator;
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->vx() << seperator;
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->vy() << seperator;
        ofile << std::setw(15) << std::setprecision(8) << u.body_at(i)->vz() << seperator;
    }
    ofile << std::endl;
}  // end of function output

void output_no_whitespace(double step_number, universe u, std::ofstream& ofile, const char* seperator)
{
    ofile << std::setiosflags(std::ios::showpoint | std::ios::uppercase);
    ofile << std::setprecision(8) << step_number << seperator;
    for (int i = 0; i < u.num_of_bodies(); i++)
    {
        ofile << std::setprecision(8) << u.body_at(i)->x() << seperator;
        ofile << std::setprecision(8) << u.body_at(i)->y() << seperator;
        ofile << std::setprecision(8) << u.body_at(i)->z() << seperator;
        ofile << std::setprecision(8) << u.body_at(i)->vx() << seperator;
        ofile << std::setprecision(8) << u.body_at(i)->vy() << seperator;
        ofile << std::setprecision(8) << u.body_at(i)->vz() << seperator;
    }
    ofile << std::endl;
}  // end of function output


void output(double step_number, body b, std::ofstream& ofile)
{
    ofile << std::setiosflags(std::ios::showpoint | std::ios::uppercase);
    ofile << std::setw(15) << std::setprecision(8) << step_number << " ";
    ofile << std::setw(15) << std::setprecision(8) << b.x() << " ";
    ofile << std::setw(15) << std::setprecision(8) << b.y() << " ";
    ofile << std::setw(15) << std::setprecision(8) << b.z() << " ";
    ofile << std::setw(15) << std::setprecision(8) << b.vx() << " ";
    ofile << std::setw(15) << std::setprecision(8) << b.vy() << " ";
    ofile << std::setw(15) << std::setprecision(8) << b.vz() << " ";
    ofile << std::endl;
}  // end of function output

void output(double step_number, body b, std::ofstream& ofile, const char* seperator)
{
    ofile << std::setiosflags(std::ios::showpoint | std::ios::uppercase);
    ofile << std::setw(15) << std::setprecision(8) << step_number << seperator;
    ofile << std::setw(15) << std::setprecision(8) << b.x() << seperator;
    ofile << std::setw(15) << std::setprecision(8) << b.y() << seperator;
    ofile << std::setw(15) << std::setprecision(8) << b.z() << seperator;
    ofile << std::setw(15) << std::setprecision(8) << b.vx() << seperator;
    ofile << std::setw(15) << std::setprecision(8) << b.vy() << seperator;
    ofile << std::setw(15) << std::setprecision(8) << b.vz() << seperator;
    ofile << std::endl;
}  // end of function output

#endif // OUTPUT_H