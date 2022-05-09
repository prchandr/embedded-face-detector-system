#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <math.h>

#define TAG "efds_train::"

using namespace std;

// Function to compare pairs of classifications for sorting
bool compareClassifications(pair<bool, int> &lhs, pair<bool, int> &rhs) {
	return lhs.second > rhs.second;
}

/*

Function to find optimal threshold and weighted error for weak classifier, 
given feature results and image weights. 

Returns a vector of <threshold, polarity, weighted error>.

*/
vector<float> trainWeakClassifier(vector<int> resultSumsFace, vector<int> resultSumsNonFace,
								vector<float> weightsFace, vector<float> weightsNonFace) {
	// Vector to hold results
	vector<float> result;
	
	// Ensure input vectors are the same
	if (resultSumsFace.size() != weightsFace.size() || resultSumsNonFace.size() != weightsNonFace.size()) {
		cerr << TAG << "trainWeakClassifier Error: Input arrays are of different length\n";
		return result;
	}
	
	// Merge vectors into one vector of pairs
	float weightedSum = 0, totalWeightFace = 0, totalWeightNonFace = 0;
	vector<pair<bool, int>> classifications;

	for (int i = 0; i < resultSumsFace.size(); i++) {
		totalWeightFace += weightsFace[i];
		classifications.push_back(make_pair(true, resultSumsFace[i]));
	}

	for (int i = 0; i < resultSumsNonFace.size(); i++) {
		totalWeightFace += weightsNonFace[i];
		classifications.push_back(make_pair(false, resultSumsNonFace[i]));
	}

	// Sort classifications based on the resultSum
	sort(classifications.begin(), classifications.end(), compareClassifications);

	// Find optimal values
	int leftNumFace = 0, leftNumNonFace = 0;
	float leftWeightFace = 0, leftWeightNonFace = 0;
	int optimalThreshold = 0, polarity = 1;
	float minError = totalWeightFace + totalWeightNonFace;
	float error;

	// Iterate through all possible thresholds
	for (int i = 0; i < classifications.size(); i++) {
		error = min((leftWeightNonFace + (totalWeightFace - leftWeightFace)), 
					(leftWeightFace + (totalWeightNonFace - leftWeightNonFace)));

		// Adjust left weights depending on if the sample is a face or non-fae
		if (classifications[i].first) {
			leftNumFace++;
			leftWeightFace += classifications[i].second;
		} else {
			leftNumNonFace++;
			leftWeightNonFace += classifications[i].second;
		}

		// Update values if this is the lowest error so far
		if (error < minError) {
			// If there are more faces than nonfaces to the left of this threshold, set the polarity to -1
			if (leftNumFace < leftNumNonFace) {
				polarity = -1;
			} else {
				polarity = 1;
			}

			optimalThreshold = classifications[i].second;
			minError = error;
		}
	}

	// Write optimal values to result vector 
	result.push_back(static_cast<float>(optimalThreshold));
	result.push_back(static_cast<float>(polarity));
	result.push_back(minError);

	return result;
}

/*

Helper function that normalizes two vectors.

*/
void normalizeVectors(vector<float> &weightsFace, vector<float> &weightsNonFace) {
	float sumWeights;
	sumWeights = 0;
    for (auto weight : weightsFace) {
    	sumWeights += weight;
    }
    for (auto weight : weightsNonFace) {
    	sumWeights += weight;
    }
    for (auto &weight : weightsFace) {
    	weight /= sumWeights;
    }

    for (auto &weight : weightsNonFace) {
    	weight /= sumWeights;
    }
}


