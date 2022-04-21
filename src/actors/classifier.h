#ifndef classifier_h 
#define classifier_h

/*******************************************************************************
DESCRIPTION:
This is a header file of the classifier actor.
*******************************************************************************/
extern "C" {
    #include "welt_c_util.h"
    #include "welt_c_fifo.h"
}

#include "welt_cpp_actor.h"
#include "welt_cpp_graph.h"
#include "weakClassifier.h"

#include <vector>

using namespace std;

/*******************************************************************************
Actor Modes:

Configure - Loads in parameters from one or more files. Each set of files is
managed as an actor parameter. No tokens are consumed.

Read - Consumes a single PTIS token from the input_port and produces no tokens.
If the consumed token is a non-null pointer, then the actor is transitioned to
classify, otherwise it is transitioned to false.

Classify - Operates on the image subwindow W in the token consumed in the 
previous firing. VJ algorithm is used to determine whether W has a face. If W 
is rejected, it is transitioned to false. Otherwise, it is transitioned to true. 

False - Does not consume any tokens. Produces a copy of the token that was read
in on the output abort_port. Transitions to read.

in on the output continue_port. Transitions to read.
True - Does not consume any tokens. Produces a copy of the token that was read

*******************************************************************************/
#define CLASSIFIER_MODE_CONFIGURE   1
#define CLASSIFIER_MODE_READ        2    
#define CLASSIFIER_MODE_CLASSIFY    3
#define CLASSIFIER_MODE_FALSE       4
#define CLASSIFIER_MODE_TRUE        5

class classifier : public welt_cpp_actor{
public:
    classifier(welt_c_fifo_pointer input_in, 
            welt_c_fifo_pointer continue_out,
            welt_c_fifo_pointer abort_out);
    ~classifier() override;

    bool enable() override;
   
	void invoke() override;

    void reset() override;

    void connect(welt_cpp_graph *graph) override;

private:
    /* Inner parameters */
    vector<WeakClassifier> classifiers;
    vector<float> weights;

    /* FIFO pointers */
    welt_c_fifo_pointer input_port;
    welt_c_fifo_pointer continue_port;
    welt_c_fifo_pointer abort_port;
};

#endif

