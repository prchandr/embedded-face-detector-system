#!/usr/bin/env bash

./clearWeakClassifiers.sh

echo "Weak Classifiers erased..." 

./generateRandomFeatures.sh 1024

echo "New Weak Classifiers generated!"

cd ../train
./demo

echo "Done training! New Strong Classifier made."
