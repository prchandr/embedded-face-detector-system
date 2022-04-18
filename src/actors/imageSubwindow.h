#ifndef image_subwindow_h 
#define image_subwindow_h

#include <vector>

struct ImageSubwindow {
	vector<vector<int>> *image;
	int startRow, startCol;
	int windowWidth, windowHeight;
};


#endif
