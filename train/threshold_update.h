#ifndef threshold_update_h
#define weightupdate_h

#include <stdio.h>


/*
This class represents a weak classifier. It uses a feature,
threshold, and polarity to classify an image as a face or
non-face.
*/

class threshold_update {
public:

    threshold_update::threshold_update(vector<int> feature, vector<int> sample);
    
    int threshold_update::update();

    // Setters for private variables
    
private:
	vector<int> threshold;
	vector<int> sample;
}

#endif
