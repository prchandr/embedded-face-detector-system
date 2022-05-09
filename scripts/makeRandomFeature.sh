#!/usr/bin/env bash

#Constants
NUM_FEATURE_TYPES=5
IMAGE_MAX_WIDTH=24
IMAGE_MAX_HEIGHT=24

DEFAULT_PARITY=1
DEFAULT_THRESHOLD=0
DEFAULT_WEIGHT=1

FILE_PREFIX=wc

# Get next classifier index from filenames
classifier_dir=../classifiers/weak
cd $classifier_dir
num_files=$(ls  | wc -l)
feature_index=$((num_files - 1))
echo "index="$feature_index

# Make random feature type
feature_type=$((RANDOM % NUM_FEATURE_TYPES))
echo "featureType="$feature_type

# Get random size, fix as needed
case $feature_type in
	0)
		# height must be multiple of 2
		width=$((RANDOM % (IMAGE_MAX_WIDTH - 1) + 1))
		height=$((2 * (RANDOM % ((IMAGE_MAX_HEIGHT - 1) / 2) + 1)))
		;;

	1)
		# width must be multiple of 2
		width=$((2 * (RANDOM % ((IMAGE_MAX_WIDTH - 1) / 2) + 1)))
		height=$((RANDOM % (IMAGE_MAX_HEIGHT - 1) + 1))
		;;

	2)
		# height must be multiple of 3
		width=$((RANDOM % (IMAGE_MAX_WIDTH - 1) + 1))
		height=$((3 * (RANDOM % ((IMAGE_MAX_HEIGHT-1)/3) + 1)))
		;;

	3)
		# width must be multiple of 3
		width=$((3 * (RANDOM % ((IMAGE_MAX_WIDTH - 1) / 3) + 1)))
		height=$((RANDOM % (IMAGE_MAX_HEIGHT - 1) + 1))
		;;

	4)
		# both height and width must be even
		width=$((2 * (RANDOM % ((IMAGE_MAX_WIDTH - 1) / 2) + 1)))
		height=$((2 * (RANDOM % ((IMAGE_MAX_HEIGHT - 1) / 2) + 1)))
		;;
	*)
		echo "Error: Unexpected feature type."
		width=-1
		height=-1
		;;
esac

echo "width = "$width
echo "height = "$height

# Get random position appropriate to size
if [[ $width = 23 ]]
then
	startCol=0
else
	startCol=$((RANDOM % (IMAGE_MAX_WIDTH - 1 - width)))
fi

if [[ $height = 23 ]]
then
	startRow=0
else
	startRow=$((RANDOM % (IMAGE_MAX_HEIGHT - 1 - height)))
fi

echo "startRow = "$startRow
echo "startCol = "$startCol

# Write to new file
echo $feature_type $width $height >> ${FILE_PREFIX}_${feature_index}.txt
echo $startRow $startCol >> ${FILE_PREFIX}_${feature_index}.txt
echo $DEFAULT_PARITY $DEFAULT_THRESHOLD >> ${FILE_PREFIX}_${feature_index}.txt
echo $DEFAULT_WEIGHT >> ${FILE_PREFIX}_${feature_index}.txt
