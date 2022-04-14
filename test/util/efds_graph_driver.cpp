#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "../../src/graph/efds_graph.h"

using namespace std;

int main(int argc, char **argv) {
    int i = 0;
    int arg_count = ; /* driver  */

    /* Check program usage. */
    if (argc != arg_count) {
        fprintf(stderr, "efds_graph_driver.exe error: arg count\n");
    }

    /* Open the input and output file(s). */
    i = 1;

    auto* efds_graph = new efds_graph();
    /* Execute the graph. */
    efds_graph->scheduler();

    /* Normal termination. */
    return 0;
}





