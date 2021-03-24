import matplotlib.pyplot as plt
import numpy as np
import mpl_toolkits.mplot3d.axes3d as p3
import pandas as pd
from matplotlib import animation

colour_list = ('red', 'orange', 'blue', 'lawngreen', 'aqua', 'purple', 'fuchsia', 'lightblue', 'chocolate',
               'khaki')  # Add more colours if you want too


class plot_traj:
    def __init__(self, filename, xlim=0, ylim=0, zlim=0, rotate=False, tail=True, labels=False, show_anim=True,
                 axes=True, axes_text=True, rotate_speed=5, save=False):
        # define variables
        self.names, self.masses, self.radii = [], [], []
        self.number_of_bodies, self.number_of_steps = 0, 0
        self.fig = plt.figure()
        self.ax = self.fig.gca(projection='3d')
        self.ax.view_init(elev = 10, azim = 10)
        self.data_list, self.line_list, self.data = [], [], []
        self.azim = 0
        # The keywords arguments are handled below
        self.rotate, self.tail, self.labels, self.show_anim, self.axes = rotate, tail, labels, show_anim, axes
        self.axes_text, self.rotate_speed, self.save = axes_text, rotate_speed, save

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
        self.df = pd.read_csv(self.filename, skip_blank_lines=True, skiprows=3 * self.number_of_bodies + 10)
        # Remove the two unnecessary columns (could be done in C++)
        # Unnamed: creates a column called 'Unnamed: n' where n is the number of bodies * 6 + 1
        self.df = self.df.drop(columns=['Step No', 'Unnamed: ' + str(self.number_of_bodies * 6 + 1)])

        # Set the x limit any y limits for the data frame
        min_array_x, max_array_x, min_array_y, max_array_y, min_array_z, max_array_z = [], [], [], [], [], []
        for i in range(len(self.names)):
            # Gets the X values of the bodies
            column = self.df[self.names[i] + "x"]
            # Gets the min and max values and appends them
            min_value_x = column.min()
            max_value_x = column.max()
            min_array_x.append(min_value_x)
            max_array_x.append(max_value_x)
            # Gets the Y values of the bodies
            column = self.df[self.names[i] + "y"]
            min_value_y = column.min()
            max_value_y = column.max()
            min_array_y.append(min_value_y)
            max_array_y.append(max_value_y)
            # Gets the Z values of the bodies
            column = self.df[self.names[i] + "z"]
            min_value_z = column.min()
            max_value_z = column.max()
            min_array_z.append(min_value_z)
            max_array_z.append(max_value_z)

        # Sets the x and y limits to the min and max values of the array OR the min and max value defined a kwarg
        # Which ever is lesser
        if xlim == 0:
            self.xlim = max(np.maximum(abs(min(min_array_x)), max_array_x))
        else:
            self.xlim = xlim

        if ylim == 0:
            self.ylim  = max(np.maximum(abs(min(min_array_x)), max_array_x))
        else:
            self.ylim = ylim

        if zlim == 0:
            self.zlim = max(np.maximum(abs(min(min_array_x)), max_array_x))
        else:
            self.zlim = zlim

        # X LIMITS
        if min(min_array_x) < -self.xlim and max(max_array_x) > self.xlim:
            self.ax.set_xlim(-self.xlim, self.xlim)
        elif min(min_array_x) < -self.xlim:
            self.ax.set_xlim(-self.xlim, max(max_array_x))
        elif max(max_array_x) > self.xlim:
            self.ax.set_xlim(min(min_array_x), self.xlim)
        else:
            self.ax.set_xlim(min(min_array_x), max(max_array_x))

        #Y LIMITS
        if min(min_array_y) < -self.ylim and max(max_array_y) > self.ylim:
            self.ax.set_ylim(-self.ylim, self.ylim)
        elif min(min_array_y) < -self.ylim:
            self.ax.set_ylim(-self.ylim, max(max_array_y))
        elif max(max_array_x) > self.ylim:
            self.ax.set_ylim(min(min_array_y), self.ylim)
        else:
            self.ax.set_ylim(min(min_array_y), max(max_array_y))

        # Z LIMITS
        if min(min_array_z) < -self.zlim and max(max_array_z) > self.zlim:
            self.ax.set_zlim(-self.zlim, self.zlim)
        elif min(min_array_z) < -self.zlim:
            self.ax.set_zlim(-self.zlim, max(max_array_z))
        elif max(max_array_z) > self.zlim:
            self.ax.set_zlim(min(min_array_z), self.zlim)
        else:
            self.ax.set_zlim(min(min_array_z), max(max_array_z))



        # Create body and line object for each planet/star
        for bodies in range(len(self.names)):
            body_obj, = self.ax.plot([], [], [], colour_list[bodies], marker="o", lw=1)
            # If tail keyword is true create tails of bodies
            #if self.tail:
            line_obj, = self.ax.plot([], [], [], colour_list[bodies])
            self.line_list.append(line_obj, )
            self.data_list.append(body_obj, )

        for _ in range(self.number_of_bodies):
            self.data.append([])  # x data
            self.data.append([])  # y data
            self.data.append([])  # z data

        # Set label names
        if self.labels:
            self.ax.set_xlabel('X Pos')
            self.ax.set_ylabel('Y Pos')
            self.ax.set_zlabel('Z Pos')
        # Set axes or not
        if not self.axes:
            self.ax.set_axis_off()
            plt.grid(True)

        # Set axes text or not
        if not self.axes_text:
            self.ax.get_xaxis().set_ticklabels([])
            self.ax.get_yaxis().set_ticklabels([])
            self.ax.get_zaxis().set_ticklabels([])

    def _update(self, frame):
        self.frame = frame
        for x in range(len(self.data_list)):
            # Set sphere to be planet
            self.data_list[x].set_data_3d(self.df.at[self.frame, self.names[x] + 'x'],
                                          self.df.at[self.frame, self.names[x] + 'y'],
                                          self.df.at[self.frame, self.names[x] + 'z'])
            # set data for bodies tails
            self.line_list[x].set_data_3d(self.df.loc[0:self.frame, self.names[x] + 'x'],
                                          self.df.loc[0:self.frame, self.names[x] + 'y'],
                                          self.df.loc[0:self.frame, self.names[x] + 'z'])

            # If rotate is set to true rotate the 3D plot every 5 frames
            if self.rotate:
                if self.frame % self.rotate_speed == 0:
                    self.ax.view_init(azim=self.azim)
                    self.azim += 0.5
        return self.line_list + self.data_list and self.ax,

    def animate(self, f):
        anim = animation.FuncAnimation(self.fig, self._update, frames=self.number_of_steps, interval=1/60, blit=True)
        # If the keyword argument for show animation is true, show the plot
        if self.show_anim:
            plt.show()
        if self.save:
            anim.save(f, writer='PillowWriter', fps=30)

if __name__ == "__main__":
    planets = plot_traj("Test2.csv", rotate=True, show_anim=False)
    plot_traj.animate(planets, r"C://Users/Jcater/source/repos/SolarSystem/Python/test3.gif")
