#check if the no is prime or not ?
#!/bin/bash

echo -n "enter a num to check if its prime or not? = "
read n

if [ $n -lt 2 ]; then
	echo "$n not a prime"
	exit
fi

i=2
flag=0

while [ $i -lt $n ]
do 
	if [ $(($n % $i)) -eq 0 ];then
		flag=1
		break
	fi
	i=$(($i+1))
done
        if [ $flag -eq 1 ]
then
		echo "$n is a not a prime"
	else
		echo "$n is a prime"
	fi






