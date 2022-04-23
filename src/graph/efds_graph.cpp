#include "efds_graph.h"

#include "txt_img_read.h"
#include "../actors/classifier.h"
#include "../actors/imageSubwindow.h"
#include "../actors/integrateImage.h"

#include <string>
#include <fstream>

using namespace std;

// constructor
efds_graph::efds_graph(string classifierDir, string classifierConfig,
                        string imageDir, string imageConfig,
                        string outputFile) {
    
    /* Configure classifier actors */
	ifstream classifierConfigInput(classifierConfig);
	if (!classifierConfigInput.is_open()) {
		cerr << "Classifier config file could not be opened.\n";
		return 1; 
	}

	int classifierIndex = 0;
	string strongFileName;
	while (classifierConfigInput >> classifierIndex) {
		// Obtain filenames for strong classifier files
		strongFileName = classifierDir + "sc_" + to_string(classifierIndex) + ".txt";
		cout << strongFileName << endl;
	}
	return;


    /* Initialize fifos to have a size of a pointer. */
    int token_size = sizeof(imageSubwindow *image);

    for (int fifo_idx = 0; fifo_idx < FIFO_COUNT; fifo_idx++) {
        fifos.push_back((welt_c_fifo_pointer)welt_c_fifo_new(BUFFER_CAPACITY,
                token_size, fifo_idx));
    }

    /***************************************************************************
    Create actors in the actors vector and put descriptions
    for each actor in the descriptions vector.
    ***************************************************************************/
	actors.push_back(new txt_img_read(fifos[FIFO_TIR_CLAS], in_img_file, numRows, numCols, 0));
    descriptors.push_back((char*)"actor txt img read");

    actors.push_back(new image_rotate(fifos[FIFO_IMREAD_IMROT], fifos[FIFO_FILESRC_IMROT], fifos[FIFO_IMROT_IMWRITE]));
    descriptors.push_back((char*)"actor image rotate");

    actors.push_back(new txt_img_write(fifos[FIFO_IMROT_IMWRITE], out_img_file, 0));
    descriptors.push_back((char*)"actor img read");  

    /* following two members are initialized but never used */
    actor_count = ACTOR_COUNT;
    fifo_count = FIFO_COUNT;
}

void efds_graph::scheduler() {
    for (int i = 0; i < actor_count; i++){
        welt_cpp_util_guarded_execution(actors[i], descriptors[i]);
    }
}

efds_graph::~efds_graph() {
    cout << "delete efds graph" << endl;
}
