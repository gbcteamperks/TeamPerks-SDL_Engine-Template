#pragma once

#include "DisplayObject.h"
#include "TextureManager.h"


class TitleSprite : public DisplayObject
{
public:
	TitleSprite();
	~TitleSprite();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

};

