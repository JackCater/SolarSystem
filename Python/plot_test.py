import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
import pandas as pd
from matplotlib import animation

colour_list = ('red', 'orange', 'blue', 'lawngreen', 'aqua', 'purple', 'fuchsia', 'lightblue', 'chocolate',
               'khaki')  # Add more colours if you want too


class plot_traj:
    def __init__(self, filename):
        # define variables
        self.names, self.masses, self.radii = [], [], []
        self.number_of_bodies, self.number_of_steps = 0, 0
        self.fig = plt.figure()
        self.ax = plt.axes()
        self.data_list, self.line_list, self.data = [], [], []

        # Open file
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
        # Unnamed: creates a column called 'Unnamed: n' where n is the number of bodies * 6 + 1
        self.df = self.df.drop(columns=['Step No', 'Unnamed: ' + str(self.number_of_bodies * 6 + 1)])

        # Create body and line object for each planet/star
        for bodies in range(len(self.names)):
            body_obj, = self.ax.plot([], [], colour_list[bodies], marker="o", lw=1)
            line_obj, = self.ax.plot([], [], colour_list[bodies])
            self.line_list.append(line_obj, )
            self.data_list.append(body_obj, )

        for _ in range(self.number_of_bodies):
            self.data.append([])  # x data
            self.data.append([])  # y data

        self.ax.set_xlim(-2E11, 2E11)
        self.ax.set_ylim(-2E11, 2E11)

    def _update(self, frame):
        self.frame = frame
        for x in range(len(self.data_list)):
            # Set sphere to be planet
            self.data_list[x].set_data(self.df.at[self.frame, self.names[x] + 'x'],
                                          self.df.at[self.frame, self.names[x] + 'y'])
            # set data for bodies tails
            self.line_list[x].set_data(self.df.loc[0:self.frame, self.names[x] + 'x'],
                                          self.df.loc[0:self.frame, self.names[x] + 'y'])

        return self.line_list + self.data_list #and self.ax,

    def animate(self):
        anim = animation.FuncAnimation(self.fig, self._update, frames=self.number_of_steps, interval=1, blit=True)
        plt.show()

if __name__ == "__main__":
    planets = plot_traj("three_test.csv")
    plot_traj.animate(planets)
