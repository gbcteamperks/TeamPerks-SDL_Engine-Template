//#pragma once
//#ifndef _LEVELMANAGER_H
//#define _LEVELMANAGER_H
//
//#include <iostream>
//#include <map>
//#include <array>
//#include "Tile.h"
//class LevelManager 
//{
//
//private:
//
//	static LevelManager* s_pInstance;
//
//	LevelManager();
//	~LevelManager();
//	
//	std::map<int, Tile*> m_tiles;
//	std::array < std::array<Tile*, 360>, 204> m_level;
//
//
//public:
//
//	static LevelManager* Instance() 
//	{
//		if (s_pInstance == nullptr) 
//		{
//			s_pInstance = new LevelManager();
//		}
//		return s_pInstance;
//	}
//
//	void update();
//	void clean();
//	void render();
//
//	bool loadTiles();
//
//	
//
//};
//
//
//#endif