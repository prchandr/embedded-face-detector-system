## Strong Classifiers File

This directory holds the configuration files for the strong classifiers. 

The filename is formatted as `classifier_XX.txt` where XX is the index. 

The format of the classifier file is as follows:
```
<weight>					| Weak Classifier #1 Weight 
<feature_type> <width> <height>			|
<start_row> <start_col>				| Weak Classifier #1 Config
<parity> <threshold>				|

<weight>					| Weak Classifier #2 Weight
<feature_type> <width> <height>			|
<start_row> <start_col>				| Weak Classifier #2 Config
<parity> <threshold>				|
.
.
.
```



