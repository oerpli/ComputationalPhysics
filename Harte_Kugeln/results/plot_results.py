# -*- coding: utf-8 -*-
import Gnuplot
import sys
import os 
import glob
import linecache
import numpy as np
import scipy.optimize as optimization

def string_after(s, dem): 
    str_r = s.partition(dem)[2]
    if str_r: 
        return str_r.split("_")[0]
    else: 
        return 0
def sort_by_rho(s): 
    rho = string_after(s, "rho")
    return rho

def set_param(): 
    ss_para = "DIM" + sys.argv[1] + "_N" + sys.argv[2] + "_r" + sys.argv[3] + "_m" + sys.argv[4]
    return ss_para 

def coll_exp(x,tau,scale): 
    return scale*np.exp(-x/tau)

### Main ###
parameter = set_param()
print parameter
N = int(string_after(parameter, "_N"))
radius = float(string_after(parameter, "_r"))
mass = float(string_after(parameter, "_m"))
number_of_files = 0; 

gnu = Gnuplot.Gnuplot(persist = 1)

#pair distribution ini
plot_data_g = "plot "
g_split = 4
g_split_count = 0
name_image_pair = " "


name_output = "eos_"+str(parameter)+".dat"
name_output_diffusion = "diffusion_"+str(parameter)+".dat"
name_output_collision = "collision_"+str(parameter)+".dat"
f_output = open(name_output, 'w')
f_output_diffusion = open(name_output_diffusion, 'w')
f_output_collision = open(name_output_collision, 'w')
search_string = "./Pair_distribution_"+str(parameter)+"*.dat"
print search_string

for file in sorted(glob.glob(search_string), key =sort_by_rho):
    number_of_files += 3
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
    f_output_collision.write("%f" %rho + " " + "%f " %(4.*np.pi*rho*np.sqrt(np.pi)*g)+"\n")
 
# collisions auswertung noch experimentell :P 
    coll_file = file.replace("Pair_distribution", "Coll_time")
    collx, colly = np.loadtxt(coll_file, unpack=True)
    tau_estimate = 1.0
    scale_estimate = 1000
    estimates = np.array([tau_estimate, scale_estimate])
    coll_fit = optimization.curve_fit(coll_exp, collx, colly, estimates)
    print coll_fit
    tau = coll_fit[0][0]
    scale = coll_fit[0][1]
    print tau, scale   
    x_values = np.arange(0.0, 0.0065, 0.0001)
    coll_func = coll_exp(x_values, tau, scale)
    coll_func = np.column_stack((x_values, coll_func)) 

    coll_outfile = file.replace("Pair_distribution", "Coll_fit")
    np.savetxt(coll_outfile, coll_func)
     
    #plot collision times
    plot_data = "plot '" + coll_file + "' u 1:2  t 'rho = " + str(rho) + "', '"+coll_outfile+"' w l t 'exponential fit'"  
#    gnu( 'set title "Velocity autocorrelation function"' )
    gnu( 'set xlabel "t [s]"' )
    gnu( 'set ylabel "probability"' ) 
    gnu( 'set term x11 ' + str(number_of_files+2) ) 
    gnu( 'set output' )
    gnu( plot_data )
    gnu( 'set terminal png large size 1024,768' )
    name_image = value_file.replace("values", "autocorrelation") 
    name_image = name_image.replace(".dat", ".png")
    gnu( 'set output "' + name_image + '"' )
    gnu( 'repl' )
    print "Das Bild '" + name_image + "' wurde erstellt.\n"     
# collisions auswertung ende

    #plot pair distribution
    g_split_count += 1

    if g_split_count%4 == 1 :
        plot_data_g = "plot "
        name_image_pair = "PairDistribution"+str(g_split_count)+".tex"
    plot_data_g += "'" + file + "' u "
    plot_data_g += "($1/" + str(2.0*radius) + "):3 w l t 'rho = " + str(rho) + "'"
    if g_split_count%4:
        plot_data_g += " , "
    else: 
        gnu( 'set xrange [1:3.5]' )
        gnu( 'set xlabel "r"' )
        gnu( 'set ylabel "g(r)"' ) 
        gnu( 'set term x11 ' + str(number_of_files) ) 
        gnu( 'set output' )
        gnu( plot_data_g )
        plot_data_g = plot_data_g.replace("t 'rho","t '$\\rho$")
        print plot_data_g
        gnu( 'set terminal epslatex size 15cm,12cm color colortext')
        gnu( 'set xlabel "$r$"' )
        gnu( 'set ylabel "$g(r)$"' )          
       # gnu( 'set terminal png large size 1024,768' )
 #       name_image = file.partition(".dat")[0] + ".png" # changed .png to .tex
        gnu( 'set output "' + name_image_pair + '"' )
        gnu( plot_data_g )
     #   gnu( 'repl' )
        print "Das Bild '" + name_image_pair + "' wurde erstellt.\n"
    
    gnu( 'set autoscale x' )

