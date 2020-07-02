#pragma once
#ifndef _TILE_H
#define _TILE_H
#include "DisplayObject.h"
#include "TextureManager.h"

class Tile : public DisplayObject 
{
private:
	bool m_bObstacle;
	bool m_bHazard;
	//std::string m_sPath;
	std::string m_sName;
	float m_fX;
	float m_fY;
public:

	//PathNode* m_node;
	//Label *m_lCost, *m_lX, *m_lY;
	Tile(std::string name, float posX, float posY, bool o, bool h);
	~Tile();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	bool& isObstacle();
	bool isHazard();
	Tile* Clone();
	//PathNode* Node();
};

#endif // !_TILE_H
