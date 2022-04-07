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

#include "txt_img_read.h"
#include "../utils.h"

#define MAX_FIFO_COUNT 1

using namespace std;

// constructor
txt_img_read::txt_img_read(welt_c_fifo_pointer out_fifo, char *file_name,
        int nRows, int nCols, int index) {
    this->out = (welt_c_fifo_pointer)out_fifo;
    this->actor_set_index(index);
    this->actor_set_max_port_count(MAX_FIFO_COUNT);
    this->mode = TXT_IMG_READ_MODE_READ;
    this->file_name = file_name;
    this->nRows = nRows;
    this->nCols = nCols;
}

bool txt_img_read::enable() {
    cout << "txt_img_read::enable() ENTER" << endl;
    bool result = false;

    switch (mode) {
        case TXT_IMG_READ_MODE_READ:
            result = (welt_c_fifo_population(out) < welt_c_fifo_capacity(out));
            break;
        case TXT_IMG_READ_MODE_INACTIVE:
            result = false;
            break;
        default:
            result = false;
            break;
    }
    cout << "txt_img_read::enable() EXIT" << endl;
    return result;
}

void txt_img_read::invoke() {
    cout << "txt_img_read::invoke() ENTER" << endl;
    switch (mode) {
        case TXT_IMG_READ_MODE_READ: {
            this->img_grid = read_txt_image(this->file_name, this->nRows,
                    this->nCols);
            auto ptr_token = &img_grid;
            welt_c_fifo_write(this->out, &ptr_token);

            cout << "txt_img_read::invoke() ptr_token: " << ptr_token << endl;
            break;
        }
        case TXT_IMG_READ_MODE_INACTIVE:
            mode = TXT_IMG_READ_MODE_INACTIVE;
            break;
        default:
            mode = TXT_IMG_READ_MODE_INACTIVE;
            break;
    }
    cout << "txt_img_read::invoke() EXIT" << endl;
}

void txt_img_read::reset() {
    mode = TXT_IMG_READ_MODE_READ;
}

void txt_img_read::connect(welt_cpp_graph *graph) {
    int port_index;
    int direction;

    /* output 1*/
    direction = GRAPH_OUT_CONN_DIRECTION;
    port_index = 0;
    graph->add_connection(this, port_index, direction);
    //cout << "in_image" << endl;


}

txt_img_read::~txt_img_read() {
    cout << "delete img rotate actor" << endl;
}

