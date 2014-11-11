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

/usr/bin/gnuplot -persist  |&

print -p "n=$number" #number of intervals

print -p "min=$min" #min value
print -p "max=$max" #max value
print -p "width=(max-min)/n" #interval width

#function used to map a value to the intervals
print -p "hist(x,width)=width*(floor((x-min)/width)+0.5) + min"
print -p "set boxwidth width*0.9"

print -p "set xrange[min:max]"
#count and plot
print -p "plot '$file' u (hist(\$$col,width)):($scale) smooth freq w boxes lc rgb'blue' notitle"

