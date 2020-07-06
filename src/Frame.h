#pragma once
#ifndef __FRAME__
#define __FRAME__
#include <string>

struct Frame
{
	std::string name;
	int x;
	int y;
	int w;
	int h;
	int dw = 0; //destination width
	int dh = 0;
};

#endif /* defined (__FRAME__) */