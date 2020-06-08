#pragma once
#include "DisplayObject.h"
#include "TextureManager.h"


class StaticSprite : public DisplayObject
{
private:
	std::string name;
public:
	StaticSprite(std::string spritePath, std::string name, float posX, float posY);
	~StaticSprite();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

};
