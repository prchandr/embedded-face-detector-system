## Getting Dataset
The images used for training and testing are obtained from a dataset based on the MIT CBCL dataset, found [here](https://github.com/paveyry/FaceDetection/tree/master/learning-tests). 

Download the images by navigating to the project directory and running the 
```
idxupdate project-dataset
```
on the DICE command line, or simply running the **`installDataset.sh`** script.

## Make Random Features
To generate a single random feature, run the
```
makeRandomFeature.sh
```
script on the DICE command line. 
To generate multiple random features, run the
```
generateRandomFeatures.sh
```
script on the DICE command line instead.

## Train Weak Classifiers
To train the weak classifiers using facial and non-facial data from images, run the
```
trainWeakClassifier.sh
```
script on the DICE command line.
