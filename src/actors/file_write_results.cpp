#include <iostream>
#include "file_write_results.h"

#define MAX_FIFO_COUNT 1

using namespace std;

file_write_results::file_write_results(welt_c_fifo_pointer input_in, string output_filename) {
    this->input_port = input_in;

    this->actor_set_max_port_count(MAX_FIFO_COUNT);
    this->mode = CLASSIFIER_MODE_CONFIGURE;
}

bool file_write_results::enable() {
    bool result = false;
    switch (mode) {
        case FILE_WRITE_PROCESS:
            result = true;
            break;

        case FILE_WRITE_ERROR:
            result = false;
            break;

        default:
            result = false;
            break;
    }
    return result;
}

void file_write_results::invoke() {
    switch (mode) {
        case FILE_WRITE_PROCESS: {
	    welt_c_fifo_read(input_port, &resultCounter);
	    if (resultCounter == 0)
	      outputFileName += "NF\n";
	    else
	      outputFileName += "F\n";
	    outStream << outputFileName << endl;
	    mode = FILE_WRITE_PROCESS;
            break;
        }

        case FILE_WRITE_ERROR: {
	    /* Remain in the same mode, do nothing */
	    mode = FILE_WRITE_ERROR;
            break;
        }

        default:
	    mode = FILE_WRITE_ERROR:
            break;
    }
}

void file_write_results::reset() {
    mode = FILE_WRITE_PROCESS;
}

void file_write_results::connect(welt_cpp_graph *graph) {
    int port_index;
    int direction;

    direction = GRAPH_IN_CONN_DIRECTION;
    port_index = 0;
    graph->add_connection(this, port_index, direction);
}

file_write_results::~file_write_results() {
    cout << "delete file_write_results actor" << endl;
}

