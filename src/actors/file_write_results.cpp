#include <iostream>
#include <fstream>
#include "file_write_results.h"
#include "../utils/ImageSubwindow.h"

#define MAX_FIFO_COUNT 1

#define TAG "file_write_results::"

using namespace std;

file_write_results::file_write_results(welt_c_fifo_pointer input_in, string output_filename) {
    this->input_port = input_in;
    this->resultCounter = 0;
    this->outputFilename = output_filename;
    this->actor_set_max_port_count(MAX_FIFO_COUNT);
    this->mode = FILE_WRITE_PROCESS;
}

bool file_write_results::enable() {
    cout << TAG << "enable() ENTER" << endl;
    bool result = false;
    switch (mode) {
        case FILE_WRITE_PROCESS:
            result = (welt_c_fifo_population(input_port) > 0);
            break;

        case FILE_WRITE_ERROR:
            result = false;
            break;

        default:
            result = false;
            break;
    }

    cout << TAG << "enable() EXIT result: " << result << endl;
    return result;
}

void file_write_results::invoke() {
    cout << TAG << "invoke() ENTER" << endl;
    switch (mode) {
        case FILE_WRITE_PROCESS: {
            cout << TAG << "invoke() FILE_WRITE_PROCESS" << endl;
            resultCounter++;
            ImageSubwindow *image;
    	    welt_c_fifo_read(this->input_port, &image);

            if (image == nullptr) {
                break;
            }

            string result;
    	    if (image->reject){
                result = "NF";
            } else {
                result = "F";
            }

            // Open stream and append results
            ofstream outStream;
            outStream.open(this->outputFilename, ofstream::app);

            if (!outStream.is_open()) {
                cerr << "Error: Unable to open output file: " << this->outputFilename << endl;
                mode = FILE_WRITE_ERROR;
                break;
            }

    	    outStream << resultCounter << " " << result << endl;
            outStream.close();
            break;
        }

        case FILE_WRITE_ERROR: {
            cout << TAG << "invoke() FILE_WRITE_ERRO" << endl;
            /* Remain in the same mode, do nothing */
            mode = FILE_WRITE_ERROR;
            break;
        }

        default:
            mode = FILE_WRITE_ERROR;
            break;
    }
    cout << TAG << "invoke() EXIT" << endl;
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

