import glob
import numpy as np 
import matplotlib.pyplot as plt

p = 4
T = 20

R = 0.0083143
k = 1.3806488e-23
beta = R*T
m = 2.
#setting up the figure 
#plt.rcParams.update({'font.size': 24})
fig=plt.figure(figsize=(10,8), dpi=80)
plt.subplot(1,1,1) 


vel_points = np.linspace(-2, 2, num=100)

vel_prob = np.exp(-(beta/p)*(m/2.)*vel_points**2)*np.sqrt(p/(2.*2.*beta*np.pi))

pos, vel = np.loadtxt("Andersen_pos_vel_p=4_T=20.dat", unpack=True)


plt.hist(vel, bins=100, range=(-5,5) , normed=True) 
#plt.plot(vel_points, vel_prob)

plt.xlim(-2,2)
plt.xlabel(r"velocity")
plt.ylabel(r"probability")

fig.savefig("Andersen_vel_p=4_T=20.jpg")
plt.show()

