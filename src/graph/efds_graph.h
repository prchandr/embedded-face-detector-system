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

#include "../utils/weakClassifier.h"

#define BUFFER_CAPACITY 1024
#define MAX_CLASSIFIERS 32

/* An enumeration of the actors in this application. */
#define ACTOR_TXT_IMG_READ  0
#define ACTOR_FILE_WRITE_T  1
#define ACTOR_FILE_WRITE_F  2

/* An enumeration of the edges in this application. The naming convention
for the constants is FIFO_<source actor>_<sink actor>. */
#define FIFO_TIR_CLAS   0
#define FIFO_CLAS_FWT  	1
#define FIFO_CLAS_FWF	2

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

    ~efds_graph();

    /* Scheduler for this graph */
    void scheduler() override;
};

#endif
