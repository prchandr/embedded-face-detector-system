#include <iostream>
#include "classifier.h"

#define MAX_FIFO_COUNT 3

using namespace std;

classifier::classifier(welt_c_fifo_pointer input_in, 
            welt_c_fifo_pointer continue_out,
            welt_c_fifo_pointer abort_out) {

    this->input_port = input_in;
    this->continue_port = continue_out;
    this->abort_out = abort_out;

    this->actor_set_max_port_count(MAX_FIFO_COUNT);
    this->mode = CLASSIFIER_MODE_CONFIGURE;
}

bool classifier::enable() {
    
    bool result = false;

    switch (mode) {
        case CLASSIFIER_MODE_CONFIGURE:
            result = true;
            break;
        case CLASSIFIER_MODE_READ:
            result = (welt_c_fifo_population(input_port) > 0);
            break;

        case CLASSIFIER_MODE_CLASSIFY:
            break;


        case CLASSIFIER_MODE_FALSE:
            result = (welt_c_fifo_population(abort_out) 
                < welt_c_fifo_capacity(abort_out));
            break;


        case CLASSIFIER_MODE_TRUE:
            result = (welt_c_fifo_population(continue_out) 
                    < welt_c_fifo_capacity(continue_out));
            break;

        default:
            result = false;
            break;
    }
    return result;
}

void classifier::invoke() {
    switch (mode) {
        case CLASSIFIER_MODE_CONFIGURE: {
            /* Configures actor with specific features and weights */
            break;
        }
        case CLASSIFIER_MODE_READ: {
            /* Reads in pointer to image subwindow*/

            break;
        }
        case CLASSIFIER_MODE_CLASSIFY: {
            /* Runs VJ on subwindow input */
            /* 1 Rectangular Features*/

			
            /* weight update process for face training*/
            for(i=0; i<samplenum; i++)
            {
                if(label[i] == true)
                {
                    error += weight[i];
                }
            }
			
            for(i=0; i<samplenum; i++)
            {
                weight[i]  = weight[i]*pow((error/(1-error), label[i]); // update the weight
            }
			
            break;
        }
        case CLASSIFIER_MODE_FALSE: {
            /* Write copy of subwindow input to abort */
            break;
        }
        case CLASSIFIER_MODE_TRUE: {
            /* Write copy of subwindow input to continue */
            break;
        }

        default:
            break;
    }
}

void classifier::reset() {
    mode = CLASSIFIER_MODE_CONFIGURE;
}

void classifier::connect(welt_cpp_graph *graph) {
    int port_index;
    int direction;

    direction = GRAPH_IN_CONN_DIRECTION;
    port_index = 0;
    graph->add_connection(this, port_index, direction);

    direction = GRAPH_OUT_CONN_DIRECTION;
    port_index = 1;
    graph->add_connection(this, port_index, direction);

    direction = GRAPH_OUT_CONN_DIRECTION;
    port_index = 2;
    graph->add_connection(this, port_index, direction);
}

classifier::~classifier() {
    cout << "delete classifier actor" << endl;
}

