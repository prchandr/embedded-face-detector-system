# Embedded-Face-Detector-System
## ENEE408M Capstone: Embedded Face Detector System using Viola-Jones for Raspberry Pi

### Getting Dataset of Images
The images used for training and testing are obtained from a dataset based on the MIT CBCL dataset, found [here](https://github.com/paveyry/FaceDetection/tree/master/learning-tests). 

Download the images by navigating to the project directory and running the 
```
idxupdate project-dataset
```
on the DICE command line, or simply running the **`installDataset.sh`** script.


### About the Algorithm
The Viola-Jones algorithm is an object-detection framework that allows for the detection of specific image features in real time. There are two main stages in the Viola-Jones algorithm: training and detection.

During the training stage, the machine is being trained to identify Haar-like features. There are three types of Haar-like features that are identified by the Viola-Jones algorithm: edge features, line features, and four-sided features. Since these images have been converted to grayscale, there is a dark side and a light side to each of these features. The two important features for Face Detection, the horizontal and the vertical features, describe the eyebrows and the nose respectively.

The algorithm then shrinks the image to a 24x24 subwindow and looks for trained features within the image. The more facial data the algorithm consumes, the algorithm can more accurately set the minimum threshold to determine whether something can be classified as a feature or not. Additionally, the more non-facial data the algorithm consumes, the algorithm can more accurately differentiate between the two, understanding what images are faces and what images just look similar to a face.

Subsequently, the most accurate model looks at all the possible combinations for each frame or image, which is more likely to identify false positives and true negatives. Each feature the algorithm identifies, also known as the weak classifier, is given a weight and combined to get the strong classifier. The more weak classifiers there are, the stronger the strong classifier. Additionally, the most important features are given a higher weight to improve detection, so the AdaBoost algorithm increases the importance of the images the algorithm falsely identified as negatives, and finds the next best feature to fit these images and complement the strongest features. 

For the detection stage, each feature is given its own value. To get this value, you can add all the pixels in the dark side of the feature, add all the pixels in the light side of the feature, and then subtract the light side from the dark side to get the feature value. However, since this is time-intensive, you can create an integral image by calculating the sum of all the pixels to the left of a pixel. Then, you can find the four corners of the feature, add the top left and bottom right values, and then subtract the top right and bottom left values from that sum to get the value of the feature.

Finally, to speed up and provide more accuracy to the Viola-Jones algorithm, cascading can be used by looking to see if a feature is within a subwindow. If the most important feature isn't there, then the entire subwindow is disregarded, but if it is, then the next important feature is looked for. If the second feature isn't there, then the entire subwindow is also disregarded. Only when all three features are present will the algorithm calculate the strong classifier, speeding up the Viola-Jones algorithm.
