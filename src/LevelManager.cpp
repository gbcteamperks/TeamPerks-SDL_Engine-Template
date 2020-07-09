#include "LevelManager.h"
#include "TextureManager.h"
#include "MathManager.h"
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
	if (x) 
	{
		m_sumDX += scroll;
	}
	else
	{
		m_sumDY += scroll;
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
	TextureManager::Instance()->load(spritePath, texture_Name);
	std::ifstream inFile(tileDataPath);
	if (inFile.is_open())
	{
		//create map of Tile Prototypes(what we copy to make the level)
		char key;
		int x, y;
		bool o, h;

		while (!inFile.eof())
		{
			inFile >> key >> x >> y >> o >> h;
			std::cout << "tile x " << x << " tile y " << y << "\n";
			m_tiles.emplace(key, new Tile("tiles", x, y, o, h));
		}
	
	}
	inFile.close();
	/*m_tiles[0]->setXY(31, 0);
	m_tiles[1]->setXY(63, 0);
	m_tiles[2]->setXY(95, 0);
	m_tiles[3]->setXY(127, 0);
	m_tiles[4]->setXY(159, 0);
	m_tiles[5]->setXY(31, 32);
	m_tiles[6]->setXY(63, 32);
	m_tiles[7]->setXY(95, 32);
	m_tiles[8]->setXY(127, 32);
	m_tiles[9]->setXY(159, 32);*/
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
				m_level[row][col]->getTransform()->position.x = (int)(col* Config::TILE_SIZE);
				m_level[row][col]->getTransform()->position.y = (int)(row* Config::TILE_SIZE);
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

bool LevelManager::checkCollision(GameObject* obj, const int dX, const int dY)
{
	int row = (obj->getTransform()->position.y - m_sumDY) / Config::TILE_SIZE;
	int col = (obj->getTransform()->position.x - m_sumDX) / Config::TILE_SIZE;

	
	//std::cout <<" x: "<<col << " y: " << row << "\n";
	SDL_Rect p = { obj->getTransform()->position.x + dX, obj->getTransform()->position.y + dY,obj->getWidth(),obj->getHeight()}; // Adjusted bounding box.
	//std::cout << "p " << " x " << p.x << " y " << p.y << " w " << p.w << " h " << p.h <<"\n";
	Tile* tiles[4] = { m_level[row][col],																				// Player's tile.
					   m_level[row][(col + 1 == Config::COL_NUM ? Config::COL_NUM - 1 : col + 1)],						// Right tile.
					   m_level[(row + 1 == Config::ROW_NUM ? Config::ROW_NUM - 1 : row + 1)][(col + 1 == Config::COL_NUM ? Config::COL_NUM - 1 : col + 1)],	// Bottom-Right tile.
					   m_level[(row + 1 == Config::ROW_NUM ? Config::ROW_NUM - 1 : row + 1)][col] // Bottom tile.
					};									
	for (int i = 0; i < 4; i++)
	{
		SDL_Rect t = MAMA::RectConverter(tiles[i]);
		//std::cout << i <<" x: " << tiles[i]->getTransform()->position.x <<"y: " << tiles[i]->getTransform()->position.y << "is obstacle" << tiles[i]->isObstacle() << "\n";
		if (tiles[i]->isObstacle())
		{	
			if (SDL_HasIntersection(&p, &t))
			{
				std::cout << "Collision" << std::endl;
				return true;
			}
		}
	}
	return false;
}
