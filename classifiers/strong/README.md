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



