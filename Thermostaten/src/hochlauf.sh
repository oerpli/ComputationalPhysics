#! /bin/ksh

rMin=$1
dr=$2
rMax=$3

states=0
r=$rMin
while [[ $r -le $rMax ]] ; do
states=$(( states + 1 ))
r=$(( r + dr ))
done

read ANSWER?"Do you want to simulate $states states? "
[[ $ANSWER == n* ]] && exit

r=$rMin
while [[ $r -le $rMax ]] ; do
	echo "$r $dr $rMax" 
	file=$( /home/waechter/GIT/ComputationalPhysics/Thermostaten/src/sim_histo Berendsen $r reset)
	
	file=$( echo $file | awk ' BEGIN { FS="<<" } {print $2} ' | awk ' { print $3 } ' )
	file=${file#?}
	file=${file%?}

	outF=$( printf "%s_para%07.3f" ${file%.dat} $r )
	outF=${outF//"."/"-"}.dat
	mv $file $outF
	echo $outF
r=$(( r + dr ))
done
