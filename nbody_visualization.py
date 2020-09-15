import numpy as np
import os
import sys
import matplotlib.pyplot as plt
import matplotlib.animation as animation

from matplotlib.animation import FuncAnimation

#Load binary file from absolute path
file = np.fromfile("/Users/StephenSigman/Desktop/CP341/output.bin",dtype=float,count=-1,offset=0)
np.set_printoptions(threshold=sys.maxsize)
#print(file)
print(file.shape)
#print(file[0],file[1])
shape = int(file.shape[0]/7)

file = np.reshape(file,(shape,7))
#print(file.shape)

#display first scatter plot with the 100 bodies at time 0
first_x = file[:99,0]
first_y = file[:99,1]

x_vals = file[:,0]
y_vals = file[:,1]

# x_vals2 = file[200:299,0]
# y_vals2 = file[200:299,1]
# print(x_vals2,y_vals2)

#Create figure for animation
fig = plt.figure()
#plot, = plt.plot(first_x,first_y,'ro')

#Build scatter plot
plot = plt.scatter(first_x,first_y,file[:99,2],edgecolors="k")
ax = plt.gca()
#Aesthetics - Scatter plot: in space!
fig.patch.set_facecolor('xkcd:black')
ax.set_facecolor('xkcd:black')
plt.axis('off')

#Animates the scatter plot
#i is an iterator variable
def animate(i):
    iterate = (100*i)
   
    data = np.vstack((x_vals[iterate:iterate+99],y_vals[iterate:iterate+99]))
    data = np.transpose(data)
    plot.set_offsets(data)

    return plot,

#repeatedly call animate function
ani = animation.FuncAnimation(fig,animate,interval=200,blit=True)





plt.axis([-5000,5000,-5000,5000])
plt.show()

writergif = animation.PillowWriter(fps=60)
ani.save('/Users/StephenSigman/Desktop/CP341/animation.gif',writer = writergif)
