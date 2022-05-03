#ifndef integrate_image_h 
#define integrate_image_h

/*******************************************************************************
DESCRIPTION:
This is a header file of the integrate image actor.
*******************************************************************************/
extern "C" {
    #include "welt_c_util.h"
    #include "welt_c_fifo.h"
}

#include "welt_cpp_actor.h"
#include "welt_cpp_graph.h"
#include "../utils/imageSubwindow.h"

#include <vector>

/*******************************************************************************
Actor Modes:

Integrate - Consumes a single vec<vec<int>> pointer token from the input_port 
and produces a PTIS token on the output_port of the integrated image.

For now, this actor assumes that the startRow and startCol are 0 and 0,
respectively.

*******************************************************************************/
#define II_MODE_INTEGRATE   0

class integrateImage : public welt_cpp_actor{
public:
    integrateImage(welt_c_fifo_pointer input, welt_c_fifo_pointer output);
    ~integrateImage() override;

    bool enable() override;
   
	void invoke() override;

    void reset() override;

    void connect(welt_cpp_graph *graph) override;

private:
    void integrate(vector<vector<int>> *image);

    /* Private variable */
    ImageSubwindow integralImage;

    /* FIFO pointers */
    welt_c_fifo_pointer input;
    welt_c_fifo_pointer output;
};

#endif

