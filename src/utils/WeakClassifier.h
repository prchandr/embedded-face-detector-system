#ifndef weak_classifier_h
#define weak_classifier_h

#include <fstream>
#include "ImageSubwindow.h"
#include "FeatureType.h"

/*
This class represents a weak classifier. It uses a feature, 
threshold, and polarity to classify an image as a face or
non-face.
*/

class WeakClassifier {
public:
	WeakClassifier();
	WeakClassifier(FeatureType feature, int width, int height,
				int startRow, int startCol,
				int polarity, int threshold);

	bool classifyImage(ImageSubwindow integralImage);

	// Getters for private variables
	FeatureType getFeatureType();
	int getWidth();
	int getHeight();
	int getRowStart();
	int getColStart();
	int getThreshold();
	int getPolarity();

	// Setters for private variables
	void setFeatureType(FeatureType feature);
	void setDimensions(int width, int height);
	void setStartCoords(int startRow, int startCol);
	void setClassifyParams(int polarity, int threshold);

private:
	FeatureType feature;
	int width, height;
	int startRow, startCol;
	int threshold;
	int polarity;
};

#endif
