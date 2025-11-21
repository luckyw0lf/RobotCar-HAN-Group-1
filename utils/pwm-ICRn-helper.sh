#!/bin/sh

# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 3

# Calculates ICRn value with desired F_PWM
# ICRn TOP = (F_CPU / (F_PWM * N)) - 1

f_cpu=16000000
if [ -n "$1" ]; then
	for N in {1,4,8,64,256,1024}; do 
		icrval=$((f_cpu / ("$1" * N) - 1));

		printf "prescaler %4d = " "$N";
		printf "%8d" "$icrval";

		if [ $icrval -lt 256 ] && [ $icrval -gt 0 ]; then
			printf "\t8bit TIMER ok\n";
		elif [ $icrval -lt 65535 ] && [ $icrval -gt 0 ]; then
			printf "\t16bit TIMER ok\n";
		else
			printf "\n";
		fi
	done
else
	printf "Calculates ICRn value with F_PWM(Hz):\n";
	printf "Example:\n";
	printf "%s 5000\n" "$0";
fi
