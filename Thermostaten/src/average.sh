#!/usr/bin/ksh

awk '
	BEGIN {
		col="'$2'"+0;
		min=max=$col+0;
	}

	!/^#/{j++; val=$col+0;
		av+=val;
		
		if (min > val)
			min = val;
		else if (max < val)
			max = val;
	}

	END {
		printf "%8g %8g %8g %8g\n",j,av/j,min,max;
	} ' $1
		
