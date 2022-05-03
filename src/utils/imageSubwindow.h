#ifndef image_subwindow_h 
#define image_subwindow_h

#include <vector>

struct image_subwindow {
	vector<vector<int>> *image;
	int startRow, startCol;
};

#endif
