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
mass = float(string_after(parameter, "_m"))
number_of_files = 0; 

gnu = Gnuplot.Gnuplot(persist = 1)


name_output = "eos_"+str(parameter)+".dat"
name_output_diffusion = "diffusion_"+str(parameter)+".dat"
f_output = open(name_output, 'w')
f_output_diffusion = open(name_output_diffusion, 'w')
search_string = "./Pair_distribution_"+str(parameter)+"*.dat"
print search_string
for file in sorted(glob.glob(search_string)):
    number_of_files += 2
    rho = float(string_after(file, "_rho"))
    data = linecache.getline(file, 1).split('\t')
    g = float(data[2])
    value_file = file.replace("Pair_distribution" , "values")
    data = linecache.getline(value_file, 2).split(' ')
    eos_momentum = float(data[5])/3.0 - float(data[2])
    data = linecache.getline(value_file, 3).split(' ')
    diffusion_constant = float(data[4])
    f_output.write("%f" %rho + " " + "%f " %(1.+2.*np.pi*g*rho/3.) + "%f" %eos_momentum + "\n")
    f_output_diffusion.write("%f" %rho + " " + "%f " %diffusion_constant + "\n")

    #plot pair distribution
    plot_data = "plot '" + file + "' u "
    plot_data += "($1/" + str(2.0*radius) + "):3 w l t 'rho = " + str(rho)
    gnu( 'set title "Pair distribution function"' )
    gnu( 'set xlabel "r"' )
    gnu( 'set ylabel "g(r)"' ) 
    gnu( 'set term x11 ' + str(number_of_files) ) 
    gnu( 'set output' )
    gnu( plot_data )
    gnu( 'set terminal png large size 1024,768' )
    name_image = file.partition(".dat")[0] + ".png"
    gnu( 'set output "' + name_image + '"' )
    gnu( 'repl' )
    print "Das Bild '" + name_image + "' wurde erstellt.\n"

    #plot autocorrelation
    plot_data = "plot '" + value_file + "' u 1:2 w l t 'rho = " + str(rho)
    gnu( 'set title "Velocity autocorrelation function"' )
    gnu( 'set xlabel "t"' )
    gnu( 'set ylabel "<v(0)v(t)>"' ) 
    gnu( 'set term x11 ' + str(number_of_files+1) ) 
    gnu( 'set output' )
    gnu( plot_data )
    gnu( 'set terminal png large size 1024,768' )
    name_image = value_file.replace("values", "autocorrelation") 
    name_image = name_image.replace(".dat", ".png")
    gnu( 'set output "' + name_image + '"' )
    gnu( 'repl' )
    print "Das Bild '" + name_image + "' wurde erstellt.\n"     

  
f_output.close()
f_output_diffusion.close()
  
gnu( 'pi = 3.141593' )
gnu( 'f(x) = 1 + (x*pi/6.0 + (x*pi/6.0)**2 - (x*pi/6.0)**3)/((1-(x*pi/6.0))**3) ' ) 
gnu( 'set title "Equation of state"' )
gnu( 'set xlabel "rho"' )
gnu( 'set ylabel "p/(rho*k*T)"' )
#gnu( 'set xrange[0:1.4]' )
gnu( 'set term x11 ' + str(number_of_files+2) ) 
gnu( 'set output' )
plot_data = "plot '" + name_output + "' u 1:($2/2.) title 'via pair distribution', '" + name_output + "' u 1:($3/2.) title 'via momentum flux', f(x) title 'theory'" 
gnu( plot_data )
gnu( 'set terminal png large size 1024,768' )
name_image = name_output.partition(".dat")[0] + ".png"
gnu( 'set output "' + name_image + '"' )
gnu( 'repl' )
print "Das Bild '" + name_image + "' wurde erstellt.\n" 


gnu( 'f(x) = (3./8.)*'+str(radius*2./(mass**(1./2.)))+'*(1./(pi**(1./2.)))*(1/x)*(1-x/1.09)*(1+x**2*(0.4-0.83*x**2))' )
gnu( 'set title "Diffusion constant"' )
gnu( 'set ylabel "D"' )
gnu( 'set term x11 ' + str(number_of_files+3) ) 
gnu( 'set output' )
plot_data = "plot '" + name_output_diffusion + "' u 1:2 title 'via velocity autocorrelation', f(x) title 'theory'" 
gnu( plot_data )
gnu( 'set terminal png large size 1024,768' )
name_image = name_output_diffusion.partition(".dat")[0] + ".png"
gnu( 'set output "' + name_image + '"' )
gnu( 'repl' )
print "Das Bild '" + name_image + "' wurde erstellt.\n" 

