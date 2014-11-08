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

pos_points = np.linspace(-0.3, 0.3, num = 100)

pos_prob = np.exp(-(m*p/(2.*beta))*pos_points**2)*np.sqrt(2.*p/(2*np.pi*beta))


pos, vel = np.loadtxt("Andersen_pos_vel_p=4_T=20.dat", unpack=True)

plt.hist(pos, bins=100, range= (-0.3,0.3), normed=True) 
#plt.plot(pos_points, pos_prob)

plt.xlim(-0.3, 0.3)
plt.xlabel(r"distance to neighbor")
plt.ylabel(r"probability")

fig.savefig("Andersen_pos_p=4_T=20.jpg")
plt.show()

