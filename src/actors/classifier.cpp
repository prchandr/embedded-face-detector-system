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
			// Integrate image

			weightedSum = 0;
			// Go through list of weak classifiers, perform classification
			/* for classifier in classifiers
				isFace = classifer.classify(integral_image)
				weightedSum += isFace * weight[i]

			// Do Final Classifier evaluation using weights.

			*/









            /* Runs VJ on subwindow input */
            /* integrate image */
            int i,j,m,n;
            for(i=0;i<24; i++)
            {
                for(j=1;j<24; j++)
                {
                    //image vector is vector<vector <int>> *img.
                    if(i==0)
                        img[i][j] += img[i][j-1];
                    else if(j==0)
                        img[i][j] += img[i-1][j]
                    else
                        img[i][j] += img[i-1][j]+img[i][j-1]-img[i-1][j-1];
                }
            }

            /* 1 Rectangular Features*/
            float weight=1/m;
            int neg, pos;
            vector<bool> label;
            vector<int> sample;
            //vector<int> weight;
            /* 1~24 in column, 1~24 in row. -> 24*24 size*/
            for(m=1; m<25 ; m++) //m,n are row and column of harr features.
            {
                for(n=2; n<25; n += 2)
                {
                    for(i=0;i<24-n+1; i++)
                    {
                        for(j=0;j<24-m+1; j++)
                        {
                            /* only for face samples*/
                            if(i-1<0 && j-1>0)
                            {
                                pos = img[i+n-1][j+m-1] + img[i+n/2-1][j-1] - img[i+n/2-1][j-m-1] - img[i+n-1][j-1];
                                neg = img[i+n/2-1][j+m-1] - img[i+n/2-1][j-1] - img[i-1][j+m-1];
                            }
                            pos = img[i+n-1][j+m-1] + img[i+n/2-1][j-1] - img[i+n/2-1][j-m-1] - img[i+n-1][j-1];
                            neg = img[i+n/2-1][j+m-1] + img[i-1][j-1] - img[i+n/2-1][j-1] - img[i-1][j+m-1];
                            
                            if(pos-neg > threshold)
                                label.pushback(true);
                            else
                                label.pushback(false);
                            weight.pushback
                            
                        }
                    }
                }
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

