from matplotlib import pyplot as plt
from matplotlib import animation
import pandas as pd
import numpy as np

sun_xdata, sun_ydata = [], []
mercury_xdata, mercury_ydata = [], []
venus_xdata, venus_ydata = [], []
earth_xdata, earth_ydata = [], []
mars_xdata, mars_ydata = [], []
jupiter_xdata, jupiter_ydata = [], []
saturn_xdata, saturn_ydata = [], []
uranus_xdata, uranus_ydata = [], []
neptune_xdata, neptune_ydata = [], []

df = pd.read_csv("final_test.csv", skip_blank_lines=True, skiprows=40)

# First set up the figure, the axis, and the plot element we want to animate
fig = plt.figure()
ax = plt.axes()
sun, = plt.plot(df['Sunx'].tolist(), df['Suny'].tolist())
mercury, = plt.plot(df['Mercuryx'].tolist(), df['Mercuryy'].tolist(), lw=1)
venus, = plt.plot(df['Venusx'].tolist(), df['Venusy'].tolist(), lw=1)
earth, = plt.plot(df['Earthx'].tolist(), df['Earthy'].tolist(), lw=1)
mars, = plt.plot(df['Marsx'].tolist(), df['Marsy'].tolist(), lw=1)
jupiter, = plt.plot(df['Jupiterx'].tolist(), df['Jupitery'].tolist(), lw=1)
saturn, = plt.plot(df['Saturnx'].tolist(), df['Saturny'].tolist(), lw=1)
uranus, = plt.plot(df['Uranusx'].tolist(), df['Uranusy'].tolist(), lw=1)
neptune, = plt.plot(df['Neptunex'].tolist(), df['Neptuney'].tolist(), lw=1)


# initialization function: plot the background of each frame
def init():
    sun.set_data([], [])
    mercury.set_data([], [])
    venus.set_data([], [])
    earth.set_data([], [])
    mars.set_data([], [])
    jupiter.set_data([], [])
    saturn.set_data([], [])
    uranus.set_data([], [])
    neptune.set_data([], [])
    return sun, mercury,  venus, earth, mars, jupiter, saturn, uranus, neptune,


# animation function of dataframes' list
def animate(i):
    sun_xdata.append(df.at[i, 'Sunx'])
    sun_ydata.append(df.at[i, 'Sunx'])
    mercury_xdata.append(df.at[i, 'Mercuryx'])
    mercury_ydata.append(df.at[i, 'Mercuryy'])
    venus_xdata.append(df.at[i, 'Venusx'])
    venus_ydata.append(df.at[i, 'Venusy'])
    earth_xdata.append(df.at[i, 'Earthx'])
    earth_ydata.append(df.at[i, 'Earthy'])
    mars_xdata.append(df.at[i, 'Marsx'])
    mars_ydata.append(df.at[i, 'Marsy'])
    jupiter_xdata.append(df.at[i, 'Jupiterx'])
    jupiter_ydata.append(df.at[i, 'Jupitery'])
    saturn_xdata.append(df.at[i, 'Saturnx'])
    saturn_ydata.append(df.at[i, 'Saturny'])
    uranus_xdata.append(df.at[i, 'Uranusx'])
    uranus_ydata.append(df.at[i, 'Uranusy'])
    neptune_xdata.append(df.at[i, 'Neptunex'])
    neptune_ydata.append(df.at[i, 'Neptuney'])

    sun.set_data(sun_xdata, sun_ydata)
    mercury.set_data(mercury_xdata, mercury_ydata)
    venus.set_data(venus_xdata, venus_ydata)
    earth.set_data(earth_xdata, earth_ydata)
    mars.set_data(mars_xdata, mars_ydata)
    jupiter.set_data(jupiter_xdata, jupiter_ydata)
    saturn.set_data(saturn_xdata, saturn_ydata)
    uranus.set_data(uranus_xdata, uranus_ydata)
    neptune.set_data(neptune_xdata, neptune_ydata)
    return sun, mercury,  venus, earth, mars, jupiter, saturn, uranus, neptune,


# call the animator, animate every 300 ms
# set number of frames to the length of your list of dataframes
anim = animation.FuncAnimation(fig, animate, frames=len(df.index), interval=0.1, blit=True)

plt.show()
