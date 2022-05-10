#include "WeakClassifier.h"

#include "ImageSubwindow.h"
#include "FeatureType.h"

#include <iostream>
#include <vector>

#define TAG "WeakClassifier::"

using namespace std;

/* Constructors */

// Empty constructor, default values
WeakClassifier::WeakClassifier() {
	this->feature = VERTICAL_EDGE;
	this->width = 0;
	this->height = 0;
	this->startRow = 0;
	this->startCol = 0;
	this->threshold = 0;
	this->polarity = 0;
	this->resultSum = 0;
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
	this->resultSum = 0;
}

/* Classifies a given integral image based on the configured weak classifier */
bool WeakClassifier::classifyImage(ImageSubwindow integral_image) {
	cout << TAG << "classifyImage() ENTER\n";

	int pos, neg;
    vector<vector<int>> &img = *integral_image.image;

	switch(feature) {
		case VERTICAL_EDGE: { //feature type 1
			if (startRow != 0 && startCol != 0) {
				neg = img[startRow - 1][startCol - 1] 
					+ img[startRow + height/2 - 1][startCol + width - 1]
					- img[startRow + height/2 - 1][startCol - 1]
					- img[startRow - 1][startCol + width - 1];

				pos = img[startRow + height/2 - 1][startCol - 1]
					+ img[startRow + height - 1][startCol + width - 1]
					- img[startRow + height - 1][startCol - 1]
					- img[startRow + height/2 - 1][startCol + width - 1];
			} 
			else if(startRow == 0 && startCol != 0) {
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
		case HORIZONTAL_EDGE: { //feature type 2
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
	this->resultSum = pos - neg;
	cout << TAG << "classifyImage() result: " << this->resultSum << '\n';
	cout << TAG << "classifyImage() EXIT\n";
	return (this->polarity * (this->resultSum) < (this->polarity * this->threshold));
}


/* Getters. (Most left unimplemented since they are unused) */
int WeakClassifier::getResultSum() {
	return this->resultSum;
}

/* Setters */
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


