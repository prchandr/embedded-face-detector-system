#include "training.h"


training::training() {
	
}


bool training::classifyImage(ImageSubwindow integral_image) {
	
        if(polarity*(pos-neg) > polarity*threshold)
		return true;
	else
		return false;
}

