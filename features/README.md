## Features Files
This directory holds the files describing the features in the weak classifiers. The name of the file should be `feature_XX.txt`, where XX is the 2 digit index starting at 00.

The format of the file is as shown below.
```
<# of rows> <# of cols>
0, 0, ... , 1
.		    .
.           .
.           .
0, 0, ... , 1
```

The first two integers in the first row describe the dimensions. For
this project, the valid dimensions are [1, 24].

e.g. features for a 4x4 image

Type 0: 4x2 feature
```
0 0 
0 0 
1 1 
1 1 
```

Type 1: 2x4 feature
```
1 1 0 0 
1 1 0 0 
```

Type 2: 3x2 feature
```
0 0
1 1 
0 0 
```

Type 3: 2x3 feature
```
0 1 0 
0 1 0 
```
