## Strong Classifiers File

This directory holds the configuration files for the strong classifiers. 

The filename is formatted as `classifier_XX.txt` where XX is the index. 

The format of the classifier file is as follows:
```
<feature_type> <width> <height>			|
<start_row> <start_col>				| Weak Classifier #1 Config
<polarity> <threshold>				|
<weight>					| Weak Classifier #1 Weight 


<feature_type> <width> <height>			|
<start_row> <start_col>				| Weak Classifier #2 Config
<polarity> <threshold>				|
<weight>					| Weak Classifier #2 Weight
.
.
.
```



### Strong Classifier Descriptions

There are currently 4 trained strong classifiers in this directory.

The first 3 classifiers were trained from around 200 weak classifiers on a subset of the training images (1000 images max). Additionally, there was a bug in the way the features were calculated, so the training was likely flawed.

The last two classifiers were trained from 1024 weak classifiers on all the training images. classifier_4 is the same as 3, but with only 5 weak classifiers instead of 20. It is possible that some of the weak classifiers were also calculated incorrectly, but any future trained classifiers will be correct.

### Classifier Performance
```
classifier_0.txt

==== Performance Metrics ====
Faces: 485, NonFaces: 909
TP: 447,  FN: 38
FP: 578,  TN: 331

precision = 0.43609756097560975
recall = 0.9216494845360824
F = 0.5920529801324503
```
```
classifier_1.txt

==== Performance Metrics ====
Faces: 485, NonFaces: 909
TP: 336,  FN: 149
FP: 85,  TN: 824

precision = 0.7980997624703088
recall = 0.6927835051546392
F = 0.7417218543046358
```
```
classifier_2.txt

==== Performance Metrics ====
Faces: 485, NonFaces: 909
TP: 453,  FN: 32
FP: 294,  TN: 615

precision = 0.606425702811245
recall = 0.934020618556701
F = 0.7353896103896105
```
```
classifier_3.txt

==== Performance Metrics ====
Faces: 485, NonFaces: 909
TP: 346,  FN: 139
FP: 268,  TN: 641

precision = 0.5635179153094463
recall = 0.7134020618556701
F = 0.6296633303002731
```
```
classifier_4.txt

==== Performance Metrics ====
Faces: 485, NonFaces: 909
TP: 421,  FN: 64
FP: 251,  TN: 658

precision = 0.6264880952380952
recall = 0.8680412371134021
F = 0.7277441659464131
```

### Cascade of Strong Classifiers
```
1->4->2

==== Performance Metrics ====
Faces: 485, NonFaces: 909
TP: 325,  FN: 160
FP: 45,  TN: 864

precision = 0.8783783783783784 
recall = 0.6701030927835051 
F = 0.7602339181286549
```
