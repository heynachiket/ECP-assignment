#!/bin/bash

echo "enter three no's to compare max"
read a
read b
read c

if [ $a -gt $b ]
 then
	if [ $a -gt $c ]
then
	echo "$a is max"
	else
		echo "$c is max"
	fi
else
if [ $b -gt $c ] 
then
	echo "$b is max"
else
	echo "$c is max"
fi
fi
