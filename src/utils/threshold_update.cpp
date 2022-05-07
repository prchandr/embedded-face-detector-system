#include "threshold_update.h"


thrshold_update::threshold_update(vector<int> feature, vector<int> sample) {
    this->threshold = feature;
	this->sample = sample;
}
    
int thrshold_update::update(){
    
    vector<int> a;
    float e, e2;
    int count = 0;
    int T = y1;
    int S = y2;
    int t, s;
    
    // increase the value with 10 size
    while()
    {
		int T =0, S=0, t=0, s=0;
		int e,e2;
		sort(threshold.begin(), threshold.end());
		int i;
        for(i=0; i<threshold.size(); i++)
        {
			for(int j=0; j<feature.size(); j++)
			{
				if(sampe[j] >1)
					T += feature[j];
				if(feature[j]<threshold[i] && sample[j] > 1)
					S += feature[j];
				if(sampe[j] <1)
					T += feature[j];
				if(feature[j]<threshold[i] && sample[j] < 1)
					S += feature[j];
			}
			e = min(S+(t-s), s+(T-S));
			if(i!=0 && e>e2)
			{
				i--;
				break;
			}
			e=e2;
        }
		
    }
    return threshold[i];
}

