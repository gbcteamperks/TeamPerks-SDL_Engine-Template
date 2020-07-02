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

private:

	static LevelManager* s_pInstance;

	LevelManager();
	~LevelManager();
	
	std::map<int, Tile*> m_tiles;
	std::array < std::array<Tile*, Config::ROW_NUM>, Config::COL_NUM> m_level;


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
	void render();

	void loadTiles(std::string spritePath, std::string texture_Name, std::string tileDataPath);
	void loadLevel(std::string levelDataPath);

	void clearTiles();
	void clearLevel();

	std::map<int, Tile*>& const getTiles() { return m_tiles; }
	std::array<std::array<Tile*, Config::ROW_NUM>, Config::COL_NUM>& const getLevel() { return m_level; }

};
typedef LevelManager LVLMAN;
#endif