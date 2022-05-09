## Bash Scripts

This directory holds several useful Bash scripts for training classifiers, many of which are self-describing.

### 

### Make Random Features
To generate a single random feature (or Weak Classifier), run 
```
./makeRandomFeature.sh
```

To generate multiple random features, run 
```
./generateRandomFeatures.sh [numFeatures]
```
This runs the **`makeRandomFeature.sh`** script that many times, creating that many weak classifiers. 

### Clearing Weak Classifiers folder
To remove all weak classifier files from the weak classifiers directory, run
```
./clearWeakClassifiers.sh
```

### Making new Strong Classifier
To make a new strong classifier by AdaBoosting a set of weak classifiers using the training images, run 
```
./makeStrongClassifier.sh
```

This clears the weak classifier directory, makes 32 new weak classifiers, trains them on the training images directory, then using boosting, returns a trained strong classifier using 5 of the weak classifiers.