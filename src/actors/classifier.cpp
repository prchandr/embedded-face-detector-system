#include <iostream>
#include <fstream>
#include <string>
#include "classifier.h"

#include "../utils/WeakClassifier.h"
#include "../utils/ImageSubwindow.h"


#define MAX_FIFO_COUNT 3

#define TAG "classifier::"

using namespace std;

classifier::classifier(welt_c_fifo_pointer input_in,
                       welt_c_fifo_pointer continue_out,
                       vector<WeakClassifier> classifiers, vector<float> weights,
                       string fileOutName) {
    this->input_port = input_in;
    this->continue_port = continue_out;
    this->resultSumFilename = fileOutName;

    // Configure in constructor instead of in configure mode
    this->classifiers = classifiers;
    this->weights = weights;

    this->actor_set_max_port_count(MAX_FIFO_COUNT);
    this->mode = CLASSIFIER_MODE_CONFIGURE;
}

bool classifier::enable() {
    cout << TAG << "enable() ENTER\n";
    bool result = false;
    switch (mode) {
    case CLASSIFIER_MODE_CONFIGURE:
        cout << TAG << "enable() CLASSIFIER_MODE_CONFIGURE\n";
        result = true;
        break;

    case CLASSIFIER_MODE_READ:
        cout << TAG << "enable() CLASSIFIER_MODE_READ\n";
        result = (welt_c_fifo_population(input_port) > 0);
        break;

    case CLASSIFIER_MODE_CLASSIFY:
        cout << TAG << "enable() CLASSIFIER_MODE_CLASSIFY\n";
        result = true;
        break;

    case CLASSIFIER_MODE_CONTINUE:
        cout << TAG << "enable() CLASSIFIER_MODE_CONTINUE\n";
        result = (welt_c_fifo_population(continue_port)
                  < welt_c_fifo_capacity(continue_port));
        break;

    default:
        cout << TAG << "enable() default\n";
        result = false;
        break;
    }
    cout << TAG << "enable() EXIT result: " << result << "\n";
    return result;
}

void classifier::invoke() {
    cout << TAG << "invoke() ENTER\n";
    switch (mode) {
    case CLASSIFIER_MODE_CONFIGURE: {
        cout << TAG << "invoke() MODE_CONFIGURE\n";

        /* Configures actor with specific features and weights */
        // Checks if classifiers, weights vectors are non-empty
        if (this->classifiers.empty() || this->weights.empty()
                || (this->classifiers.size() != this->weights.size())) {
            cerr << "classifier::invoke() Error: classifiers and weights incorrectly configured.\n";
            break;
        }
        mode = CLASSIFIER_MODE_READ;
        break;
    }

    case CLASSIFIER_MODE_READ: {
        cout << TAG << "invoke() MODE_READ\n";

        /* Reads in pointer to image subwindow*/
        ImageSubwindow *integralImage = nullptr;
        welt_c_fifo_read(input_port, &integralImage);
        this->image = *integralImage;
        cout << TAG << "invoke() imageAddress: " << this->image.image << "\n";
        cout << TAG << "invoke() reject: " << this->image.reject << "\n";

        mode = CLASSIFIER_MODE_CLASSIFY;
        break;
    }

    case CLASSIFIER_MODE_CLASSIFY: {
        cout << TAG << "invoke() MODE_CLASSIFY\n";
        // If reject flag, do not classify
        if (image.reject) {
            mode = CLASSIFIER_MODE_CONTINUE;
            break;
        }

        // Perform classification using each of the classifiers
        float weightedClassify = 0.0;
        int isFace;
        this->classifierResults.clear();

        for (int i = 0; i < classifiers.size(); i++) {
            isFace = classifiers[i].classifyImage(this->image); // 1 if true, 0 if false
            weightedClassify += isFace * weights[i];

            // Store classifier results for training/debugging purposes
            this->classifierResults.push_back(classifiers[i].getResultSum());
        }

        cout << TAG << "invoke() weightedClassify: " << weightedClassify << "\n";

        // Sum weights
        float sumWeights = 0;
        for (auto &weight : weights) {
            sumWeights += weight;
        }

        cout << TAG << "invoke() sumWeights: " << sumWeights << "\n";

        // Threshold check using weights
        if (weightedClassify < 0.5 * sumWeights) {
            cout << TAG << "invoke() rejecting based on classification. \n";
            this->image.reject = true;
        }

        mode = CLASSIFIER_MODE_CONTINUE;
        break;
    }

    case CLASSIFIER_MODE_CONTINUE: {
        cout << TAG << "invoke() MODE_CONTINUE\n";
        // Write copy of subwindow input to continue
        auto ptr_token = &(this->image);
        welt_c_fifo_write(this->continue_port, &ptr_token);

        // Writes classifier results to the file for training/debugging purposes
        if (!this->resultSumFilename.empty()) {
            ofstream outStream;
            outStream.open(this->resultSumFilename, ofstream::app);
            for (auto &result : this->classifierResults) {
                outStream << result << " ";
            }
            outStream << "\n";
            outStream.close();
        }

        mode = CLASSIFIER_MODE_READ;
        break;
    }

    default:
        cout << TAG << "invoke() default\n";
        break;
    }

    cout << TAG << "invoke() EXIT\n";
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
    cout << "delete classifier actor\n";
}

