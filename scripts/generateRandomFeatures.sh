#!/usr/bin/env bash

#Define constants
MAX_FILES=1024



iterations=0

# Check if first argument exists, and is valid input
if [ $# -eq 0 ]
then
    echo "Error: No arguments provided."

elif [ $1 -le 0 ]
then
	echo "Error: Argument must be positive. Provided: $1"

elif [ $1 -ge $MAX_FILES ]
then
	echo "Provided argument too high, defaulting to $MAX_FILES"
	iterations=$MAX_FILES

else
	iterations=$1
fi


# Run makeRandomFeature.sh the provided number of times
for ((i = 1; i <= $iterations; i++))
do
	: $(./makeRandomFeature.sh)
done
