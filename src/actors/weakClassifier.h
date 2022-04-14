#ifndef weak_classifier_h
#define weak_classifier_h

#include <vector>

struct WeakClassifier {
	vector<vector<int>> feature;
	float threshold;
	int parity;
}

#endif
