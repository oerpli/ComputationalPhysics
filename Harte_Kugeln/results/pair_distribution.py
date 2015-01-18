import Gnuplot
import sys
import os 
import glob
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
    print file
    number_of_files += 1  
    name_output = file.partition("_DIM")[0] + "_function" + file.partition("distribution")[2]
    print name_output
    rho = float(string_after(name_output, "_rho"))
    f_output = open(name_output, "w") 
    f_pair_dist = open(file, "r")
    for line in f_pair_dist: 
        data = line.split("\t")
        g = float(data[1])
        r = float(data[0])
        g = g*3.0*N/(2.0*np.pi*rho*r*r)
        f_output.write("%f" %r + " " + "%f" %g + " \n")
    f_output.close()
    
    plot_data = "plot '" + name_output + "' u "
    plot_data += "($1/" + str(2.0*radius) + "):2 w l t 'rho = " + str(rho)
    gnu( 'set xrange[1:' + str(int(radius*np.power(N/rho, 1./3.))-1) + ']')
    gnu( 'set term x11 ' + str(number_of_files) ) 
    gnu( 'set output' )
    gnu( plot_data )
    gnu( 'set terminal png large size 1024,768' )
    name_image = name_output.partition(".dat")[0] + ".png"
    gnu( 'set output "' + name_image + '"' )
    gnu( 'repl' )
    print "Das Bild '" + name_image + "' wurde erstellt.\n"

    
