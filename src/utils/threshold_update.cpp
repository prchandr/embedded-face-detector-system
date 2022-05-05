#include "threshold_update.h"


thrshold_update::threshold_update(float threshold, int index, vector<vector<vector<int>>> img, int y1, int y2) {
    this->threshold = threshold;
}
    
float thrshold_update::update(vector<float> weight){
    
    vector<int> a;
    float e, e2;
    int count = 0;
    int T = y1;
    int S = y2;
    int t, s;
    
    // increase the value with 10 size
    while()
    {
        WeakClassifier Weak.WeakClassifier(feature, width, height, startRow, startCol, polarity, threshold);
        for(int i=0; i<index; i++)
        {
            if(polarity[i] == 1)
                T += weight[i];
            else
                S += weight[i];
            if(Weak.classifyImage(img[i]) == 1 && polarity[i] == 1)
                t += weight[i];
            else
                s += weight[i];
        }
        e = min(S+t-s, s + T - S);
        threshold += 10;
        if(count != 0 && e>e2)
        {
            threshold -= 10;
            break;
        }
        e2=e;
    }
    
    // increase the value with 1 size
    count = 0;
    while()
    {
        WeakClassifier Weak.WeakClassifier(feature, width, height, startRow, startCol, polarity, threshold);
        for(int i=0; i<index; i++)
        {
            if(polarity[i] == 1)
                T += weight[i];
            else
                S += weight[i];
            if(Weak.classifyImage(img[i]) == 1 && polarity[i] == 1)
                t += weight[i];
            else
                s += weight[i];
        }
        e = min(S+t-s, s + T - S);
        threshold += 1;
        if(count != 0 && e>e2)
        {
            threshold -= 1;
            break;
        }
        e2=e;
    }
    
    //increase the threshold in .1 size
    count =0;
    while()
    {
        WeakClassifier Weak.WeakClassifier(feature, width, height, startRow, startCol, polarity, threshold);
        for(int i=0; i<index; i++)
        {
            if(polarity[i] == 1)
                T += weight[i];
            else
                S += weight[i];
            if(Weak.classifyImage(img[i]) == 1 && polarity[i] == 1)
                t += weight[i];
            else
                s += weight[i];
        }
        e = min(S+t-s, s + T - S);
        threshold += .1;
        if(count != 0 && e>e2)
        {
            threshold -= .1;
            break;
        }
        e2=e;
    }
    
    //increase the threshold in .01 size
    count =0;
    while()
    {
        WeakClassifier Weak.WeakClassifier(feature, width, height, startRow, startCol, polarity, threshold);
        for(int i=0; i<index; i++)
        {
            if(polarity[i] == 1)
                T += weight[i];
            else
                S += weight[i];
            if(Weak.classifyImage(img[i]) == 1 && polarity[i] == 1)
                t += weight[i];
            else
                s += weight[i];
        }
        e = min(S+t-s, s + T - S);
        threshold += .01;
        if(count != 0 && e>e2)
        {
            threshold -= .01;
            break;
        }
        e2=e;
    }
    
    return threshold; // final value
}

