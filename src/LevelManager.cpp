#include "LevelManager.h"
#include "TextureManager.h"
#include "MathManager.h"
#include "Util.h"
#include "PlayScene.h"
#include <fstream>

LevelManager* LevelManager::s_pInstance = nullptr;

LevelManager::LevelManager() = default;
LevelManager::~LevelManager() = default;


void LevelManager::update(float scroll, bool x)
{

	for (auto i : m_obstacles)
	{
		if (i->getType() == DESTRUCTIBLE)
		{
			i->update();
		
		}
		
	}
	//for (int row = 0; row < Config::ROW_NUM; row++)
	//{
	//	for (int col = 0; col < Config::COL_NUM; col++)
	//	{
	//		if (x)
	//		{
	//			m_level[row][col]->getTransform()->position.x += scroll;
	//		}
	//		else
	//		{
	//			m_level[row][col]->getTransform()->position.y += scroll;
	//		}
	//	}
	//}
	//if (x) 
	//{
	//	m_sumDX += scroll;
	//}
	//else
	//{
	//	m_sumDY += scroll;
	//}
}

void LevelManager::clean()
{
	//Cleaning as Alex would say "Wrangle your Dangle"
	clearLevel();
	clearTiles();
}

void LevelManager::render(bool debug)
{
	//Draw out the tiles
	for (int row = 0; row < Config::ROW_NUM; row++)
	{
		for (int col = 0; col < Config::COL_NUM; col++)
		{
			m_level[row][col]->draw();

			if (debug) 
			{
				if (m_level[row][col]->m_node->isOpen()) 
				{
					Util::DrawRect({ m_level[row][col]->getPosX(), m_level[row][col]->getPosY() }, m_level[row][col]->getWidth(), m_level[row][col]->getHeight(), { 0.0f,0.0f,1.0f,1.0f });
				}
				else 
				{
					Util::DrawRect({ m_level[row][col]->getPosX(), m_level[row][col]->getPosY() }, m_level[row][col]->getWidth(), m_level[row][col]->getHeight(), { 1.0f,0.0f,0.0f,1.0f });
				}
			}
		}
	}

	for (auto i : m_obstacles) 
	{
		if (i->getType() == DESTRUCTIBLE) 
		{
			i->draw();
			
		}
		if (debug)
		{
			if (i->getType() == DESTRUCTIBLE) 
			{
				//Util::DrawRect({ i->getPosX() /*- i->getWidth()*/, i->getPosY() /*- i->getHeight() */ }, i->getWidth(), i->getHeight(), { 1.0f,1.0f,1.0f,1.0f });
			}
			else {
				//Util::DrawRect({ i->getPosX(), i->getPosY() }, i->getWidth(), i->getHeight(), { 1.0f,1.0f,1.0f,1.0f });
			}
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
}

void LevelManager::loadLevel(std::string levelDataPath,std::vector<DisplayObject*>& dList) //Passes the scene display list to add obstacles and hazard tiles
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
				if (key == 'b') 
				{
					m_level[row][col] = m_tiles['F']->Clone();
				}
				else 
				{ 
					m_level[row][col] = m_tiles[key]->Clone(); 
				}
				m_level[row][col]->getTransform()->position.x = (int)(col * Config::TILE_SIZE);
				m_level[row][col]->getTransform()->position.y = (int)(row * Config::TILE_SIZE);

				if (key == 'b') 
				{
					dList.push_back(new DestructibleObject(m_level[row][col]->getTransform()->position, 3, "../Assets/sprites/barrel.txt",
						"../Assets/sprites/barrel.png","barrel",50,60,30,40));
				}
				
				
				m_level[row][col]->m_node = new PathNode((int)(m_level[row][col]->getTransform()->position.x + 16), (int)(m_level[row][col]->getTransform()->position.y + 16));

				/*m_level[row][col]->setPosX(m_level[row][col]->m_node->x);
				m_level[row][col]->setPosX(m_level[row][col]->m_node->y);*/
				m_level[row][col]->setPosX(m_level[row][col]->getTransform()->position.x);
				m_level[row][col]->setPosY(m_level[row][col]->getTransform()->position.y);
				if (m_level[row][col]->getX() == 4 && m_level[row][col]->getY() == 1) //if the index nums match up to where the door tile is on the texture make the tile a door game object
				{
					m_level[row][col]->setType(SPIKES);
				}

				if (m_level[row][col]->isObstacle() || m_level[row][col]->isHazard()) //If tile is an obstacle add it to the obstacle list
				{
					m_obstacles.push_back(m_level[row][col]);
					m_level[row][col]->m_node->toggleNode();
				}
			}
		}
	}
	inFile.close();
	

	for (int i = 0; i < dList.size(); i++) 
	{
		if (dList[i]->getType() == DESTRUCTIBLE) 
		{
		m_obstacles.push_back(dList[i]);
		}
	}
}


