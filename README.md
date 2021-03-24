# SolarSystem

This repository simulates Planetary Motion using Newton's Laws of gravity.
In the C++ folder is the code to compute the simulation whereas the Python folder is where the code to animate the trajectories is.

There are many methods implemented in the C++ Project. These are defined in body.h:
* Euler Metod
* Runge Kutta 4th order
* Runge Kutta Fehlberg 4th order
* Runge Kutta Fehlberg 5th order
* Runge Kutta Fehlberg 5th order with adaptive time step

Within the project there are different methods; one which computes the force felt on the planets in the 'Universe' by one acting force, typically the sun, and once which computes the force felt on the planets in the 'Universe' by all other planets in the 'Universe'.

Some examples are seen below, which highlights the importance of a good numerical method and a suitable step size:
RK4 method with 1/2 Earth day step size.


![rk4_half_day_step](https://user-images.githubusercontent.com/76100438/112312856-2b5aed00-8c9f-11eb-96b0-61968aaff2fc.gif)
