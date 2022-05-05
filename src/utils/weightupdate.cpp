#include "weightupdate.h"


weightupdate::weightupdate(vector<vector<vector<int>>> img) {
	for(int i=0; i<index ; i++)
	{
		if(vector[i] == 1)
		{
			y1++;
		}
		else if(vector[i] == -1)
		{	
			y2++;
		}
	}
	for(int i=0; i<index ; i++)
	{
		if(vector[i] == 1)
		{
			weight[i] = 1/y1;
		}
		else if(vector[i] == -1)
		{	
			weight[i] = 1/y2;
		}
	}
	//initial weight value
}


float weightupdate::normalize(float weight){
	
	for(int j=0; i<index; i++)
	{
		total_weight += weight[j];
	}
	for(int i=0; i<index; i++)
	{
		weight[i] = weight[i]/total_weight;		
	}
	//weight nomarlize
}
	
float weightupdate::update(float weight){
	
	WeakClassifier Weak.WeakClassifier(feature, width, height, startRow, startCol, polarity, threshold);
	for(int i=0; i<index; i++)
	{
		e[i] = abs(Weak.classifyImage - vector[i])
		error += weight[i]*abs(Weak.classifyImage - vector[i]);
	}
	beta = error/(1-error);
	weight[i] = weight[i]*pow(beta,1-e);
	
	//updating the weight
}



