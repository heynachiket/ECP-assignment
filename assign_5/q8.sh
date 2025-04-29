#!/bin/bash
echo -n "bhai no de mai uska table print krunga = "
read n

i=1
while [ $i -le 10 ]
do   
	table=$((n * i))
	echo " $n x $i = $table"
	i=$((i + 1))
done
