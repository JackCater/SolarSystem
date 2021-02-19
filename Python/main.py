import matplotlib.pyplot as plt
from matplotlib import animation
import pandas as pd

fig = plt.figure()
ax = plt.axes()


class PlotTraj:
    def __init__(self, filename):
        # define global variables
        global fig, ax
        self.names, self.masses, self.radii = [], [], []
        self.number_of_bodies, self.number_of_steps = 0, 0
        self.data_list = []
        self.data = []

        self.filename = filename
        # Open and unpack, names, masses, radii and number of bodies and steps info
        f = open(self.filename, 'r')

        # For every line in the file, if the line contains the header read the next line
        # and assign the variable
        for x in f:
            if x.startswith('NUM_BODIES'):
                self.number_of_bodies = int(f.readline())
            if x.startswith('NUM_STEPS'):
                self.number_of_steps = int(f.readline())
            if x.startswith('NAMES'):
                i = 0
                while i < self.number_of_bodies:
                    # To separate names on a new line they contain \n which needs to be stripped
                    self.names.append(f.readline().strip('\n'))
                    i += 1

            if x.startswith('MASSES'):
                i = 0
                while i < self.number_of_bodies:
                    self.masses.append(float(f.readline()))
                    i += 1

            if x.startswith('RADII'):
                i = 0
                while i < self.number_of_bodies:
                    self.radii.append(float(f.readline()))
                    i += 1
        # Close file
        f.close()

        # Open dataframe to the trajectories information
        self.df = pd.read_csv(self.filename, skip_blank_lines=True, skiprows=3 * self.number_of_bodies + 13)
        # Remove the two unnecessary columns (could be done in C++)
        self.df = self.df.drop(columns=['Step No', 'Unnamed: 55'])

        for bodies in range(len(self.names)):
            body_obj, = ax.plot(self.df[self.names[bodies] + 'x'].tolist(), self.df[self.names[bodies] + 'y'].tolist(), lw=1)
            self.data_list.append(body_obj,)

        for x in range(self.number_of_bodies):
            self.data.append([])  # x data
            self.data.append([])  # y data

    def _update(self, frame):
        self.frame = frame
        for x in range(len(self.names)):
            self.data[2 * x].append(self.df.at[self.frame, self.names[x] + 'x'])
            self.data[2 * x + 1].append(self.df.at[self.frame, self.names[x] + 'y'])

        for x in range(len(self.data_list)):
            self.data_list[x].set_data(self.data[x*2], self.data[x*2+1])
        return self.data_list

    def animate(self):
        anim = animation.FuncAnimation(fig, self._update, frames=self.number_of_steps, interval=0.05, blit=True)
        plt.show()


if __name__ == "__main__":
    planets = PlotTraj("ILoveHannahCronau.csv")
    PlotTraj.animate(planets)