void LevelManager::clearTiles()
{
	for (int t = 0; t < m_tiles.size(); t++)
	{
		delete m_tiles[t];
		m_tiles[t] = nullptr;
	}
	m_tiles.clear();
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
	m_obstacles.clear();
}

void LevelManager::drawObstaclesCollisionBox()
{
	for (auto o : m_obstacles)
	{
		if (o->getType() == DESTRUCTIBLE)
		{
			Util::DrawRect(glm::vec2(o->getPosX(), o->getPosY()), o->getColX(), o->getColY(), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else 
		{
			Util::DrawRect(glm::vec2(o->getPosX(), o->getPosY()), o->getWidth(), o->getHeight(), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}

bool LevelManager::checkCollision(GameObject* obj, const int dX, const int dY) //kinda took this out
{
	//int row = ((obj->getTransform()->position.y - m_sumDY) / Config::TILE_SIZE);
	//int col = ((obj->getTransform()->position.x - m_sumDX) / Config::TILE_SIZE);
	//const int numTiles = 4;
	//
	////std::cout <<" x: "<<col << " y: " << row << "\n";
	//SDL_Rect p = { obj->getTransform()->position.x + dX, obj->getTransform()->position.y + dY,obj->getWidth(),obj->getHeight()}; // Adjusted bounding box.
	////std::cout << "p " << " x " << p.x << " y " << p.y << " w " << p.w << " h " << p.h <<"\n";
	//Tile* tiles[numTiles] = { m_level[row][col],																				// Player's tile.
	//				   m_level[row][(col + 1 == Config::COL_NUM ? Config::COL_NUM - 1 : col + 1)],						// Right tile.
	//				   m_level[(row + 1 == Config::ROW_NUM ? Config::ROW_NUM - 1 : row + 1)][(col + 1 == Config::COL_NUM ? Config::COL_NUM - 1 : col + 1)],	// Bottom-Right tile.
	//				   m_level[(row + 1 == Config::ROW_NUM ? Config::ROW_NUM - 1 : row + 1)][col] // Bottom tile.
	//				};

	//for (int i = 0; i < numTiles; i++)
	//{
	//	

	//	SDL_Rect t = MAMA::RectConverter(tiles[i]);
	//	//std::cout << i <<" x: " << tiles[i]->getTransform()->position.x <<"y: " << tiles[i]->getTransform()->position.y << "is obstacle" << tiles[i]->isObstacle() << "\n";
	//	if (tiles[i]->isObstacle())
	//	{	
	//		if (SDL_HasIntersection(&p, &t))
	//		{
	//			std::cout << "Collision" << std::endl;
	//			return true;
	//		}
	//	}
	//}
	return false;
}

void LevelManager::printNodes()
{
	for (int row = 0; row < Config::ROW_NUM; row++)
	{
		for (int col = 0; col < Config::COL_NUM; col++)
		{
			if (m_level[row][col]->m_node != nullptr) 
			{
				std::cout << "Node at x: " << m_level[row][col]->m_node->x << " y: " << m_level[row][col]->m_node->y <<"\n";
			}
			
		}
	}
}

void LevelManager::cleanObstacles()
{
}
