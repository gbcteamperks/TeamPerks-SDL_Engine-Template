#include "PlayScene.h"
#include "Config.h"
#include <fstream>
#include <string>
PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	for (int row = 0; row < Config::ROW_NUM; row++)
	{
		for (int col = 0; col < Config::COL_NUM; col++)
		{
			
			m_level[row][col]->draw();
		
		}
	}
	drawDisplayList();
}

void PlayScene::update()
{
	updateDisplayList();
	
	//delete projectiles
	if (getDisplayList().size() > 0) {
		for (auto it = getDisplayList().begin(); it != getDisplayList().end();) {
			if ((*it)->getType() == PROJECTILE && (*it)->m_CheckBounds()) {
				(*it)->clean();
				delete (*it);
				it = getDisplayList().erase(it);
			}
			else {
				it++;
			}
		}
	}

}

void PlayScene::clean()
{
	delete m_pBackButton;
	m_pBackButton = nullptr;

	delete m_pNextButton;
	m_pNextButton = nullptr;


removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	// handle player movement with GameController
	if (SDL_NumJoysticks() > 0)
	{
		if (EventManager::Instance().getGameController(0) != nullptr)
		{
			const auto deadZone = 10000;
			if (EventManager::Instance().getGameController(0)->LEFT_STICK_X > deadZone)
			{
				m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < -deadZone)
			{
				m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
			}
		}
	}


	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
	{
		//----
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			//m_pVictorVanHelsing->getTransform()->position -= glm::vec2(playerSpeed, 0.0f);
			m_pVictorVanHelsing->setAnimationState(VICTOR_WALK_LEFT);
			
			if (m_pVictorVanHelsing->getTransform()->position.x /*> Config::SCREEN_WIDTH * 0.3f*/)
			{
				if (m_level[0][0]->getTransform()->position.x < 0)
				{
					updateLevel(playerSpeed, true);
				}
			}

			

		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			//m_pVictorVanHelsing->getTransform()->position += glm::vec2(playerSpeed, 0.0f);
			m_pVictorVanHelsing->setAnimationState(VICTOR_WALK_RIGHT);
			if (m_pVictorVanHelsing->getTransform()->position.x /*> Config::SCREEN_WIDTH * 0.7f*/)
			{
				if (m_level[0][Config::COL_NUM - 1]->getTransform()->position.x > Config::SCREEN_WIDTH - 32)
				{
					updateLevel(-playerSpeed, true);
				}
			}
		
		}
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
		{
			//m_pVictorVanHelsing->getTransform()->position -= glm::vec2(0.0f, playerSpeed);
			m_pVictorVanHelsing->setAnimationState(VICTOR_WALK_UP);
			if (m_pVictorVanHelsing->getTransform()->position.y /*< Config::SCREEN_HEIGHT * 0.3f*/)
			{
				if (m_level[0][0]->getTransform()->position.y < 0)
				{
					updateLevel(playerSpeed, false);
				}
			}
			
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
		{
			//m_pVictorVanHelsing->getTransform()->position += glm::vec2(0.0f, playerSpeed);
			m_pVictorVanHelsing->setAnimationState(VICTOR_WALK_DOWN);
			if (m_pVictorVanHelsing->getTransform()->position.y /*> Config::SCREEN_HEIGHT * 0.7f*/)
			{
				if (m_level[Config::ROW_NUM - 1][0]->getTransform()->position.y > Config::SCREEN_HEIGHT - 32)
				{
					updateLevel(-playerSpeed, false);
				}
			}
		}
	}


	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}
	//Change Ability
	if (EventManager::Instance().KeyReleased(SDL_SCANCODE_E))
	{
		m_pVictorVanHelsing->changeAbility();
	}
	//Use Current Ability
	if (EventManager::Instance().KeyReleased(SDL_SCANCODE_Q)) 
	{
		m_pVictorVanHelsing->useCurrentAbility();
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}

	collisions();
}

