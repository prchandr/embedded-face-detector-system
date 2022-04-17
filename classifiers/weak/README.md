## Weak Classifiers Files
This directory holds the files describing each weak classifier. The name of the file should be `weak_XX.txt`, where XX is the 2 digit index starting at 00.

The format of the file is as shown below.
```
<feature_type> <width> <height>
<start_row> <start_col>
<parity> <threshold>
```

The <feature\_ type> is an integer in [0, 4] that specifies the type of Haar-like feature that the clasifier uses. The <width> and <height> arguments are integers in [1, 24] that represent the dimensions of the feature. The dimensions provided are expected to be in accordance with the feature type (for example, Type 0 cannot have height 1, or Type 4 cannot be 2x1).

The types of features are shown below. 0 represents a black square, 1 represents a white square

```
Type 0: Vertical Edge
0 0 
0 0 
1 1 
1 1 

Type 1: Horizontal Edge
1 1 0 0 
1 1 0 0 

Type 2: Vertical Line
0 0
1 1 
0 0 

Type 3: Horizontal Line
0 1 0 
0 1 0 

Type 4: Four-Rectangle
1 1 0 0
1 1 0 0
0 0 1 1 
0 0 1 1 

```

The <start\_row> and <start\_col> are integers that represent the location of the top left pixel of the feature in the 24x24 image subwindow.

Both the feature dimensions and the start coordinates must allow the entire feature to stay within the 24x24 subwindow.

The <parity> and <threshold> values default to 1 and 0.5, respectively, until the classifier is properly trained on the training set. 

e.g. 

0 6 2
5 5
1 0.5



