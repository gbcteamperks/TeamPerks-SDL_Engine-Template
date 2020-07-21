#pragma once
#ifndef _LEVELMANAGER_H
#define _LEVELMANAGER_H

#include <iostream>
#include <map>
#include <array>
#include "Tile.h"
#include "Config.h"
class LevelManager 
{



public:

	static LevelManager* Instance() 
	{
		if (s_pInstance == nullptr) 
		{
			s_pInstance = new LevelManager();
		}
		return s_pInstance;
	}

	void update(float scroll, bool x);
	void clean();
	void render(bool debug);

	void loadTiles(std::string spritePath, std::string texture_Name, std::string tileDataPath);
	void loadLevel(std::string levelDataPath);

	void clearTiles();
	void clearLevel();

	std::map<char, Tile*>& const getTiles() { return m_tiles; }
	std::array<std::array<Tile*, Config::COL_NUM>, Config::ROW_NUM>& const getLevel() { return m_level; }
	std::vector<GameObject*>& const getObstacles() { return m_obstacles; }
	bool checkCollision(GameObject* obj, const int dX, const int dY);
	void printNodes();

private:

	static LevelManager* s_pInstance;
	int m_sumDX = 0;
	int m_sumDY = 0;
	LevelManager();
	~LevelManager();

	std::map<char, Tile*> m_tiles;
	std::vector<GameObject*> m_obstacles;
	std::array < std::array<Tile*, Config::COL_NUM>, Config::ROW_NUM> m_level;
	std::vector<PathNode*> m_Nodes;
};
typedef LevelManager LVLMAN;
#endif