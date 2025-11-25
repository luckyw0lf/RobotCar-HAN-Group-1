#!/bin/sh
F_CPU="16000000"
if [ -n "$1" ]; then
	# for all prescaler values
	for i in {1,8,64,256,1024}; do
		num=$(echo "($1 / (1/$F_CPU * $i) - 1)" | bc -l);
		int=$(printf "%.0f" "$num");

		printf "prescaler %4d\tICRn = " "$i";
		printf "%5d" "$int";

		if [ $int -lt 256 ] && [ $int -gt 0 ]; then
			printf "\t8bit TIMER ok\n";
		elif [ $int -lt 65535 ] && [ $int -gt 0 ]; then
			printf "\t16bit TIMER ok\n";
		else
			printf "\n";
		fi
	done
else
	echo "$0 \"(10 ^ -6)\""
fi


