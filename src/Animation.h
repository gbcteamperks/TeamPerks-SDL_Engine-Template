#pragma once
#ifndef __ANIMATION__
#define __ANIMATION__
#include "Frame.h"
#include <vector>

struct Animation
{
	std::string name;
	std::vector<Frame> frames;
	int current_frame = 0;
	void setWidthAndHeight(int w, int h)
	{
		for (int i = 0; i < frames.size(); i++) {
			frames[i].dw = w;
			frames[i].dh = h;
		}
	}
};

#endif /* defined (__ANIMATION__) */