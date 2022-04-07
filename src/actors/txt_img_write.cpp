/*******************************************************************************
@ddblock_begin copyright

Copyright (c) 1997-2022
Maryland DSPCAD Research Group, The University of Maryland at College Park 

Permission is hereby granted, without written agreement and without
license or royalty fees, to use, copy, modify, and distribute this
software and its documentation for any purpose, provided that the above
copyright notice and the following two paragraphs appear in all copies
of this software.

IN NO EVENT SHALL THE UNIVERSITY OF MARYLAND BE LIABLE TO ANY PARTY
FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES
ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
THE UNIVERSITY OF MARYLAND HAS BEEN ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.

THE UNIVERSITY OF MARYLAND SPECIFICALLY DISCLAIMS ANY WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE SOFTWARE
PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE UNIVERSITY OF
MARYLAND HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
ENHANCEMENTS, OR MODIFICATIONS.

@ddblock_end copyright
*******************************************************************************/

#include <iostream>

#include "txt_img_write.h"
#include "../utils.h"

#define MAX_FIFO_COUNT 1

using namespace std;

// constructor
txt_img_write::txt_img_write(welt_c_fifo_pointer out_fifo, char*
file_name, int index) {
    this->in = (welt_c_fifo_pointer)out_fifo;
    this->actor_set_index(index);
    this->actor_set_max_port_count(MAX_FIFO_COUNT);
    this->mode = TXT_IMG_WRITE_MODE_WRITE;
    this->file_name = file_name;
}

bool txt_img_write::enable() {
    cout << "txt_img_write::enable() ENTER" << endl;
    bool result = false;

    switch (mode) {
        case TXT_IMG_WRITE_MODE_WRITE:
            result = (welt_c_fifo_population(in) >= 1);
            break;
        case TXT_IMG_WRITE_MODE_INACTIVE:
            result = false;
            break;
        default:
            result = false;
            break;
    }
    cout << "txt_img_write::enable() EXIT" << endl;
    return result;
}

void txt_img_write::invoke() {
    cout << "txt_img_write::invoke() ENTER" << endl;
    switch (mode) {
        case TXT_IMG_WRITE_MODE_WRITE: {
            vector<vector<int>>* grid_in;
            welt_c_fifo_read(this->in, &grid_in);
            write_txt_image(this->file_name, *grid_in);
            break;
        }
        case TXT_IMG_WRITE_MODE_INACTIVE:
            mode = TXT_IMG_WRITE_MODE_INACTIVE;
            break;
        default:
            mode = TXT_IMG_WRITE_MODE_INACTIVE;
            break;
    }
    cout << "txt_img_write::invoke() EXIT" << endl;
}

void txt_img_write::reset() {
    mode = TXT_IMG_WRITE_MODE_WRITE;
}

void txt_img_write::connect(welt_cpp_graph *graph) {
    int port_index;
    int direction;

    /* output 1*/
    direction = GRAPH_OUT_CONN_DIRECTION;
    port_index = 0;
    graph->add_connection(this, port_index, direction);
    //cout << "in_image" << endl;


}

txt_img_write::~txt_img_write() {
    cout << "delete img rotate actor" << endl;
}

