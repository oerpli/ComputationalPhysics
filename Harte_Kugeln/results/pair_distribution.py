import Gnuplot
import sys
import os 
import glob
import linecache
import numpy as np

def string_after(s, dem): 
    str_r = s.partition(dem)[2]
    if str_r: 
        return str_r.split("_")[0]
    else: 
        return 0

def set_param(): 
    ss_para = "DIM" + sys.argv[1] + "_N" + sys.argv[2] + "_r" + sys.argv[3] + "_m" + sys.argv[4]
    return ss_para 

### Main ###
parameter = set_param()
print parameter
N = int(string_after(parameter, "_N"))
radius = float(string_after(parameter, "_r"))
number_of_files = 0; 

gnu = Gnuplot.Gnuplot(persist = 1)

gnu( 'set title "Pair distribution function"' )
gnu( 'set xlabel "r"' )
gnu( 'set ylabel "g(r)"' ) 

search_string = "./Pair_distribution_"+str(parameter)+"*"
print search_string
for file in glob.glob(search_string):
    number_of_files += 1  
    name_output = file.partition("_DIM")[0] + "_function" + file.partition("distribution")[2]
    rho = float(string_after(name_output, "_rho"))
    f_output = open(name_output, "w") 
    f_pair_dist = open(file, "r")
    for line in f_pair_dist: 
        data = line.split("\t")
        g = float(data[1])
        r = float(data[0])
        g = g*(N-1)*np.power(2*radius,3)/(4.0*np.pi*rho*r*r)
	print g 
        f_output.write("%f" %r + " " + "%f" %g + " \n")
    f_output.close()
    
    plot_data = "plot '" + name_output + "' u "
    plot_data += "($1/" + str(2.0*radius) + "):2 w l t 'rho = " + str(rho)
    #gnu( 'set xrange[1:' + str(int(np.sqrt(3)*np.power(N/rho, 1./3.)/(2.*radius))) + ']')
    gnu( 'set xrange[1:' + str(5.*radius) + ']')
    gnu( 'set term x11 ' + str(number_of_files) ) 
    gnu( 'set output' )
    gnu( plot_data )
    gnu( 'set terminal png large size 1024,768' )
    name_image = name_output.partition(".dat")[0] + ".png"
    gnu( 'set output "' + name_image + '"' )
    gnu( 'repl' )
    #print "Das Bild '" + name_image + "' wurde erstellt.\n"

search_string = "./Pair_distribution_function_"+str(parameter)+"*.dat"
name_output = "eos_"+str(parameter)+".dat"
f_output = open(name_output, 'w')
 
for file in sorted(glob.glob(search_string)):  
    rho = float(string_after(file, "_rho"))
    data = linecache.getline(file, 1).split(' ')
    g = float(data[1])
    f_output.write("%f" %rho + " " + "%f" %(1.+2.*np.pi*g*rho/3.) + " \n")
  
f_output.close()
  
gnu( 'pi = 3.141593' )
gnu( 'f(x) = 1 + (x*pi/6.0 + (x*pi/6.0)**2 - (x*pi/6.0)**3)/((1-(x*pi/6.0))**3) ' ) 
gnu( 'set title "Equation of state"' )
gnu( 'set xlabel "rho"' )
gnu( 'set ylabel "p/(rho*k*T)"' )
gnu( 'set xrange[0:1.4]' )
gnu( 'set term x11 ' + str(number_of_files+1) ) 
gnu( 'set output' )
plot_data = "plot '" + name_output + "' , f(x) " 
gnu( plot_data )
gnu( 'set terminal png large size 1024,768' )
name_image = name_output.partition(".dat")[0] + ".png"
gnu( 'set output "' + name_image + '"' )
gnu( 'repl' )
#print "Das Bild '" + name_image + "' wurde erstellt.\n" 
