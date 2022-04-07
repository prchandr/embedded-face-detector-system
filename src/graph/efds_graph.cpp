#include <iostream>
#include "efds_graph.h"

using namespace std;

// constructor
efds_graph::efds_graph() {
    
    /* Initialize fifos. */
    int token_size = sizeof(vector<vector<int>>*);

    for (int fifo_idx = 0; fifo_idx < FIFO_COUNT; fifo_idx++) {
        fifos.push_back((welt_c_fifo_pointer)welt_c_fifo_new(BUFFER_CAPACITY,
                token_size, fifo_idx));
    }

    /***************************************************************************
    Create actors in the actors vector and put descriptions
    for each actor in the descriptions vector.
    ***************************************************************************/
  
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
