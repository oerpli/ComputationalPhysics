#!/usr/bin/ksh

file=$1;
col=${2:-1};
number=${3:-100};

./average.sh $1 $col | read res

echo $res | awk '{print 100/$1}' | read scale

if [[ -z $4 ]] ; then
	echo $res | awk 'function max(a,b) {if (a>=b) return a; else return b} {print max(-$3,$4)}' | read max
	min=$(( -max ))
else
	min=${4:-$(( -0.3 ))}
	max=${5:-$(( -min ))}
fi

echo "$file $col $number $scale $min $max"

therm=${file%_pos*}
para=${file#*_pos_vel_} ; para=${para%.*}

if [[ $col -eq 1 ]] ; then
	outF="${therm}_pos_${para}.jpg"
	xlabel="position"
elif [[ $col -eq 2 ]] ; then
	outF="${therm}_vel_${para}.jpg"
	xlabel="velocity"
elif [[ $col -eq 3 ]] ; then
	outF="${therm}_force_${para}.jpg"
	xlabel="force"
elif [[ $col -eq 4 ]] ; then
	outF="${therm}_dis_${para}.jpg"
	xlabel="distance to neighbor"
else
	outF="${therm}_col${col}_${para}.jpg"
	xlabel="other"
fi

/usr/bin/gnuplot  |&
print -p "set terminal jpeg large size 1024,768"
print -p "set output '$outF'"

print -p "n=$number" #number of intervals

print -p "min=$min" #min value
print -p "max=$max" #max value
print -p "width=(max-min)/n" #interval width

#function used to map a value to the intervals
print -p "hist(x,width)=width*(floor((x-min)/width)+0.5) + min"
#print -p "set boxwidth width*0.9"
print -p "set style fill solid border -1"
print -p "set grid"

print -p "set xrange[min:max]"
print -p "set title '$therm with $para'"
print -p "set xlabel '$xlabel'"
print -p "set ylabel 'probability'"

print -p "plot '$file' u (hist(\$$col,width)):($scale) smooth freq w boxes lc rgb'blue' notitle"
print -p "quit"

wait

print "<< Das Bild '$outF' wurde erstellt."
eog $outF &
