#include "LevelManager.h"
#include "TextureManager.h"
#include <fstream>

LevelManager* LevelManager::s_pInstance = nullptr;

LevelManager::LevelManager() = default;
LevelManager::~LevelManager() = default;


void LevelManager::update(float scroll, bool x)
{
	for (int row = 0; row < Config::ROW_NUM; row++)
	{
		for (int col = 0; col < Config::COL_NUM; col++)
		{
			if (x)
			{
				m_level[row][col]->getTransform()->position.x += scroll;
			}
			else
			{
				m_level[row][col]->getTransform()->position.y += scroll;
			}
		}
	}
}

void LevelManager::clean()
{

	clearLevel();
	clearTiles();
}

void LevelManager::render()
{
	for (int row = 0; row < Config::ROW_NUM; row++)
	{
		for (int col = 0; col < Config::COL_NUM; col++)
		{
			
			m_level[row][col]->draw();
		
		}
	}
}

void LevelManager::loadTiles(std::string spritePath, std::string texture_Name, std::string tileDataPath)
{
	std::ifstream inFile(tileDataPath);
	if (inFile.is_open())
	{
		//create map of Tile Prototypes(what we copy to make the level)
		char key;
		int x, y;
		bool o, h;
		int i = 1;
		TheTextureManager::Instance()->load(spritePath, texture_Name);
		while (!inFile.eof())
		{
			inFile >> key >> x >> y >> o >> h;
			m_tiles.emplace(key, new Tile("tiles", x, y, o, h));
		}
	}
	inFile.close();
}

void LevelManager::loadLevel(std::string levelDataPath)
{
	std::ifstream inFile(levelDataPath);
	if (inFile.is_open())
	{
		//build level from tiles
		char key;
		for (int row = 0; row < Config::ROW_NUM; row++)
		{
			for (int col = 0; col < Config::COL_NUM; col++)
			{
				inFile >> key;
				m_level[row][col] = m_tiles[key]->Clone();
				m_level[row][col]->getTransform()->position.x = (float)64 * col;
				m_level[row][col]->getTransform()->position.y = (float)64 * row;
			}
		}
	}
	inFile.close();
}

void LevelManager::clearTiles()
{
	for (int row = 0; row < Config::ROW_NUM; row++)
	{
		for (int col = 0; col < Config::COL_NUM; col++)
		{

			

		}
	}
}

void LevelManager::clearLevel()
{
	for (int row = 0; row < Config::ROW_NUM; row++)
	{
		for (int col = 0; col < Config::COL_NUM; col++)
		{
			delete m_level[row][col];
			m_level[row][col] = nullptr;
		}
	}
}
