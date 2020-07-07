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
		for (auto f : frames) {
			f.dw = w;
			f.dh = h;
		}
	}
};

#endif /* defined (__ANIMATION__) */