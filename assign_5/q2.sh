#!/bin/bash
# que2

echo "check the options"

echo "Date"
echo "cal"
echo "ls"
echo "pwd"
echo "exit"

echo -n "Enter choice = "
read m

case $m in
	1)date
		;;
	2)cal
		;;
	3)ls
		;;
	4)pwd
		;;
	5) break
		;;
	*) echo "option barabar choose kr bhadve"

	esac

