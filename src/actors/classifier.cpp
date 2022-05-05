#include <iostream>
#include "classifier.h"

#include "../utils/WeakClassifier.h"
#include "../utils/ImageSubwindow.h"


#define MAX_FIFO_COUNT 3

using namespace std;

classifier::classifier(welt_c_fifo_pointer input_in, 
            welt_c_fifo_pointer continue_out,
            vector<WeakClassifier> classifiers, vector<float> weights) {
    this->input_port = input_in;
    this->continue_port = continue_out;

    // Configure in constructor instead of in configure mode
    this->classifiers = classifiers;
    this->weights = weights;

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

        case CLASSIFIER_MODE_FALSE: case CLASSIFIER_MODE_TRUE:
            result = (welt_c_fifo_population(continue_port) 
                < welt_c_fifo_capacity(continue_port));
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

            // Checks if classifiers, weights vectors are non-empty
            if (this->classifiers.empty() || this->weights.empty()
                || (this->classifiers.size() != this->weights.size())) {
                mode = CLASSIFIER_MODE_READ;
            } else {
                cerr << "Error: classifiers and weights incorrectly configured.\n";
            }

            break;
        }

        case CLASSIFIER_MODE_READ: {
            /* Reads in pointer to image subwindow*/
            ImageSubwindow *integralImage = nullptr;
            welt_c_fifo_read(input_port, &integralImage);
            this->image = integralImage;
            mode = CLASSIFIER_MODE_CLASSIFY;       
            break;
        }

        case CLASSIFIER_MODE_CLASSIFY: {
            // If null, do not classify
            if (image == nullptr) {
                mode = CLASSIFIER_MODE_FALSE;
                break;
            }

            float weightedClassify = 0.0;
            int isFace;

            // Perform classification using each of the classifiers
            for (int i = 0; i < classifiers.size(); i++) {
                isFace = classifiers[i].classifyImage(*(this->image)); // 1 if true, 0 if false
                weightedClassify += isFace * weights[i];
            }

            // Sum weights
            float sumWeights = 0;
            for (auto &weight: weights) {
                sumWeights += weight;
            }

            // Threshold check using weights
    	    if (weightedClassify >= 0.5 * sumWeights) { // final strong classifier: SUM(alpha_t * h_t) >= 1/2 *(SUM(alpha_t)), alpha_t = log(1/beta_t)
                mode = CLASSIFIER_MODE_TRUE;
            } else {
                mode = CLASSIFIER_MODE_FALSE;
            }
            
            break;
        }
        
        case CLASSIFIER_MODE_FALSE: {
            /* Write copy of subwindow input to abort */
	        welt_c_fifo_write(continue_port, nullptr);
            mode = CLASSIFIER_MODE_READ;
            break;
        }

        case CLASSIFIER_MODE_TRUE: {
            /* Write copy of subwindow input to continue */
	       welt_c_fifo_write(continue_port, this->image);
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
}

classifier::~classifier() {
    cout << "delete classifier actor" << endl;
}

