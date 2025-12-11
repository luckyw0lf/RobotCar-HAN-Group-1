#!/bin/sh

# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 3

F_CLK="16000000"		#16 MHz
F_CLK_TIMER2="32768"	#32768 Hz

if [ -n "$1" ] && [ -n "$2" ]; then
	#select clock frequency
	if [ "$1" == "timer0" ] || [ "$1" == "timer1" ]; then
		FREQ=$F_CLK;
	elif [ "$1" == "timer2" ]; then
		FREQ=$F_CLK_TIMER2;
	fi

	# for all prescaler values
	for i in {1,8,64,256,1024}; do
		num=$(echo "($2 / (1/$FREQ * $i) - 1)" | bc -l);
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
	printf "$0: {timer0|timer1|timer2} *desired timer freq*\n"
	printf "$0 timer1 \"(10 ^ -6)\"\n"
fi