void PlayScene::start()
{
	
	// 
	//m_pPlaneSprite = new PlaneSprite();
	//addChild(m_pPlaneSprite);

	loadTiles("../Assets/sprites/TileTest.png", "tiles", "../Assets/sprites/TileData.txt");
	std::cout << "here\n";
	loadLevel("../Assets/data/Level1.txt");

	std::cout << "start";

	//boss hits
	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(200.0f, 200.0f);
	addChild(m_pTarget);

	//Boss
	m_pBossOne = new BossOne();
	m_pBossOne->getTransform()->position = glm::vec2(90.0f, 90.0f);
	m_pBossOne->getBullet(m_pTarget);
	m_pBossOne->addAbility(new Fireball());
	addChild(m_pBossOne);

	//Victor
	m_pVictorVanHelsing = new VictorVanHelsing();
	m_pVictorVanHelsing->getTransform()->position = glm::vec2(390.0f, 400.0f);
	m_pVictorVanHelsing->addAbility(new Sword());
	addChild(m_pVictorVanHelsing);
	

}

void PlayScene::collisions()
{

	bool changeState = false;
	//Probably we have to change this "auto it", for int it = 0
	for (auto it = getDisplayList().begin(); it != getDisplayList().end();it++) {
		for (auto kt = getDisplayList().begin(); kt != getDisplayList().end();kt++) {
			if ((*it) != nullptr && (*kt) != nullptr) {
				if ((*it)->getType() == SWORD && (*kt)->getType() == BOSS) {
					if (CollisionManager::AABBCheck((*it), (*kt))) {
						m_pBossOne->dropAbility();
						(*kt)->clean();
						delete (*kt);
						(*kt) = nullptr;
					}
				
				}
				else if ((*it)->getType() == VICTOR && (*kt)->getType() == PICKABLE) {
					if (CollisionManager::AABBCheck((*it), (*kt))) {
						dynamic_cast<VictorVanHelsing*>((*it))->addAbility(new Fireball());
						(*kt)->clean();
						delete (*kt);
						(*kt) = nullptr;
					}
				}
				else if ((*it)->getType() == PROJECTILE && (*kt)->getType() == VICTOR) {
					if (CollisionManager::AABBCheck((*it), (*kt))) {
						changeState = true;
					}
				}
			}
			
		}
	}
	getDisplayList().erase(std::remove(getDisplayList().begin(), getDisplayList().end(), nullptr),getDisplayList().end());
	if (changeState) {
		TheGame::Instance()->changeSceneState(END_SCENE);
	}

}

void PlayScene::loadTiles(std::string spritePath, std::string name,std::string tileData)
{
	/*std::string path = spritePath;
	std::string nam = name;
	std::string data = tileData;*/
	

	std::ifstream inFile(tileData);
	if (inFile.is_open()) 
	{
		//create map of Tile Prototypes(what we copy to make the level)
		char key;
		int x, y;
		bool o, h;
		int i = 1;
		TheTextureManager::Instance()->load(spritePath, name);
	/*	std::string path = "../Assets/sprites/" +1;
		std::cout << path << std::endl;*/
		while (!inFile.eof()) 
		{
			/*std::string n = 'T' + std::to_string(i);
			std::string png = n + ".png"; 
			std::cout << path + png << std::endl;*/
			inFile >> key >> x >> y >> o >> h;
			m_tiles.emplace(key, new Tile("tiles", x, y, o, h));
			//i++;
			
		}
	}
	inFile.close();
	
	
}

void PlayScene::loadLevel(std::string dataPath)
{
	
	std::ifstream inFile(dataPath);
	if (inFile.is_open()) 
	{
		//build level from tiles
		char key;
		for (int row = 0; row < Config::ROW_NUM; row++) 
		{
			for (int col = 0; col < Config::COL_NUM; col++)
			{
				std::cout << "start" << col << " " << row;
				inFile >> key;
				m_level[row][col] = m_tiles[key]->Clone();
				m_level[row][col]->getTransform()->position.x = (float)64 * col;
				m_level[row][col]->getTransform()->position.y = (float)64 * row;
				//add obstacles
			}
		}
	}
	inFile.close();
}

void PlayScene::updateLevel(float scroll, bool x)
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

