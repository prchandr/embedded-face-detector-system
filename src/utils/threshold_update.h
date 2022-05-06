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

    threshold_update::threshold_update(float threshold, int index, vector<vector<vector<int>>> img, int y1, int y2);
    
    float threshold_update::update(vector<float> weight);

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
