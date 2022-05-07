#ifndef image_subwindow_h 
#define image_subwindow_h

#include <vector>

struct ImageSubwindow {
	std::vector<std::vector<int>> *image;
	int startRow, startCol;
	bool reject = false;
};

#endif
