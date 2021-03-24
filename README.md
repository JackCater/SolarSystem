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
**For visual ease these methods are only showing the planets in the inner Solar System.*

***RK4 method with 1/2 Earth day step size.***
Whilst the RK4 method is good, the step size is far too large

![rk4_half_day_step](https://user-images.githubusercontent.com/76100438/112312856-2b5aed00-8c9f-11eb-96b0-61968aaff2fc.gif)


***RK4 method with 1/10 Earth day step size.***

We see lowering the step size produces a more realistic approximation

![rk4_10_day_step_3](https://user-images.githubusercontent.com/76100438/112336099-ada1dc00-8cb4-11eb-89a0-d93bfe568c58.gif)

***Euler method with 1/10 Earth day step size.***

However the same step size using the Euler method (a lower order numerical method) produces less realistic approximations

![euler_10_day_step](https://user-images.githubusercontent.com/76100438/112336122-b5618080-8cb4-11eb-8a77-b43a63399520.gif)

