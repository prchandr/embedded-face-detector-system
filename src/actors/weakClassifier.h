#ifndef weak_classifier_h
#define weak_classifier_h

#include <vector>
#include <stdio.h>

// Define Types of Features
enum featureType {
	VERTICAL_EDGE,  	// 0
	HORIZONTAL_EDGE,	// 1
	VERTICAL_LINE,		// 2
	HORIZONTAL_LINE,	// 3
	FOUR_RECTANGLE		// 4
}

/*
This class represents a weak classifier. It uses a feature, 
threshold, and polarity to classify an image as a face or
non-face.
*/

class WeakClassifier {
public:
	WeakClassifier(featureType feature, int width, int height,
				int startRow, int startCol,
				int polarity, float threshold);

	//static vector<vector<int>> integrateImage(ImageSubwindow image);

	bool classifyImage(ImageSubwindow image);

	// Getters for private variables
	featureType getFeatureType();
	int getWidth();
	int getHeight();
	int getRowStart();
	int getColStart();
	float getThreshold();
	int getPolarity();

	// Setters for private variables
	void setFeatureType(featureType feature);
	void setDimensions(int width, int height);
	void setStartCoord(int startRow, int startCol);
	void setClassifyParams(int polarity, float threshold);

private:
	featureType feature;
	int width, height;
	int startRow, startCol;
	float threshold;
	int polarity;
}

#endif
