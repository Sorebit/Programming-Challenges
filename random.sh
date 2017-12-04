#!/bin/bash
#
# random.sh - randomize a challenge and remove it

file="CHALLENGES-LEFT.md"

while true; do
	shuf -n 1 $file
	printf "Accept and remove from list? [y/N]: "
	read line
	case $line in
		"y"|"Y")
			exit 0
			;;
	esac
done