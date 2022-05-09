#ifndef weightupdate_h
#define weightupdate_h

#include <stdio.h>


/*
This class represents a weak classifier. It uses a feature, 
threshold, and polarity to classify an image as a face or
non-face.
*/

class weightupdate {
public:

    weightupdate::weightupdate(vector<int> sample)
	float weightupdate::normalize(float weight);
    
    float training::update(float weight)

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
