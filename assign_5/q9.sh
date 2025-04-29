#!/bin/bash

echo -n "Bhayya please input dijiye, hame uska factorial nikalna hai: "
read n

orig=$n  # original number ko save kar lo for later use

if [ "$n" -eq 0 ]; then
    echo "Factorial of $n is 1"
elif [ "$n" -lt 0 ]
then
    echo "Factorial of negative number does not exist"
else
    fact=1
    while [ "$n" -gt 0 ]
    do
        fact=$((fact * n))
        n=$((n - 1))
    done
    echo "Bhai $orig ka factorial mil gaya!"
    echo "Batau?"

    echo "Chalo bata deta hu"
    echo "Bhai $orig ka factorial hai $fact"
fi

