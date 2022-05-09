#!/usr/bin/env bash

./clearWeakClassifiers.sh
./generateRandomFeatures.sh 50

cd ../train
./demo

