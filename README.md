# SolarSystem

This repository simulates Planetary Motion using Newton's Laws of gravity.
In the C++ folder is the code to compute the simulation whereas the Python folder is where the code to animate the trajectories is.

All information is gathered from NASA.gov

There are many methods implemented in the C++ Project. These are defined in body.h:
* Euler Metod
* Runge Kutta 4th order
* Runge Kutta Fehlberg 4th order
* Runge Kutta Fehlberg 5th order
* Runge Kutta Fehlberg 5th order with adaptive time step

Within the project there are different methods; one which computes the force felt on the planets in the 'Universe' by one acting force, typically the sun, and once which computes the force felt on the planets in the 'Universe' by all other planets in the 'Universe'.

Some examples are seen below, which highlights the importance of a good numerical method and a suitable step size:

**For visual ease these methods are only showing the planets in the inner Solar System.**


# ***RK4 method with 1/2 Earth day step size.***

Whilst the RK4 method is good, the step size is far too large

![rk4_half_day_step](https://user-images.githubusercontent.com/76100438/112312856-2b5aed00-8c9f-11eb-96b0-61968aaff2fc.gif)


# ***RK4 method with 1/10 Earth day step size.***

We see lowering the step size produces a more realistic approximation, although a smaller time step will be needed for higher precision

![rk4_10_day_step_3](https://user-images.githubusercontent.com/76100438/112336099-ada1dc00-8cb4-11eb-89a0-d93bfe568c58.gif)


# ***Euler method with 1/10 Earth day step size.***

However the same step size using the Euler method (a lower order numerical method) produces less realistic approximations

![euler_skip_days](https://user-images.githubusercontent.com/76100438/112338559-cc08d700-8cb6-11eb-8cba-ce5640c236e9.gif)



In the following examples we use the Runge Kutta Fehlberg 5th order with adaptive time step. With these examples, the time step is dependant on the calculation error.
This method computes the variables for the 5th order method, but calculates the positions and velocities for a 4th and 5th order method, the difference in these values is the error. If this error is within the tolerance the steps can be computed, if not the step is ignored and the time step is halved. If the time step is well within the error then the time step is doubled. This method utilises computation time. Please note for the ease of viewing the same number of frames are plotted in the animation but the number of steps that were computed are different.


# ***Adpative time step with x as the tolerance***

![rkf45_40000_tol](https://user-images.githubusercontent.com/76100438/112339803-e98a7080-8cb7-11eb-9031-cb7db040a7db.gif)


# ***Adaptive time step with x/4 as the tolerance***

As we can see reducing the tolerance by a factor of 4 makes almost no difference to the output but increases computation time by a factor of 4, therefore finding the 'sweet spot' is needed to maximise computation time.

![rkf45_10000_tol](https://user-images.githubusercontent.com/76100438/112339877-f6a75f80-8cb7-11eb-9b32-a7ab1953f48c.gif)


# ***5 years of the adaptive time step***

For good measure, here's 5 years with the adaptive time step. (Notice no Precession of Mercury, this is because the calculations are based on Newton's theory, not General Relativity).

![rkf45_5_years_3](https://user-images.githubusercontent.com/76100438/112344708-47b95280-8cbc-11eb-9024-9661b2981fc8.gif)

# ***SPED UP***

![rkf45_5_years_4](https://user-images.githubusercontent.com/76100438/112346136-91ef0380-8cbd-11eb-8be6-96eefe00978d.gif)



