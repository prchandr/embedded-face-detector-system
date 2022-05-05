#include "WeakClassifier.h"
#include "ImageSubwindow.h"

#include <vector>
#include "FeatureType.h"

using namespace std;

WeakClassifier::WeakClassifier() {
	this->feature = VERTICAL_EDGE;
	this->width = 0;
	this->height = 0;
	this->startRow = 0;
	this->startCol = 0;
	this->threshold = 0;
	this->polarity = 0;
}

WeakClassifier::WeakClassifier(FeatureType feature, int width, int height,
				int startRow, int startCol, int polarity, int threshold) {
	this->feature = feature;
	this->width = width;
	this->height = height;
	this->startRow = startRow;
	this->startCol = startCol;
	this->threshold = threshold;
	this->polarity = polarity;
}

void WeakClassifier::setFeatureType(FeatureType feature) {
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
		case HORIZONTAL_EDGE:
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
		case VERTICAL_LINE:
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
		case HORIZONTAL_LINE:
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
		case FOUR_RECTANGLE:
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
	
	return (polarity * (pos-neg) > polarity * threshold);
}