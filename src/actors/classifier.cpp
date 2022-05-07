#include <iostream>
#include "classifier.h"

#include "../utils/WeakClassifier.h"
#include "../utils/ImageSubwindow.h"


#define MAX_FIFO_COUNT 3

#define TAG "classifier::"

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
    cout << TAG << "enable() ENTER" << endl;
    bool result = false;
    switch (mode) {
        case CLASSIFIER_MODE_CONFIGURE:
            result = true;
            break;

        case CLASSIFIER_MODE_READ:
            result = (welt_c_fifo_population(input_port) > 0);
            break;

        case CLASSIFIER_MODE_CLASSIFY:
            result = true; 
            break;

        case CLASSIFIER_MODE_CONTINUE:
            result = (welt_c_fifo_population(continue_port) 
                < welt_c_fifo_capacity(continue_port));
            break;

        default:
            result = false;
            break;
    }
    cout << TAG << "enable() EXIT result: " << result << endl;
    return result;
}

void classifier::invoke() {
    cout << TAG << "invoke() ENTER" << endl;
    switch (mode) {
        case CLASSIFIER_MODE_CONFIGURE: {
            cout << TAG << "invoke() MODE_CONFIGURE" << endl;

            /* Configures actor with specific features and weights */
            // Checks if classifiers, weights vectors are non-empty
            if (this->classifiers.empty() || this->weights.empty()
                || (this->classifiers.size() != this->weights.size())) {
                cerr << "classifier::invoke() Error: classifiers and weights incorrectly configured." << endl;
                break;
            }
            mode = CLASSIFIER_MODE_READ;
            break;
        }

        case CLASSIFIER_MODE_READ: {
            cout << TAG << "invoke() MODE_READ" << endl;

            /* Reads in pointer to image subwindow*/
            ImageSubwindow *integralImage = nullptr;
            welt_c_fifo_read(input_port, &integralImage);
            this->image = *integralImage;
            cout << TAG << "invoke() imageAddress: " << this->image.image << endl;
            cout << TAG << "invoke() reject: " << this->image.reject << endl;

            mode = CLASSIFIER_MODE_CLASSIFY;
            break;
        }

        case CLASSIFIER_MODE_CLASSIFY: {
            cout << TAG << "invoke() MODE_CLASSIFY" << endl;
            // If reject flag, do not classify
            if (image.reject) {
                mode = CLASSIFIER_MODE_CONTINUE;
                break;
            }

            float weightedClassify = 0.0;
            int isFace;

            // Perform classification using each of the classifiers
            for (int i = 0; i < classifiers.size(); i++) {
                isFace = classifiers[i].classifyImage(this->image); // 1 if true, 0 if false
                weightedClassify += isFace * weights[i];
            }

            cout << TAG << "invoke() weightedClassify: " << weightedClassify << endl;

            // Sum weights
            float sumWeights = 0;
            for (auto &weight: weights) {
                sumWeights += weight;
            }

            cout << TAG << "invoke() sumWeights: " << sumWeights << endl;

            // Threshold check using weights
    	    if (weightedClassify < 0.5 * sumWeights) { // final strong classifier: SUM(alpha_t * h_t) >= 1/2 *(SUM(alpha_t)), alpha_t = log(1/beta_t)
                cout << TAG << "invoke() rejecting based on classification. " << endl;
                this->image.reject = true;
            }

            mode = CLASSIFIER_MODE_CONTINUE;
            break;
        }
        
        case CLASSIFIER_MODE_CONTINUE: {
            cout << TAG << "invoke() MODE_CONTINUE" << endl;
            /* Write copy of subwindow input to continue */
	        welt_c_fifo_write(continue_port, &(this->image));
            mode = CLASSIFIER_MODE_READ;
            break;
        }

        default:
        cout << TAG << "invoke() default" << endl;
            break;
    }

    cout << TAG << "invoke() EXIT" << endl;
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

