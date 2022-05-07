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

#include "../utils/WeakClassifier.h"
#include "../utils/ImageSubwindow.h"

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
is rejected, it is transitioned to false. Otherwise, it is transitioned to true

False - Does not consume any tokens. Produces a null pointer token.

True - Does not consume any tokens. Produces a copy of the PTIS token.

*******************************************************************************/
#define CLASSIFIER_MODE_CONFIGURE   1
#define CLASSIFIER_MODE_READ        2    
#define CLASSIFIER_MODE_CLASSIFY    3
#define CLASSIFIER_MODE_CONTINUE    4

class classifier : public welt_cpp_actor{
public:
    classifier(welt_c_fifo_pointer input_in, 
            welt_c_fifo_pointer continue_out,
            vector<WeakClassifier> classifiers, vector<float> weights);
    ~classifier() override;

    bool enable() override;
   
    void invoke() override;

    void reset() override;

    void connect(welt_cpp_graph *graph) override;

private:
    /* Inner parameters */
    vector<WeakClassifier> classifiers;
    vector<float> weights;
    ImageSubwindow image;

    /* FIFO pointers */
    welt_c_fifo_pointer input_port;
    welt_c_fifo_pointer continue_port;
};

#endif

