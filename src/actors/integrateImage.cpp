#include <iostream>
#include "integrateImage.h"

#define MAX_FIFO_COUNT 2

using namespace std;

integrateImage::integrateImage(welt_c_fifo_pointer input, welt_c_fifo_pointer output) {
    this->input = input;
    this->output = output;

    this->actor_set_max_port_count(MAX_FIFO_COUNT);
    this->mode = II_MODE_INTEGRATE;
}

bool integrateImage::enable() {
    bool result = false;
    switch (mode) {
        case II_MODE_INTEGRATE:
            result = (welt_c_fifo_population(input) > 0) &&
                    (welt_c_fifo_population(output) < 
                    welt_c_fifo_capacity(output));
            break;

        default:
            break;
    }
    return result;   
}

void integrateImage::invoke() {
    // Read in vec<vec<int>> image from pointer
    vector<vector<int>> *img = nullptr;
    welt_c_fifo_read(input, &img);

    if (img == nullptr) {
        cerr << "Error: image pointer received is null.\n";
        return;
    }

    this->image = *img;

    // Integrate image
    integrate(this->image);

    // Make Image Subwindow
	this->integralImage.image = &(this->image);
	this->integralImage.startRow = 0;
    this->integralImage.startCol = 0; 

    // Write to pointer
	welt_c_fifo_write(output, &(this->integralImage));	
	
}

void integrateImage::reset() {
    mode = II_MODE_INTEGRATE;
	this->integralImage.image->clear();
}

void integrateImage::connect(welt_cpp_graph *graph) {
    int port_index;
    int direction;

    direction = GRAPH_IN_CONN_DIRECTION;
    port_index = 0;
    graph->add_connection(this, port_index, direction);

    direction = GRAPH_OUT_CONN_DIRECTION;
    port_index = 1;
    graph->add_connection(this, port_index, direction);
}

integrateImage::~integrateImage() {
    cout << "delete integrateImage actor" << endl;
}

// Integrates an image. 
void integrateImage::integrate(vector<vector<int>> &image) {
    // Sum first row
    for (int i = 1; i < image.size(); i++) {
        image[0][i] += image[0][i - 1];
    }

	// Sum first column
	for (int i = 1; i < image[0].size(); i++) {
		image[i][0] += image[i - 1][0];
	}
    
    // Sum the rest of the image
    for (int i = 1; i < image.size(); i++) {
        for (int j = 1; j < image[i].size(); j++) {
            image[i][j] += image[i - 1][j] + image[i][j - 1] - image[i - 1][j - 1];
        }
    }
}
