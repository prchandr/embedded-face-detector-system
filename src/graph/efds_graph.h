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

#include "../actors/txt_img_write.h"
#include "../actors/txt_img_read.h"
#include "../actors/classifier.h"

#define BUFFER_CAPACITY 1024

/* An enumeration of the actors in this application. */


/* An enumeration of the edges in this application. The naming convention
for the constants is FIFO_<source actor>_<sink actor>. */


/* The total number of actors in the application. */
#define ACTOR_COUNT     4
#define FIFO_COUNT      3

/*******************************************************************************
TYPE DEFINITIONS
*******************************************************************************/

class efds_graph : public welt_cpp_graph{
public:
    efds_graph();
    ~efds_graph();

    /* Scheduler for this graph */
    void scheduler() override;
};

#endif
