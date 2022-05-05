#ifndef file_write_results_h 
#define file_write_results_h

/*******************************************************************************
DESCRIPTION:
This is a header file of the file_write_results actor.
*******************************************************************************/
extern "C" {
    #include "welt_c_util.h"
    #include "welt_c_fifo.h"
}

#include "welt_cpp_actor.h"
#include "welt_cpp_graph.h"

#include "../utils/WeakClassifier.h"

#include <vector>

using namespace std;

/*******************************************************************************
Actor Modes:

Process - Reads in a pointer from input, checks if it is null, and writes the
result to the text file.

Error - Enters this mode if there is an error with writing to the text file. 
*******************************************************************************/
#define FILE_WRITE_PROCESS   1
#define FILE_WRITE_ERROR     2

class file_write_results : public welt_cpp_actor{
public:
    file_write_results(welt_c_fifo_pointer input_in, string output_filename);
    ~file_write_results() override;

    bool enable() override;
   
    void invoke() override;

    void reset() override;

    void connect(welt_cpp_graph *graph) override;

private:
    /* Inner parameters */
    int resultCounter;
    string outputFilename;

    /* FIFO pointers */
    welt_c_fifo_pointer input_port;
};

#endif

