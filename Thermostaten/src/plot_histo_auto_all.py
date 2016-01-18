import Gnuplot
import sys 
import os

def string_after(s,dem):
	str_r = s.partition(dem)[2]
	if str_r: return str_r.split()[0]
	else: return 0

def norm_func(sigma2):
	return "sqrt(1/(2*pi*" + str(sigma2) + "))*exp(-x**2/(2*" + str(sigma2) + "))" 
	
def plot_theory(kind , sim):
        k= 0.008314464
	if kind == "relPos": re = norm_func( 1./(sim.feder*sim.beta) )
	elif kind == "velocity": re = norm_func( 1./(sim.mass*sim.beta) )
	elif kind == "tempCol": 
		re = "exp(-x*" + str(sim.p) + "/(2*" + str(sim.temp) + "))*(1/gamma(" + str(sim.p) + "/2))*(" + str(sim.p)+ "*x/(2*" + str(sim.temp) + "))**(" + str(sim.p) + "/2)*(1/x)"                
		print re
	else: return ""
	return re + "w l lc 'black' t 'theory',"

class Simulation(object):
	all_kinds = ["relPos","absPosition","velocity","tempCol","epot","schwerPos","schwerVel"]
	
	def plot_kind(self,s):
		if s == "relPos": return "distance to neighbor [nm]"
		if s == "velocity": return "velocity [nm/ps]"
		if s == "absPosition": return "absolute position [nm]"
		if s == "tempCol": return "temperature [K]"
		if s == "schwerPos" : return "center of mass position [nm]"
		if s == "schwerVel" : return "center of mass velocity [nm/ps]"
                if s == "epot" : return "potential energy [kJ/mol]"
		
		return s
		
	def __init__(self,filename):
		f = open(filename, 'r')
		print "Lese '%s'" %filename
		line = f.readline()
		head = ""
		while line[0] == '#':
			head += line
			head_last = line.split()
			line = f.readline()
		f.close()
		
		self.filename = filename
		self.temp = float( string_after( head , "temp" ) )
		self.beta = float( string_after( head , "beta" ) )
		self.p = int( string_after( head , "trotter" ) )
		self.initiate = string_after( head , "initiate" ) 
		self.mass = float( string_after( head , "monomerMass" ) )
		self.feder = float( string_after( head , "feder" ) )
		
		self.thermostat = ( string_after( head , "Thermostat" ) )
                self.thermostat = self.thermostat.replace("_", " ")
		self.dtime = float( string_after( head , "dtime" ) )
		self.q2 = float( string_after( head, "q2" ) )
		
		self.runs = int( float( string_after( head , "runs" ) ) )
		self.warm = int( float( string_after( head , "warm" ) ) )
		self.reset = int( float( string_after( head , "reset" ) ) )
		
		self.title = ""
		self.kinds = ""
		self.histo = {}
		for kind in self.all_kinds:
			col = int( string_after( head , kind ) )
			if col:
				self.kinds += kind + " "
				self.histo[kind]= [self.plot_kind(kind),col,head_last[col],head_last[col+1]]
				
