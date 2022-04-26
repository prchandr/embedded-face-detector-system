#include <fstream>
#include <string>
#include <vector>

#include "../../src/actors/weakClassifier.h"
#include "../../src/graph/efds_graph.h"

using namespace std;

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
	ifstream classifiersInput(classifierSelect);
	if (!classifiersInput.is_open()) {
		cerr << "efds_graph_driver.exe error: Classifier config file could not be opened.\n";
		return 1; 
	}

	string strongFileName;
	vector<vector<WeakClassifier>> classifiers;
	vector<vector<int>> weights;
	while (classifierConfigInput >> classifierIndex) {
		// Obtain filenames for strong classifier file
		strongFileName = classifierDir + "sc_" + to_string(classifierIndex) + ".txt";
		cout << strongFileName << endl;

		// Get all weak classifiers and weights in strong classifier file

		vector<WeakClassifier> strongClassifier;
		vector<int> strongWeights;	
	}

	// Get all image names and store in a vector
	
	


	return;


    auto* efds_graph = new efds_graph(classifiers, weights, imageDir, imageNames, output);
    /* Execute the graph. */
    efds_graph->scheduler();

    /* Normal termination. */
    return 0;
}





