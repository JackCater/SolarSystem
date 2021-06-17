# SolarSystem

![3d_plot_all](https://user-images.githubusercontent.com/76100438/122409262-e92e0880-cf7a-11eb-90f6-ef2d11eafd0e.gif)


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

The Python folder contains two files, one for plotting 2D and one for plotting 3D, they both contain keyword arguments which can be used to control the rotation speed (in 3D) and the number of frames to save, amongst other arguments.

Some examples are seen below, which highlights the importance of a good numerical method and a suitable step size:

**For visual ease these methods are only showing the planets in the inner Solar System.**


# ***RK4 method with 1/2 Earth day step size.***

Whilst the RK4 method is good, the step size is far too large

![rkf4_half_step_black](https://user-images.githubusercontent.com/76100438/122409336-f814bb00-cf7a-11eb-91e4-2fe9572d84ac.gif)


# ***RK4 method with 1/10 Earth day step size.***

We see lowering the step size produces a more realistic approximation, although a smaller time step will be needed for higher precision

![rkf4_10_step_black](https://user-images.githubusercontent.com/76100438/122409350-fb0fab80-cf7a-11eb-8be7-8d0f3627efe3.gif)


# ***Euler method with 1/10 Earth day step size.***

However the same step size using the Euler method (a lower order numerical method) produces less realistic approximations

![euler_10_step_back](https://user-images.githubusercontent.com/76100438/122409363-fd720580-cf7a-11eb-92c2-bcd430fe2276.gif)


# ***Adpative time step with x as the tolerance***

In the following examples we use the Runge Kutta Fehlberg 5th order with adaptive time step. With these examples, the time step is dependant on the calculation error.
This method computes the variables for the 5th order method, but calculates the positions and velocities for a 4th and 5th order method, the difference in these values is the error. If this error is within a given tolerance, in this case an arbritary value x, the steps can be computed, if not the step is ignored and the time step is halved. If the time step is well within the error then the time step is doubled. This method utilises computation time. Please note for the ease of viewing the same number of frames are plotted in the animation but the number of steps that were computed are different.

![rkf45_x_step_black](https://user-images.githubusercontent.com/76100438/122409426-09f65e00-cf7b-11eb-940a-23be2ee9e4ce.gif)


# ***Adaptive time step with x/4 as the tolerance***

As we can see reducing the tolerance by a factor of 4 makes almost no difference to the output but increases computation time by a factor of 4, therefore finding the 'sweet spot' is needed to maximise computation time.

![rkf45_4x_step_black](https://user-images.githubusercontent.com/76100438/122409445-0e227b80-cf7b-11eb-8938-67d034fb1e44.gif)


# ***5 years of the adaptive time step***

For good measure, here's 5 years with the adaptive time step. (Notice no Precession of Mercury, this is because the calculations are based on Newton's theory, not General Relativity).

![rkf45_4x_step_5years_black](https://user-images.githubusercontent.com/76100438/122409470-14185c80-cf7b-11eb-8b8d-9834ea2a2d60.gif)


# ***SPED UP***

![rkf45_4x_step_5years_sped_black](https://user-images.githubusercontent.com/76100438/122409534-1e3a5b00-cf7b-11eb-8a9f-6142b0bb9ee0.gif)


# ***The Whole Solar System***

Here's the whole solar system with a very small tolerance on the error. The tolerance is small enough not to effect the outer planets but is large enough to effect the inner planets over the course of 160 or so years.


![rkf45_whole_ss_black](https://user-images.githubusercontent.com/76100438/122414429-0ebd1100-cf7f-11eb-8e87-234b0224eed6.gif)
