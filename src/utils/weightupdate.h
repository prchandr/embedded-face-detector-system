#ifndef weightupdate_h
#define weightupdate_h

#include <stdio.h>


/*
This class represents a weak classifier. It uses a feature, 
threshold, and polarity to classify an image as a face or
non-face.
*/

class training {
public:
	training();

	// Getters for private variables
	float training::normalize(float weight);
	training::weightinitialize(vector<vector<vector<int>>> img);

	// Setters for private variables
	
private:
	featureType feature;
	int width, height;
	int startRow, startCol;
	float threshold;
	float error =0;
	float beta = 0;
	vector<int> e;
	int polarity;
    int y1 = 0,y2 = 0;
	int index;
	int total_weight=0;
}

#endif
