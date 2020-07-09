#pragma once
#ifndef _TILE_H
#define _TILE_H
#include "DisplayObject.h"
#include "Pathing.h"

class Tile : public DisplayObject 
{
private:
	bool m_bObstacle;
	bool m_bHazard;
	std::string m_sName;
	int m_iX;
	int m_iY;
public:

	PathNode* m_node;
	//Label *m_lCost, *m_lX, *m_lY;
	Tile(std::string name, int x, int y, bool o, bool h);
	~Tile();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	bool& isObstacle();
	bool isHazard();
	void setXY(int x, int y);
	Tile* Clone();
	PathNode* Node();
	virtual void Print();
};

#endif // !_TILE_H
