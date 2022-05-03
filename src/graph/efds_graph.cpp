#include "efds_graph.h"

#include "txt_img_read.h"
#include "../actors/classifier.h"
#include "../actors/imageSubwindow.h"
#include "../actors/integrateImage.h"
#include "../actors/file_write_results.h"

#include <string>

using namespace std;

// constructor
efds_graph::efds_graph(vector<vector<WeakClassifier>> classifiers, vector<vector<float>> weights, 
        string imageDir, vector<int> imageIndices, 
        string output) {

    this->imageDir = imageDir;
    this->imageIndices = imageIndices;

    /* Initialize fifos to have a size of a pointer. */
    int token_size = sizeof(imageSubwindow *image);

    for (int fifo_idx = 0; fifo_idx < FIFO_COUNT; fifo_idx++) {
        fifos.push_back((welt_c_fifo_pointer) welt_c_fifo_new(BUFFER_CAPACITY,
                token_size, fifo_idx));
    }

    /***************************************************************************
    Create actors in the actors vector and put descriptions
    for each actor in the descriptions vector.
    ***************************************************************************/
    actors.push_back(new txt_img_read(fifos[FIFO_TIR_II], in_img_file, numRows, numCols, 0));
    descriptors.push_back((char*)"actor txt img read");

    actors.push_back(new integrateImage(fifos[FIFO_TIR_II], fifos[FIFO_II_CLAS]));
    descriptors.push_back((char*)"actor integrate image");

    int fifoIndex = FIFO_II_CLAS;
    this->numClassifierActors = min(classifiers.size(), MAX_CLASSIFIERS);
    for (int i = 0; i < numClassifierActors; i++) {
        actors.push_back(new classifier(fifos[fifoIndex], fifos[fifoIndex + 1],
                classifiers[i], weights[i]));
        descriptors.push_back((char*)"actor strong classifier");
        fifoIndex++;
    }

    actors.push_back(new file_write_results(fifos[fifoIndex], output));
    descriptors.push_back((char*)"actor file write");

    /* following two members are initialized but never used */
    actor_count = ACTOR_COUNT;
    fifo_count = FIFO_COUNT;
}

void efds_graph::scheduler() {
    // Get reference to image read actor
    txt_img_read &imageRead = actors[ACTOR_TXT_IMG_READ];

    // Iterate through all the images
    string imageFileName;
    for (auto &imageIndex: this->imageIndices) {
        imageFileName = this->imageDir + to_string(imageIndex);
        imageRead.setFileName(imageFileName);

        if (imageRead.enable()) {
            imageRead.invoke();
        }

        // Integrate Image, Run through Classifiers, and write results
        for (int i = 0; i < numClassifierActors + 2; i++) {
            if (actors[ACTOR_INTEGR_IMG + i].enable()) {
                actors[ACTOR_INTEGR_IMG + i].invoke();
            }
        }
    }
}

efds_graph::~efds_graph() {
    cout << "delete efds graph" << endl;
}
