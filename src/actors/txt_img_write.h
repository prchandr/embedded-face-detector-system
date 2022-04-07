#ifndef txt_img_write_h
#define txt_img_write_h

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

/*******************************************************************************
DESCRIPTION:
This is a header file of text image write actor.
*******************************************************************************/
extern "C" {
#include "welt_c_util.h"
#include "welt_c_fifo.h"
}

#include "welt_cpp_actor.h"
#include "welt_cpp_graph.h"

/*******************************************************************************
Actor Modes:
INACTIVE mode will not do anything. If there is no input in the tokens, the
program will be in the INACTIVE mode.
WRITE mode will read image from the input FIFO. The image format is a 2D vector.
Then the content of the vector will be written to an external file.
*******************************************************************************/
#define TXT_IMG_WRITE_MODE_WRITE        1
#define TXT_IMG_WRITE_MODE_INACTIVE     2

class txt_img_write : public welt_cpp_actor{
public:
    txt_img_write(welt_c_fifo_pointer out, char* file_name,
                    int index);
    ~txt_img_write() override;

    bool enable() override;
    void invoke() override;

    void reset() override;

    void connect(welt_cpp_graph *graph) override;

private:
    welt_c_fifo_pointer in;
    char* file_name;
};

#endif
