#!/usr/bin/ksh

awk '
	BEGIN {
		col="'$2'"+0;
		min=inf;
		max=-inf;
	}

	!/^#/{ i++
		if (! first) first = $col;
		val += $(col+1)
		last = $col
	}

	END {
		printf "Integrate: %g\n",val/i*(last-first);
	} ' $1
		
