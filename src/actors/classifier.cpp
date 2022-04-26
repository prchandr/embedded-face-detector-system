#include <iostream>
#include "classifier.h"
#include "weakClassifier.h"
#include "integrateImage.h"

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
	       ImageSubwindow *W = nullptr;
	       welt_c_fifo_read(input_port, &W);

	       if (integralImage == nullptr)
		 mode = CLASSIFIER_MODE_FALSE;
	       else
		 mode = CLASSIFIER_MODE_CLASSIFY;

	       break;

        }
        case CLASSIFIER_MODE_CLASSIFY: {
            /* Runs VJ on subwindow input */
            /* 1 Rectangular Features*/

	    float error = 0.0;
            /* weight update process for face training*/
            for(int i=0; i<samplenum; i++)
            {
                if(label[i] == true)
                {
                    error += weight[i];
                }
            }
			
            for(int i=0; i<samplenum; i++)
            {
                weight[i]  = weight[i]*pow((error/(1-error), label[i]); // update the weight
            }
			
		  //break;

	    // Do Final Classifier Evaluation using weights
	    weightedSum = 0.0;
	    float isFace;
	    for (int i = 0; i < classifiers.size(); i++) {
	      isFace = classifiers[i].classifyImage(W) ? 1.0 : 0.0; // 1 if true, 0 if false
	      weightedSum += isFace + weights[i]; 
	    }

	    if (error*weightedSum >= 0.5*weightedSum) // final strong classifier: SUM(alpha_t * h_t) >= 1/2 *(SUM(a_t)), a_t = log(1/beta_t)
	      mode = CLASSIFIER_MODE_TRUE;
	    else
	      mode = CLASSIFIER_MODE_FALSE;
	    
	    break;
        }
        case CLASSIFIER_MODE_FALSE: {
            /* Write copy of subwindow input to abort */
	        welt_c_fifo_write(abort_port, &(W));
		mode = CLASSIFIER_MODE_READ;
		
                break;
        }
        case CLASSIFIER_MODE_TRUE: {
            /* Write copy of subwindow input to continue */
	       welt_c_fifo_write(continue_port, &(W));
	       mode = CLASSIFIER_MODE_READ;
	       
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