/* 

Main driver program for AdaBoost

*/
int main (int argc, char *argv[]) {
	// Arguments Declaration
	string weakClassifiersDir, weakClassifiersIndexFile, resultSumsDir, strongClassifierFile;
	int iterations;

	// Check program usage
	const int arg_count = 5;
    if (argc != arg_count) {
		cerr << TAG << "main() Error: arg count invalid. Usage: ./efds_train.exe weakClassifiersDir weakClassifiersIndexFile resultSumsDir strongClassifierFile iterations\n";
        return 1;
    }

    // Read in arguments
    int i = 0;
    weakClassifiersDir = argv[++i];
    weakClassifiersIndexFile = argv[++i];
    resultSumsDir = argv[++i];
    strongClassifierFile = argv[++i];
    iterations = stoi(argv[++i]);

    // Reads in weak classifiers indices from file
    ifstream weakClassifiersIndexFileStream(weakClassifiersIndexFile);
    if (!weakClassifiersIndexFileStream.is_open()) {
		cerr << TAG << "main() Error: can't open weak classifiers file: " << weakClassifiersIndexFile << "\n";
		return 1; 
	}

	vector<int> weakClassifierIndices;
	int classifierIdx;
	while (weakClassifiersIndexFileStream >> classifierIdx) {
		weakClassifierIndices.push_back(classifierIdx);
	}

    // Read in resultSums for each weak classifier. Each element is a pair of face and nonface results, in that order. 
    // Sorry for the confusing variable names.
    vector<pair<vector<int>, vector<int>>> resultSums;
    ifstream resultSumFaceStream, resultSumNonFaceStream;
    string resultSumFilename;
    vector<int> resultSumFace, resultSumNonFace;
    int resultSum;

    for (auto classifierIdx : weakClassifierIndices) {
    	resultSumFilename = to_string(classifierIdx) + ".txt";

    	// Read in resultSum files for face
    	resultSumFaceStream.open(resultSumsDir + "face_" + resultSumFilename);
    	if (!resultSumFaceStream.is_open()) {
			cerr << TAG << "main() Error: can't open resultSumFace file: " << resultSumsDir << "face_" << resultSumFilename << "\n";
			return 1; 
		}

		while (resultSumFaceStream >> resultSum) {
			resultSumFace.push_back(resultSum);
		}
    
    	resultSumNonFaceStream.open(resultSumsDir + "nonface_" + resultSumFilename);
    	if (!resultSumNonFaceStream.is_open()) {
			cerr << TAG << "main() Error: can't open resultSumNonFace file: " << resultSumsDir << "nonface_" << resultSumFilename << "\n";
			return 1; 
		}

		while (resultSumNonFaceStream >> resultSum) {
			resultSumNonFace.push_back(resultSum);
		}

    	// Push back the new pair of vectors
		resultSums.push_back(make_pair(resultSumFace, resultSumNonFace));

    	// Close file streams for next iteration and clear vectors
		resultSumFaceStream.close();
    	resultSumFaceStream.close();
    	resultSumFace.clear();
    	resultSumNonFace.clear();

    }

    // Initialize weights for images, list of weak classifiers, adaboosting
    int numFaces = resultSums[0].first.size(), numNonFaces = resultSums[0].second.size();
    vector<float> weightsFace(numFaces, 1.0 / numFaces), weightsNonFace(numNonFaces, 1.0 / numNonFaces);
    vector<int> trainedClassifiers(iterations), trainedThresholds(iterations), trainedPolarities(iterations);
    vector<float> trainedWeights(iterations);
    
    int lowestErrorIdx = -1, optimalThreshold = 0, optimalPolarity = 0;
    float error = 0, lowestError = numeric_limits<float>::max(), beta = 0;
    vector<float> result;

    // Repeat for each classifier in strong classifier
    for (int i = 0; i < iterations; i++) {
    	// Normalize weights
    	normalizeVectors(weightsFace, weightsNonFace);

    	// For each feature (not already selected)
    	for (int weakClassifierIdx : weakClassifierIndices) {
    		// Get optimal threshold, polarity, weighted error for this feature, based on training data
    		result = trainWeakClassifier(resultSums[weakClassifierIdx].first, resultSums[weakClassifierIdx].second,
								 weightsFace, weightsNonFace);

    		if (result.empty()) {
    			cerr << TAG << "main() Error: empty result from trainWeakClassifier.\n";
    			return 1;
    		}

    		// Store results for lowest error
    		error = result[2];
    		if (error < lowestError) {
    			lowestErrorIdx = weakClassifierIdx;
    			optimalThreshold = static_cast<int>(result[0]);
    			optimalPolarity = static_cast<int>(result[1]);
    			lowestError = error;
    		}
		}

    	// Using lowest error, update weights
    	beta = lowestError / (1 - lowestError);

    	for (int j = 0; j < numFaces; j++) {
    		// If face was misclassified, adjust weight of image
    		if (optimalPolarity * resultSums[lowestErrorIdx].first[j] < optimalPolarity * optimalThreshold) {
    			weightsFace[j] *= beta;
    		}
    	}

    	for (int j = 0; j < numNonFaces; j++) {
    		// If nonface was misclassified, adjust weight of image
    		if (optimalPolarity * resultSums[lowestErrorIdx].second[j] >= optimalPolarity * optimalThreshold) {
    			weightsNonFace[j] *= beta;
    		}
    	}

    	// Store trained weak classifier and weight to vector for strong classifier
    	trainedClassifiers[i] = lowestErrorIdx;
    	trainedThresholds[i] = optimalThreshold;
    	trainedPolarities[i] = optimalPolarity;
    	trainedWeights[i] = log(1 / beta);

		// Remove selected weak classifier from inputs
		weakClassifierIndices.erase(remove(weakClassifierIndices.begin(), weakClassifierIndices.end(), lowestErrorIdx), weakClassifierIndices.end());

    	// Reset values for next iteration
    	lowestErrorIdx = -1; 
    	lowestError = numeric_limits<float>::max();
    }



    // Make strong classifier file using trained values.
    ofstream strongClassifierStream(strongClassifierFile);
	if (!strongClassifierStream.is_open()) {
		cerr << TAG << "main() Error: can't open strong classifiers file: " << strongClassifierFile << "\n";
		return 1; 
	}

	string weakClassifierFilename;
	ifstream weakClassifierStream;
	int featureType, width, height, startRow, startCol;
	for (int i = 0; i < iterations; i++) {
		weakClassifierFilename = weakClassifiersDir + "wc_" + to_string(trainedClassifiers[i]) + ".txt";

		// Read in feature data from weak classifier file
		weakClassifierStream.open(weakClassifierFilename);

		if (!weakClassifierStream.is_open()) {
			cerr << TAG << "main() Error: can't open weak file: " << weakClassifierFilename << "\n";
			return 1; 
		}

		weakClassifierStream >> featureType >> width >> height >> startRow >> startCol;
		weakClassifierStream.close();


		// Write feature data, threshold, parity, and weight to strong classifier file
		strongClassifierStream << featureType << " " << width << " " << height << "\n";
		strongClassifierStream << startRow << " " << startCol << "\n";
		strongClassifierStream << trainedThresholds[i] << " " << trainedPolarities[i] << "\n";
		strongClassifierStream << trainedWeights[i] << "\n\n";
	}

}