#    gnu( 'set terminal epslatex')
#    plot_data = "plot '" + file + "' u "
#    plot_data += "($1/" + str(2.0*radius) + "):3 w l t 'rho = " + str(rho)
#    gnu( 'set title "Pair distribution function"' )
#    gnu( 'set xlabel "$r [\text{m}]$"' )
#    gnu( 'set ylabel "$g(r)$"' )   
#    gnu( 'set xlabel "r [m]"' )
#    gnu( 'set ylabel "g(r)"' ) 
#    gnu( 'set term x11 ' + str(number_of_files) ) 
#    gnu( 'set output' )
#    gnu( plot_data )
#    gnu( 'set terminal png large size 1024,768' )
#    name_image = file.partition(".dat")[0] + ".png" # changed .png to .tex
#    gnu( 'set output "' + name_image + '"' )
#    gnu( plot_data )
#    gnu( 'repl' )
#    print "Das Bild '" + name_image + "' wurde erstellt.\n"

    #plot autocorrelation
    plot_data = "plot '" + value_file + "' u 1:2 w l t 'rho = " + str(rho)
#    gnu( 'set title "Velocity autocorrelation function"' )
#    gnu( 'set xrange [0:0.5]' )
    gnu( 'set xlabel "t"' )
    gnu( 'set ylabel "<v(0)v(t)>"' ) 
    gnu( 'set term x11 ' + str(number_of_files+1) ) 
    gnu( 'set output' )
    gnu( plot_data )
    gnu( 'set terminal epslatex size 15cm,12cm color colortext')
    gnu( 'set xlabel "$t $"' )
    gnu( 'set ylabel "$\\langle \\vec{v}(0) \\vec{v}(t)\\rangle$"' )
    name_image = value_file.replace("values", "autocorrelation") 
    name_image = name_image.replace(".dat", ".tex")
    gnu( 'set output "' + name_image + '"' )
    gnu( 'repl' )
    print "Das Bild '" + name_image + "' wurde erstellt.\n"     
    
    gnu( 'set autoscale x')
  
f_output.close()
f_output_diffusion.close()
  
gnu( 'pi = 3.141593' )
gnu( 'f(x) = x <= 0.945 ? 1 + (x*pi/6.0 + (x*pi/6.0)**2 - (x*pi/6.0)**3)/((1-(x*pi/6.0))**3) : 1/0 ' ) 
gnu( 'g(x) = 1 + (3.68584*(x*pi/6.0)/(1-2.5848*(x*pi/6.0) + 1.9499*((x*pi/6.0)**2) - 0.172284*((x*pi/6.0)**3)-0.16012*((x*pi/6.0)**4))) ' )
#gnu( 'set title "Equation of state"' )
gnu( 'set xlabel "rho "' )
gnu( 'set ylabel "p/(rho*k*T)"' )
gnu( 'set key Left reverse top left') 
#gnu( 'set xrange[0:1.4]' )
gnu( 'set term x11 ' + str(number_of_files+3) ) 
gnu( 'set output' )
gnu( 'set arrow 1 from 0.943,0 to 0.943,20 lt 2 lc rgb "black" lw 0.5 nohead' )
gnu( 'set arrow 2 from 1.041,0 to 1.041,20 lt 2 lc rgb "black" lw 0.5 nohead' )
plot_data = "plot '" + name_output + "' u 1:($2/2.) title 'aus Paarverteilungsfunktion', '" + name_output + "' u 1:($3/2.) title 'aus Impulsübertrag', f(x) title 'Carnahan & Starling'" 
gnu( plot_data )
gnu( 'set terminal epslatex size 15cm,12cm color colortext')
gnu( 'set xlabel "$\\rho $"' )
gnu( 'set ylabel "$p/(\\rho k T)$"' )

#gnu( 'set terminal png large size 1024,768' )
#name_image = name_output.partition(".dat")[0] + ".tex"
name_image = "eos.tex"
gnu( 'set output "' + name_image + '"' )
gnu( 'repl' )
print "Das Bild '" + name_image + "' wurde erstellt.\n" 


gnu( 'f(x) = x <= 0.945 ? (3./8.)*'+str(radius*2./(mass**(1./2.)))+'*(1./(pi**(1./2.)))*(1/x)*(1-x/1.09)*(1+x**2*(0.4-0.83*x**2)) : 1/0' )
#gnu( 'set title "Diffusion constant"' )
gnu( 'set ylabel "D"' )
gnu( 'set key default') 
gnu( 'set yrange [-0.1:]' )
gnu( 'set term x11 ' + str(number_of_files+4) ) 
gnu( 'set output' )
gnu( 'set arrow 1 from 0.943,-0.1 to 0.943,0.9 lt 2 lc rgb "black" lw 0.5 nohead' )
gnu( 'set arrow 2 from 1.041,-0.1 to 1.041,0.9 lt 2 lc rgb "black" lw 0.5 nohead' )
plot_data = "plot '" + name_output_diffusion + "' u 1:2 title 'Simulation', f(x) title 'Theorie'" 
gnu( plot_data )

gnu( 'set terminal epslatex size 15cm, 12cm color colortext' )
gnu( 'set ylabel "$D$"' )
gnu( 'set xlabel "$\\rho $"' )
#name_image = name_output_diffusion.partition(".dat")[0] + ".tex"
name_image = "diffusion.tex"
gnu( 'set output "' + name_image + '"' )
gnu( 'repl' )
print "Das Bild '" + name_image + "' wurde erstellt.\n" 

