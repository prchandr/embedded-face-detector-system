#!/usr/bin/env bash

./clearWeakClassifiers.sh
./generateRandomFeatures.sh 32

cd ../train
./demo

