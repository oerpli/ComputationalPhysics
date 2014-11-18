import sys 
import re
import glob
import numpy as np 
import matplotlib.pyplot as plt

p = float(sys.argv[1])
T = float(sys.argv[2])

R = 0.0083143
beta = 1./(R*T)
hbarsq = 0.00403324
m = 2.0

sigma_pos_sq = beta*hbarsq/(m*p)
sigma_pos = np.sqrt(sigma_pos_sq)
sigma_vel_sq = p/(m*beta)
sigma_vel = np.sqrt(sigma_vel_sq)

fig_pos = plt.figure(1, figsize = (16,12))
fig_vel = plt.figure(2, figsize = (16,12))


string ="*_histo_p"+str(int(p))+"_T"+str(int(T))+".dat"
print string
for file in glob.glob(string):
	filename = str(file)
	thermostat = filename.replace("_histo_p"+str(int(p))+"_T"+str(int(T))+".dat", "")
	print thermostat
	vel, prob_vel, pos, prob_pos = np.loadtxt(file, comments='#', unpack=True)
	plt.figure(1)
	plt.plot(pos, prob_pos, label = thermostat)
	plt.figure(2) 
	plt.plot(vel, prob_vel, label = thermostat)


prob_pos = np.exp(-pos**2/(2*sigma_pos_sq))*np.sqrt(1/(2*np.pi*sigma_pos_sq))
prob_vel = np.exp(-vel**2/(2*sigma_vel_sq))*np.sqrt(1/(2*np.pi*sigma_vel_sq))

plt.figure(1)
plt.plot(pos, prob_pos, label = "theory") 
plt.legend()
plt.yscale('log')
plt.xlim(-5.*sigma_pos,5.*sigma_pos)
plt.ylim(10e-5, 10e2)
plt.xlabel(r"distance to neighbor")
plt.ylabel(r"probability")
image_filename = "distance_distribution_p"+str(int(p))+"_T"+str(int(T))+".jpg"
plt.savefig(image_filename)


plt.figure(2)
plt.plot(vel, prob_vel, label = "theory") 
plt.legend()
plt.yscale('log')
plt.xlim(-5.*sigma_vel,5.*sigma_vel)
plt.ylim(10e-5, 10e1)
plt.xlabel(r"velocity")
plt.ylabel(r"probability")
image_filename = "velocity_distribution_p"+str(int(p))+"_T"+str(int(T))+".jpg"
plt.savefig(image_filename)
plt.show()



