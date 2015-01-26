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

name_output = "eos_"+str(parameter)+".dat"
f_output = open(name_output, 'w')
search_string = "./Pair_distribution_"+str(parameter)+"*"
print search_string
for file in sorted(glob.glob(search_string)):
    #print file
    number_of_files += 1
    rho = float(string_after(file, "_rho"))
    data = linecache.getline(file, 1).split('\t')
    #print data
    g = float(data[2])
    value_file = file.replace("Pair_distribution" , "values")
    data = linecache.getline(value_file, 2).split(' ')
    eos_momentum = float(data[2])/3.0 + float(data[3])
    #eos_momentum = (float(data[2])+3*float(data[3]))/(3.*np.power(2.*radius, 3))
    f_output.write("%f" %rho + " " + "%f " %(1.+2.*np.pi*g*rho/3.) + "%f" %eos_momentum + "\n")

    plot_data = "plot '" + file + "' u "
    plot_data += "($1/" + str(2.0*radius) + "):3 w l t 'rho = " + str(rho)
    #gnu( 'set xrange[1:' + str(int(np.sqrt(3)*np.power(N/rho, 1./3.)/(2.*radius))) + ']')
    #gnu( 'set xrange[1:' + str(5.*radius) + ']')
    gnu( 'set term x11 ' + str(number_of_files) ) 
    gnu( 'set output' )
    gnu( plot_data )
    gnu( 'set terminal png large size 1024,768' )
    name_image = name_output.partition(".dat")[0] + ".png"
    gnu( 'set output "' + name_image + '"' )
    gnu( 'repl' )
    print "Das Bild '" + name_image + "' wurde erstellt.\n"


  
f_output.close()
  
gnu( 'pi = 3.141593' )
gnu( 'f(x) = 1 + (x*pi/6.0 + (x*pi/6.0)**2 - (x*pi/6.0)**3)/((1-(x*pi/6.0))**3) ' ) 
gnu( 'set title "Equation of state"' )
gnu( 'set xlabel "rho"' )
gnu( 'set ylabel "p/(rho*k*T)"' )
#gnu( 'set xrange[0:1.4]' )
gnu( 'set term x11 ' + str(number_of_files+1) ) 
gnu( 'set output' )
plot_data = "plot '" + name_output + "' u 1:2 title 'via pair distribution', '" + name_output + "' u 1:3 title 'via momentum flux', f(x) " 
gnu( plot_data )
gnu( 'set terminal png large size 1024,768' )
name_image = name_output.partition(".dat")[0] + ".png"
gnu( 'set output "' + name_image + '"' )
gnu( 'repl' )
print "Das Bild '" + name_image + "' wurde erstellt.\n" 
