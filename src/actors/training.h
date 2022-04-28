#ifndef training_h
#define training_h

#include <stdio.h>


/*
This class represents a weak classifier. It uses a feature, 
threshold, and polarity to classify an image as a face or
non-face.
*/

class training {
public:
	training();

	bool classifyImage( );

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
    int sample = 0;
}

#endif
