#include "efds_graph.h"

#include "txt_img_read.h"
#include "../actors/classifier.h"
#include "../actors/integrateImage.h"
#include "../actors/file_write_results.h"

#include "../utils/WeakClassifier.h"
#include "../utils/ImageSubwindow.h"

#include <iostream>
#include <string>

#define IMAGE_WIDTH     24
#define IMAGE_HEIGHT    24

#define IMAGE_FILENAME_LENGTH 4

#define TAG "efds_graph::"

using namespace std;

// constructor
efds_graph::efds_graph(vector<vector<WeakClassifier>> classifiers, vector<vector<float>> weights, 
        string imageDir, vector<int> imageIndices, 
        string output, string classifierResultOut = "") {
    cout << TAG << "efds_graph() ENTER\n";
    this->imageDir = imageDir;
    this->imageIndices = imageIndices;
    this->classifiersResultsFilename = classifierResultOut;

    /* Initialize fifos to have a size of a pointer. */
    int token_size = sizeof(ImageSubwindow*);

    for (int fifo_idx = 0; fifo_idx < FIFO_COUNT; fifo_idx++) {
        fifos.push_back((welt_c_fifo_pointer) welt_c_fifo_new(BUFFER_CAPACITY,
                token_size, fifo_idx));
    }

    /***************************************************************************
    Create actors in the actors vector and put descriptions
    for each actor in the descriptions vector.
    ***************************************************************************/
    char defaultFileName[] = "image0.txt";
    this->imageRead = new txt_img_read(fifos[FIFO_TIR_II], defaultFileName, IMAGE_WIDTH, IMAGE_HEIGHT, 0);
    actors.push_back(this->imageRead);
    descriptors.push_back((char*)"actor txt img read");

    actors.push_back(new integrateImage(fifos[FIFO_TIR_II], fifos[FIFO_II_CLAS]));
    descriptors.push_back((char*)"actor integrate image");

    int fifoIndex = FIFO_II_CLAS;
    this->numClassifierActors = min((int)classifiers.size(), MAX_CLASSIFIERS);

    cout << TAG << "efds_graph(): Number of Classifier Actors: " << numClassifierActors << "\n";

    if (!this->classifiersResultsFilename.empty()) {
        cout << TAG "efds_graph(): writing classifier results to file: " << this->classifiersResultsFilename << "\n";       
    }

    for (int i = 0; i < numClassifierActors; i++) {
        actors.push_back(new classifier(fifos[fifoIndex], fifos[fifoIndex + 1],
                classifiers[i], weights[i], this->classifiersResultsFilename));
        descriptors.push_back((char*)"actor strong classifier");
        fifoIndex++;
    }

    actors.push_back(new file_write_results(fifos[fifoIndex], output));
    descriptors.push_back((char*)"actor file write");

    /* following two members are initialized but never used */
    actor_count = ACTOR_COUNT;
    fifo_count = FIFO_COUNT;

    cout << TAG << "efds_graph() EXIT\n";
}

void efds_graph::scheduler() {
    cout << TAG << "scheduler() ENTER\n";

    // "Configure" classify actors
    for (int i = 1; i <= numClassifierActors; i++) {
        if (actors[ACTOR_INTEGR_IMG + i]->enable()) {
            actors[ACTOR_INTEGR_IMG + i]->invoke();
        }
    }


    // Iterate through all the images
    string imageFileName;
    for (auto &imageIndex: this->imageIndices) {
        // Get image index as string and zero pad it.
        string imageFile = to_string(imageIndex);
        imageFile.insert(imageFile.begin(), IMAGE_FILENAME_LENGTH - imageFile.length(), '0');
        imageFileName = this->imageDir + imageFile + ".txt";

        cout << TAG << "scheduler() imageFileName: " << imageFileName << "\n";
        imageRead->setFileName((char*) imageFileName.c_str());

        if (imageRead->enable()) {
            cout << TAG << "scheduler() imageRead enabled. Reading..\n";
            imageRead->invoke();
        }

        // Integrate Image
        if (actors[ACTOR_INTEGR_IMG]->enable()) {
            actors[ACTOR_INTEGR_IMG]->invoke();
        }

        // Run through Classifiers,
        for (int i = 1; i <= numClassifierActors; i++) {
            // Read, classify, and write result to next actor
            for (int j = 0; j < 3; j++) {
                if (actors[ACTOR_INTEGR_IMG + i]->enable()) {
                    actors[ACTOR_INTEGR_IMG + i]->invoke();
                } 
            }
        }

        // Write results
        if (actors[ACTOR_INTEGR_IMG + numClassifierActors + 1]->enable()) {
            actors[ACTOR_INTEGR_IMG + numClassifierActors + 1]->invoke();
        }

    }

    cout << TAG << "scheduler() EXIT\n";
}

efds_graph::~efds_graph() {
    cout << "delete efds graph\n";
}
