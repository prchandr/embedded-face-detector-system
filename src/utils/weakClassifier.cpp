#include "weakClassifier.h"

using namespace std;

weakClassifier::weakClassifier(featureType feature, int width, int height,
				int startRow, int startCol,
				int polarity, float threshold) {
	void setFeatureType(featureType feature);
	{
		this->feature = feature;
	}
	void setDimensions(int width, int height)
	{
		this->width = width;
		this->height = height;
	}
	void setStartCoord(int startRow, int startCol)
	{
		this->startRow = startRow;
		this->startCol = startCol;
	}
	void setClassifyParams(int polarity, float threshold)
	{
		this->polarity = polarity;
		this->threshold = threshold;
	}
}


bool weakClassifier::classifyImage(ImageSubwindow integral_image){
	int pos, neg;
	switch(feature)
	{
		case VERTICAL_EDGE:
		{
			if(startRow!=0 && startCol!=0)
			{
				neg = img[startRow-1][startCol-1] + img[startRow+ height/2-1][startCol + width - 1]
						- img[startRow + height/2-1][startCol-1] - img[startRow-1][startCol + width-1];
				pos = img[startRow-1 + height/2-1][startCol-1] + img[startRow+ height-1][startCol + width-1]
						- img[startRow + height-1][startCol-1] - img[startRow+height/2-1][startCol + width-1];
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
				neg = img[startRow+ height/2-1][startCol + width - 1]
						- img[startRow-1][startCol + width-1];
				pos = img[startRow+ height-1][startCol + width-1]
						- img[startRow+height/2-1][startCol + width-1];
			}
			else if(startRow == 0 && startCol == 0)
			{
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
		default;
			break;
	}
	
	return (polarity * (pos-neg) > polarity*threshold);
}

istream &read(istream &input, WeakClassifier &classifier) {
	input >> classifier.featureType >> classifier.width >> classifier.height >> classifier.startRow >> classifier.startCol >> classifier.polarity >> classifier.threshold;
	return input;
}
