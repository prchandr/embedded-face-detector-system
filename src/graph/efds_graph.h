#ifndef efds_graph_h
#define efds_graph_h

extern "C" {
    #include "welt_c_basic.h"
    #include "welt_c_actor.h"
    #include "welt_c_fifo.h"
    #include "welt_c_graph.h"
    #include "welt_c_util.h"
}

#include "welt_cpp_graph.h"
#include "welt_cpp_util.h"

#include <string>

#include "txt_img_read.h"
#include "../utils/WeakClassifier.h"

#define BUFFER_CAPACITY 1024
#define MAX_CLASSIFIERS 32

/* An enumeration of the actors in this application. */
#define ACTOR_TXT_IMG_READ  0
#define ACTOR_INTEGR_IMG    1
#define ACTOR_FILE_WRITE    2  // Incorrect enumeration

/* An enumeration of the edges in this application. The naming convention
for the constants is FIFO_<source actor>_<sink actor>. */
#define FIFO_TIR_II     0
#define FIFO_II_CLAS    1

/* The total number of actors in the application. */
#define ACTOR_COUNT     3 + MAX_CLASSIFIERS
#define FIFO_COUNT      5 + MAX_CLASSIFIERS - 1

/*******************************************************************************
TYPE DEFINITIONS
*******************************************************************************/

class efds_graph : public welt_cpp_graph{
public:
    efds_graph(vector<vector<WeakClassifier>> classifiers, vector<vector<float>> weights, 
        string imageDir, vector<int> imageIndices, 
        string output);

    efds_graph(vector<vector<WeakClassifier>> classifiers, vector<vector<float>> weights, 
        string imageDir, vector<int> imageIndices, 
        string output, string classifierResultOut);

    ~efds_graph();

    /* Scheduler for this graph */
    void scheduler() override;
private:
    /* Private vars */
    string imageDir;
    vector<int> imageIndices;
    int numClassifierActors;
    txt_img_read *imageRead;
    string classifiersResultsFilename;
};

#endif
