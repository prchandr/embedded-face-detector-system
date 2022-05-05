#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../../src/utils/FeatureType.h"
#include "../../src/utils/WeakClassifier.h"
#include "../../src/graph/efds_graph.h"

using namespace std;

istream &readClassifier(istream &input, WeakClassifier &classifier) {
	FeatureType featureType;
	int featureInt, width, height, startRow, startCol, polarity, threshold;
	input >> featureInt >> width >> height >> startRow >> startCol >> polarity >> threshold;

	switch (featureInt) {
		case 0:
			featureType = VERTICAL_EDGE;
			break;
		case 1:
			featureType = HORIZONTAL_EDGE;
			break;
		case 2:
			featureType = VERTICAL_LINE;
			break;
		case 3:
			featureType = HORIZONTAL_LINE;
			break;
		case 4:
			featureType = FOUR_RECTANGLE;
			break;
		default:
			cerr << "Error: Feature Type is invalid.\n";
			break;
	}

	classifier.setFeatureType(featureType);
	classifier.setDimensions(width, height);
	classifier.setStartCoords(startRow, startCol);
	classifier.setClassifyParams(polarity, threshold);
	return input;
}

int main(int argc, char **argv) {
    string classifierDir, classifierSelect, imageDir, imageSelect, output;
	int arg_count = 6; /* driver classifierDirectory classifierSelect imageDirectory imageSelect outputFile */

    /* Check program usage. */
    if (argc != arg_count) {
		cerr << "efds_graph_driver.exe error: arg count invalid\n";
        return 1;
    }

    /* Open the input and output file(s). */
    int i = 0;
	classifierDir = argv[++i];
    classifierSelect = argv[++i];
    imageDir = argv[++i];
	imageSelect = argv[++i];
	output = argv[++i];

	/* Configure classifier actors */
	ifstream classifierConfigInput(classifierSelect);
	if (!classifierConfigInput.is_open()) {
		cerr << "efds_graph_driver.exe error: Classifier config file could not be opened.\n";
		return 1; 
	}

	/* Read in classifiers and weights */
	// Variables for all strong classifiers
	int classifierIndex;
	string strongFileName;
	vector<vector<WeakClassifier>> classifiers;
	vector<vector<float>> weights;

	// Variables for individual classifiers
	ifstream classifierInput;
	vector<WeakClassifier> strongClassifier;
	vector<float> strongWeights;	
	WeakClassifier weakClassifier;
	float weight;

	while (classifierConfigInput >> classifierIndex) {
		// Obtain filenames for strong classifier file
		strongFileName = classifierDir + "classifier_" + to_string(classifierIndex) + ".txt";
		cout << "Reading from file: "  << strongFileName << endl;

		// Get all weak classifiers and weights in strong classifier file
		classifierInput.open(strongFileName);

		while (readClassifier(classifierInput, weakClassifier)) {
			classifierInput >> weight;
			strongClassifier.push_back(weakClassifier);
			strongWeights.push_back(weight);
		}
		
		// Append classifiers and weights to the vector
		classifiers.push_back(strongClassifier);
		
		// Close and reset input file
		classifierInput.close();
		classifierInput.clear();
	}

	// Get all image names and store in a vector
	ifstream imageIndexInput(imageSelect);
	if (!imageIndexInput.is_open()) {
		cerr << "efds_graph_driver.exe error: Image index file could not be opened.\n";
		return 1;
	}

	vector<int> imageIndices;
	int imageIndex;
	while (imageIndexInput >> imageIndex) {
		imageIndices.push_back(imageIndex);
	}

    efds_graph *efds_graph_instance = new efds_graph(classifiers, weights, imageDir, imageIndices, output);
    /* Execute the graph. */
    efds_graph_instance->scheduler();

    /* Normal termination. */
    return 0;
}





