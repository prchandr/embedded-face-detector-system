
#include "ImageSubwindow.h"
#include "WeakClassifier.h"
#include <vector>

using namespace std;

WeakClassifier::WeakClassifier(featureType feature, int width, int height,
				int startRow, int startCol, int polarity, int threshold) {
	this->feature = feature;
	this->width = width;
	this->height = height;
	this->startRow = startRow;
	this->startCol = startCol;
	this->threshold = threshold;
	this->polarity = polarity;
}

void WeakClassifier::setFeatureType(featureType feature) {
	this->feature = feature;
}

void WeakClassifier::setDimensions(int width, int height) {
	this->width = width;
	this->height = height;
}

void WeakClassifier::setStartCoords(int startRow, int startCol) {
	this->startRow = startRow;
	this->startCol = startCol;
}
	
void WeakClassifier::setClassifyParams(int polarity, int threshold) {
	this->polarity = polarity;
	this->threshold = threshold;
}

bool WeakClassifier::classifyImage(ImageSubwindow integral_image){
	int pos, neg;
    vector<vector<int>> &img = *integral_image.image;
	switch(feature)
	{
		case VERTICAL_EDGE: //feature type 1
		{
			if(startRow!=0 && startCol!=0)
			{
				neg = img[startRow-1][startCol-1] + img[startRow+ height/2-1][startCol + width - 1]
						- img[startRow + height/2-1][startCol-1] - img[startRow-1][startCol + width-1];
				pos = img[startRow-1 + height/2-1][startCol-1] + img[startRow+ height-1][startCol + width-1]
						- img[startRow + height-1][startCol-1] - img[startRow+height/2-1][startCol + width-1];
				//calculate positive and negative values based on integrated image.
			}
			else if(startRow == 0 && startCol!=0) 
			{
				neg = img[startRow+ height/2-1][startCol + width - 1]
						- img[startRow + height/2-1][startCol-1];
				pos = img[startRow-1 + height/2-1][startCol-1] + img[startRow+ height-1][startCol + width-1]
						- img[startRow + height-1][startCol-1] - img[startRow+height/2-1][startCol + width-1];
			}
			if(startRow!=0 && startCol == 0)
			{

	

	switch(feature) {
		case VERTICAL_EDGE: {
			if (startRow != 0 && startCol != 0) {
				neg = img[startRow - 1][startCol - 1] 
					+ img[startRow + height/2 - 1][startCol + width - 1]
					- img[startRow + height/2 - 1][startCol - 1]
					- img[startRow - 1][startCol + width - 1];

				pos = img[startRow - 1 + height/2 - 1][startCol - 1]
					+ img[startRow + height - 1][startCol + width - 1]
					- img[startRow + height - 1][startCol - 1]
					- img[startRow + height/2 - 1][startCol + width - 1];
			} else if(startRow == 0 && startCol != 0) {
				neg = img[startRow+ height/2 - 1][startCol + width - 1]
					- img[startRow + height/2 - 1][startCol - 1];
				pos = img[startRow - 1 + height/2 - 1][startCol - 1]
					+ img[startRow + height - 1][startCol + width - 1]
					- img[startRow + height - 1][startCol - 1]
					- img[startRow + height/2 - 1][startCol + width - 1];
			}
			
			if (startRow != 0 && startCol == 0) {

				neg = img[startRow+ height/2-1][startCol + width - 1]
						- img[startRow-1][startCol + width-1];
				pos = img[startRow+ height-1][startCol + width-1]
						- img[startRow+height/2-1][startCol + width-1];
			}

			else if(startRow == 0 && startCol == 0) {
				neg = img[startRow+ height/2-1][startCol + width - 1];
				pos = img[startRow+ height-1][startCol + width-1]
						- img[startRow+height/2-1][startCol + width-1];
			}

			break;
		}
		case HORIZONTAL_EDGE: //feature type 2
		{
			if(startRow!=0 && startCol!=0)
			{
				neg = img[startRow-1][startCol-width/2-1] + img[startRow+ height-1][startCol + width - 1]
						- img[startRow + height-1][startCol + width/2-1] - img[startRow-1][startCol + width-1];
				pos = img[startRow-1][startCol-1] + img[startRow+ height-1][startCol + width/2-1]
						- img[startRow + height-1][startCol-1] - img[startRow-1][startCol + width/2-1];
			}
			else if(startRow == 0 && startCol!=0)
			{
				neg = img[startRow+ height-1][startCol + width - 1]
						- img[startRow + height-1][startCol + width/2-1];
				pos = img[startRow+ height-1][startCol + width/2-1]
						- img[startRow + height-1][startCol-1];
			}
			if(startRow!=0 && startCol==0)
			{
				neg = img[startRow-1][startCol-width/2-1] + img[startRow+ height-1][startCol + width - 1]
						- img[startRow + height-1][startCol + width/2-1] - img[startRow-1][startCol + width-1];
				pos = img[startRow+ height-1][startCol + width/2-1]
						- img[startRow-1][startCol + width/2-1];
			}
			else if(startRow == 0 && startCol == 0)
			{
				neg =img[startRow+ height-1][startCol + width - 1]
						- img[startRow + height-1][startCol + width/2-1];
				pos = img[startRow+ height-1][startCol + width/2-1];
			}
			break;
		}
		case VERTICAL_LINE: //feature type 3
		{
			if(startRow!=0 && startCol!=0)
			{
				neg = img[startRow-1][startCol-1] + img[startRow+ height/3-1][startCol + width - 1]
						- img[startRow + height/3-1][startCol-1] - img[startRow-1][startCol + width-1]
						+img[startRow+ 2*height/3-1][startCol-1] + img[startRow+ 2*height/3-1][startCol + width - 1]
						- img[startRow + height/3-1][startCol-1] - img[startRow+2*height/3-1][startCol + width-1];
				pos = img[startRow + height/3-1][startCol-1] + img[startRow+ 2*height/3-1][startCol + width-1]
						- img[startRow + 2*height/3-1][startCol-1] - img[startRow+height/3-1][startCol + width-1];
			}
			else if(startRow == 0 && startCol!=0)
			{
				neg = 	img[startRow+ height/3-1][startCol + width - 1]
						- img[startRow + height/3-1][startCol-1]
						+img[startRow+ 2*height/3-1][startCol-1] + img[startRow+ 2*height/3-1][startCol + width - 1]
						- img[startRow + height/3-1][startCol-1] - img[startRow+2*height/3-1][startCol + width-1];
				pos = img[startRow + height/3-1][startCol-1] + img[startRow+ 2*height/3-1][startCol + width-1]
						- img[startRow + 2*height/3-1][startCol-1] - img[startRow+height/3-1][startCol + width-1];
			}
			else if(startRow != 0 && startCol==0)
			{
				neg = img[startRow+ height/3-1][startCol + width - 1]
						- img[startRow-1][startCol + width-1]
						+ img[startRow+ 2*height/3-1][startCol + width - 1]
						- img[startRow+2*height/3-1][startCol + width-1];
				pos = img[startRow+ 2*height/3-1][startCol + width-1]
						- img[startRow+height/3-1][startCol + width-1];
			}
			else if(startRow == 0 && startCol == 0)
			{
				neg = img[startRow+ height/3-1][startCol + width - 1]
						+ img[startRow+ 2*height/3-1][startCol + width - 1]
						- img[startRow+2*height/3-1][startCol + width-1];
				pos = img[startRow+ 2*height/3-1][startCol + width-1]
						- img[startRow+height/3-1][startCol + width-1];
			}
			break;
		}
		case HORIZONTAL_LINE: //feature type 4
		{
			if(startRow!=0 && startCol!=0)
			{
				neg = img[startRow-1][startCol-1] + img[startRow+ height-1][startCol + width/3 - 1]
						- img[startRow + height-1][startCol-1] - img[startRow-1][startCol + width/3-1]
						+ img[startRow-1][startCol + 2*width/3 - 1] + img[startRow+ height-1][startCol + width - 1]
						- img[startRow + height-1][startCol+ 2*width/3 - 1] - img[startRow-1][startCol + width - 1];
				pos = img[startRow-1][startCol + width/3-1] + img[startRow + height-1][startCol+ 2*width/3 - 1]
						- img[startRow+ height-1][startCol + width/3 - 1] - img[startRow-1][startCol + 2*width/3 - 1];
			}
			else if(startRow == 0 && startCol != 0)
			{
				neg = img[startRow+ height-1][startCol + width/3 - 1]
						- img[startRow + height-1][startCol-1]
						+ img[startRow+ height-1][startCol + width - 1]
						- img[startRow + height-1][startCol+ 2*width/3 - 1];
				pos = img[startRow + height-1][startCol+ 2*width/3 - 1]
						- img[startRow+ height-1][startCol + width/3 - 1];
			}
			else if(startRow != 0 && startCol == 0)
			{
				neg = img[startRow+ height-1][startCol + width/3 - 1]
						- img[startRow-1][startCol + width/3-1]
						+ img[startRow-1][startCol + 2*width/3 - 1] + img[startRow+ height-1][startCol + width - 1]
						- img[startRow + height-1][startCol+ 2*width/3 - 1] - img[startRow-1][startCol + width - 1];
				pos = img[startRow-1][startCol + width/3-1] + img[startRow + height-1][startCol+ 2*width/3 - 1]
						- img[startRow+ height-1][startCol + width/3 - 1] - img[startRow-1][startCol + 2*width/3 - 1];
			}
			else if(startRow == 0 && startCol == 0)
			{
				neg = img[startRow+ height-1][startCol + width/3 - 1]
						+ img[startRow+ height-1][startCol + width - 1]
						- img[startRow + height-1][startCol+ 2*width/3 - 1];
				pos = img[startRow + height-1][startCol+ 2*width/3 - 1]
						- img[startRow+ height-1][startCol + width/3 - 1];
			}
			break;
		}
		case FOUR_RECTANGLE: //feature type 5
		{
			if(startRow!=0 && startCol!=0)
			{
				neg = 	img[startRow-1][startCol+width/2 -1] + img[startRow+height/2-1][startCol + width-1]
						- img[startRow + height/2-1][startCol+ width/2-1] - img[startRow-1][startCol + width-1]
						+ img[startRow+ height/2-1][startCol- 1] + img[startRow+ height-1][startCol+width/2-1]
						- img[startRow + height-1][startCol-1] - img[startRow + height/2-1][startCol+ width/2-1];
				pos = 	img[startRow-1][startCol-1] + img[startRow + height/2-1][startCol+ width/2-1]
						- img[startRow+ height/2-1][startCol- 1] - img[startRow-1][startCol + width/2 - 1]
						+ img[startRow+height/2-1][startCol+width/2-1] + img[startRow + height-1][startCol+ width-1]
						- img[startRow+ height-1][startCol+width/2-1] - img[startRow+height/2-1][startCol + width - 1];
			}
			else if(startRow == 0 && startCol != 0)
			{
				neg =	img[startRow+height/2-1][startCol + width-1]
						- img[startRow + height/2-1][startCol+ width/2-1]
						+ img[startRow+ height/2-1][startCol- 1] + img[startRow+ height-1][startCol+width/2-1]
						- img[startRow + height-1][startCol-1] - img[startRow + height/2-1][startCol+ width/2-1];
				pos = 	img[startRow + height/2-1][startCol+ width/2-1]
						- img[startRow+ height/2-1][startCol- 1]
						+ img[startRow+height/2-1][startCol+width/2-1] + img[startRow + height-1][startCol+ width-1]
						- img[startRow+ height-1][startCol+width/2-1] - img[startRow+height/2-1][startCol + width - 1];
			}
			else if(startRow != 0 && startCol == 0)
			{
				neg = 	img[startRow-1][startCol+width/2 -1] + img[startRow+height/2-1][startCol + width-1]
						- img[startRow + height/2-1][startCol+ width/2-1] - img[startRow-1][startCol + width-1]
						+ img[startRow+ height-1][startCol+width/2-1]
						- img[startRow + height/2-1][startCol+ width/2-1];
				pos = 	img[startRow + height/2-1][startCol+ width/2-1]
						- img[startRow-1][startCol + width/2 - 1]
						+ img[startRow+height/2-1][startCol+width/2-1] + img[startRow + height-1][startCol+ width-1]
						- img[startRow+ height-1][startCol+width/2-1] - img[startRow+height/2-1][startCol + width - 1];
			}
			else if(startRow == 0 && startCol == 0)
			{
				neg = 	img[startRow+height/2-1][startCol + width-1]
						- img[startRow + height/2-1][startCol+ width/2-1]
						+ img[startRow+ height-1][startCol+width/2-1]
						- img[startRow + height/2-1][startCol+ width/2-1];
				pos = 	img[startRow + height/2-1][startCol+ width/2-1]
						+ img[startRow+height/2-1][startCol+width/2-1] + img[startRow + height-1][startCol+ width-1]
						- img[startRow+ height-1][startCol+width/2-1] - img[startRow+height/2-1][startCol + width - 1];
			}
			break;
		}
		default:
			break;
	}

	if(pos-neg < 0)
		polarity = -1;
	else
		polarity = 1;
	//update the polarity based on feature values
	return (polarity * (pos-neg) > polarity*threshold);
}

