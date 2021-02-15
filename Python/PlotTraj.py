from matplotlib import pyplot as plt
from matplotlib import animation
import pandas as pd

# Define global variables
# Open DataFile
df = pd.read_csv("test.csv", skip_blank_lines=True, skiprows=40)
number_of_bodies, number_of_steps = 0, 0
names, masses, radii = [], [], []

sun_xdata, sun_ydata = [], []
mercury_xdata, mercury_ydata = [], []
venus_xdata, venus_ydata = [], []

# First set up the figure, the axis, and the plot element we want to animate
fig = plt.figure()
ax = plt.axes()
sun, = plt.plot(df['Sunx'].tolist(), df['Suny'].tolist())
mercury, = plt.plot(df['Mercuryx'].tolist(), df['Mercuryy'].tolist())
venus, = plt.plot(df['Venusx'].tolist(), df['Venusy'].tolist())


class PlotTraj:
    def __init__(self, filename):
        self.filename = filename
        global number_of_bodies, number_of_steps, names, masses, radii
        f = open(self.filename, 'r')

        for x in f:
            if x.startswith('NUM_BODIES'):
                number_of_bodies = int(f.readline())
            if x.startswith('NUM_STEPS'):
                number_of_steps = int(f.readline())
            if x.startswith('NAMES'):
                i = 0
                while i < number_of_bodies:
                    names.append(f.readline().strip('\n'))
                    i += 1

            if x.startswith('MASSES'):
                i = 0
                while i < number_of_bodies:
                    masses.append(float(f.readline()))
                    i += 1

            if x.startswith('RADII'):
                i = 0
                while i < number_of_bodies:
                    radii.append(float(f.readline()))
                    i += 1
        f.close()

    def _update(self, frame):
        self.frame = frame
        sun_xdata.append(df.at[self.frame, 'Sunx'])
        sun_ydata.append(df.at[self.frame, 'Sunx'])
        mercury_xdata.append(df.at[self.frame, 'Mercuryx'])
        mercury_ydata.append(df.at[self.frame, 'Mercuryy'])
        venus_xdata.append(df.at[self.frame, 'Venusx'])
        venus_ydata.append(df.at[self.frame, 'Venusy'])

        sun.set_data(sun_xdata, sun_ydata)
        mercury.set_data(mercury_xdata, mercury_ydata)
        venus.set_data(venus_xdata, venus_ydata)
        return sun, mercury, venus,

    def animate(self):
        # call the animator, animate every 300 ms
        # set number of frames to the length of your list of dataframes
        anim = animation.FuncAnimation(fig, self._update, frames=len(df.index), interval=100, blit=True)
        plt.show()


if __name__ == "__main__":
    a = PlotTraj("test.csv")
    a.animate()
