import sys 
import re
import glob
import numpy as np 
import matplotlib.pyplot as plt

filename = str(sys.argv[1])
p = re.search('_p(.+?)_T', filename).group(1) 
p = float(p.split('_p', 1)[1])
T = float(re.search('_T(.+?).dat', filename).group(1)) 

print 'p = ', p 
print 'T = ', T 


R = 0.0083143
k = 1.3806488e-23
beta = R*T
m = 2.

#setting up the figure 
#plt.rcParams.update({'font.size': 24})
f = plt.figure(figsize = (12,14))
ax1 = plt.subplot(121)
ax2 = plt.subplot(122)
#f, (ax1, ax2) = plt.subplots(1, 2, sharey = True) 


#fig = plt.figure(figsize=(10,8), dpi=80)
#plt.subplot(1,1,1) 


pos_points = np.linspace(-0.08, 0.08, num = 100)
pos_prob = np.exp(-(m*p/(2.*beta))*pos_points**2)*np.sqrt(2.*p/(2*np.pi*beta))

vel_points = np.linspace(-9, 9, num=100)
vel_prob = np.exp(-(beta/p)*(m/2.)*vel_points**2)*np.sqrt(p/(2.*2.*beta*np.pi))

vel, pos = np.loadtxt(filename, usecols = (1, 3), unpack=True)

ax1.hist(pos, bins=100, normed=True, log=True, histtype=u'step') 
#ax1.plot(pos_points, pos_prob)

ax2.hist(vel, bins=100 , normed=True, log=True, histtype=u'step') 
#ax2.plot(vel_points, vel_prob)

ax1.set_ylim(10e-5, 10e1)
ax1.set_xlim(-0.08,0.08)
ax1.set_xlabel(r"distance to neighbor")
ax1.set_ylabel(r"probability")
#start, end = ax1.get_xlim()
#ax1.xaxis.set_ticks(np.arange(start, end, 7))


ax2.set_ylim(10e-5, 10e-1)
ax2.set_xlim(-10,10)
ax2.set_xlabel(r"velocity")


#plt.ylabel(r"probability")


image_filename = filename.replace('pos_vel_', '')
image_filename = image_filename.replace('.dat', '_verteilung.jpg')
f.savefig(image_filename)
plt.show()