def set_titles(l_sim):
	title = ""
	
	buf = l_sim[0].thermostat
	flag = True
	for sim in l_sim: flag = flag and (buf == sim.thermostat)
	if flag: title += buf
	else: 
		for sim in l_sim: sim.title += sim.thermostat

	buf = l_sim[0].initiate
	flag = True
	for sim in l_sim: flag = flag and (buf == sim.initiate)
	if flag: title += " " + buf
	else: 
		for sim in l_sim: sim.title += " " + sim.initiate
		
	buf = l_sim[0].reset
	flag = True
	for sim in l_sim: flag = flag and (buf == sim.reset)
	if flag: 
		if sim.reset > 0: title += " reset=" + '%g' % (buf)
	else: 
		for sim in l_sim:
			if sim.reset > 0: sim.title += " reset=" + '%g' % ( sim.reset )
		
	buf = l_sim[0].temp
	flag = True
	for sim in l_sim: flag = flag and (buf == sim.temp)
	if flag: title += " T=" + '%g' % (buf)
	else: 
		for sim in l_sim: sim.title += " T=" + '%g' % ( sim.temp )
	
	buf = l_sim[0].p
	flag = True
	for sim in l_sim: flag = flag and (buf == sim.p)
	if flag: title += " p=" + '%g' % (buf)
	else: 
		for sim in l_sim: sim.title += " p=" + '%g' % ( sim.p )
		
	buf = l_sim[0].dtime
	flag = True
	for sim in l_sim: flag = flag and (buf == sim.dtime)
	if flag: title += " dtime=" + '%g' % (buf)
	else: 
		for sim in l_sim: sim.title += " dtime=" + '%g' % ( sim.dtime )
	
	buf = l_sim[0].runs
	flag = True
	for sim in l_sim: flag = flag and (buf == sim.runs)
	if flag: title += " steps=" + '%g' % buf
	else: 
		for sim in l_sim: sim.title += " steps=" + '%g' % ( sim.runs )
	
	buf = l_sim[0].warm
	flag = True
	for sim in l_sim: flag = flag and (buf == sim.warm)
	if flag: title += " warm=" + '%g' % (buf)
	else: 
		for sim in l_sim: sim.title += " warm=" + '%g' % ( sim.warm )
	

	buf = l_sim[0].q2
	flag = True
	for sim in l_sim: flag = flag and (buf == sim.q2)
	if flag: title += " q2=" + '%g' % (buf)
	else: 
		for sim in l_sim: sim.title += " q2=" + '%g' % ( sim.q2 )
	
	return title
	
	
######### MAIN ##########
g = Gnuplot.Gnuplot(persist = 1)

l_sim = [Simulation(sys.argv[i]) for i in range( 1 , len(sys.argv) ) if os.path.isfile(sys.argv[i])]
if len(l_sim) == 0:
	print "<< Es wurde keine Datei uebergeben."
	sys.exit()
print

title = set_titles(l_sim)
title = title.replace(" ", "_")
#g( 'set title "' + title + '"' )
g( 'set style line 6 lt rgb "brown"')

g( 'set yrange [1E-5:]' )
#g( 'set xrange [0:1E4]' )
g( 'set logscale y' )
g( 'set ylabel "probability density"' )
plot_count = -1
all_outF = "" 
for kind in Simulation.all_kinds:
	plot_data="plot"
	l_p = list();
	l_temp = list();
	k = 1
	for sim in l_sim:
		if sim.kinds.find(kind) < 0 : continue
		l_p.append(sim.p)
		l_temp.append(sim.temp)
		sim_plot = sim
		
		plot_data += " '" + sim.filename + "'" 
		plot_data += " u " + str(sim.histo[kind][1]) + ":" + str(sim.histo[kind][1]+1)
		plot_data += " w l linestyle " + str(k) + " t '" + sim.thermostat + "' ,"
                k += 1
	if plot_data == "plot" : continue
	plot_count += 1
	g( 'set xlabel "' + sim_plot.histo[kind][0] + '"' )
        if sim_plot.histo[kind][0]=="potential energy [kJ/mol]": 
            g('set xrange[0:15]')
        elif sim_plot.histo[kind][0]=="center of mass velocity [nm/ps]": 
            g('set xrange[-5:5]')
        elif sim_plot.histo[kind][0]=="velocity [nm/ps]": 
            g('set xrange[-10:10]')
        elif sim_plot.histo[kind][0]=="absolute position [nm]": 
            g('set xrange[-3:3]')
        elif sim_plot.histo[kind][0]=="distance to neighbor [nm]": 
            g('set xrange[-0.07:0.07]')
        elif sim_plot.histo[kind][0]=="temperature [K]": 
            g('set xrange[0:60]')
        else: g('set autoscale x')
	
	b_same = True
	for i in range( 1 , len(l_p) ):
		b_same = b_same and l_p[0] == l_p[1] and l_temp[0] == l_temp[i]
	if b_same:
		plot_data += plot_theory( kind, sim_plot )
	plot_data = plot_data[:-1]
	
	g( 'set term x11 ' + str( plot_count ) )
	g( 'set output' )
	g( plot_data )
	
	outF = "Histogramm_" + kind + title + ".png"
	g( 'set terminal png large size 1224,768 font times 20 linewidth 1' )
        #g( 'set terminal epslatex')
	g( 'set output "' + outF + '"' )
	g( 'repl' )
	all_outF += "Das Bild '" + outF + "' wurde erstellt.\n"

print all_outF
