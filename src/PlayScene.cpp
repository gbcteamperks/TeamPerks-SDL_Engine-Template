#include "PlayScene.h"
#include "MotherSpider.h"
#include "Config.h"
#include "LevelManager.h"
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
	LVLMAN::Instance()->render();
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

	LVLMAN::Instance()->clean();

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
		playerSpeed = 2.0f;
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_LSHIFT)) 
		{
			playerSpeed = 5.0f;
		}
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			m_pVictorVanHelsing->getTransform()->position -= glm::vec2(playerSpeed, 0.0f);
			m_pVictorVanHelsing->setAnimationState(VICTOR_WALK_LEFT);
			
			if (m_pVictorVanHelsing->getTransform()->position.x /*> Config::SCREEN_WIDTH * 0.3f*/)
			{
				if (LVLMAN::Instance()->getLevel()[0][0]->getTransform()->position.x < 0)
				{
					LVLMAN::Instance()->update(playerSpeed, true);
				}
			}

			

		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_pVictorVanHelsing->getTransform()->position += glm::vec2(playerSpeed, 0.0f);
			m_pVictorVanHelsing->setAnimationState(VICTOR_WALK_RIGHT);
			if (m_pVictorVanHelsing->getTransform()->position.x /*> Config::SCREEN_WIDTH * 0.7f*/)
			{
				if (LVLMAN::Instance()->getLevel()[0][Config::COL_NUM - 1]->getTransform()->position.x > Config::SCREEN_WIDTH - 32)
				{
					LVLMAN::Instance()->update(-playerSpeed, true);
				}
			}
		
		}
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
		{
			m_pVictorVanHelsing->getTransform()->position -= glm::vec2(0.0f, playerSpeed);
			m_pVictorVanHelsing->setAnimationState(VICTOR_WALK_UP);
			if (m_pVictorVanHelsing->getTransform()->position.y /*< Config::SCREEN_HEIGHT * 0.3f*/)
			{
				if (LVLMAN::Instance()->getLevel()[0][0]->getTransform()->position.y < 0)
				{
					LVLMAN::Instance()->update(playerSpeed, false);
				}
			}
			
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
		{
			m_pVictorVanHelsing->getTransform()->position += glm::vec2(0.0f, playerSpeed);
			m_pVictorVanHelsing->setAnimationState(VICTOR_WALK_DOWN);
			if (m_pVictorVanHelsing->getTransform()->position.y /*> Config::SCREEN_HEIGHT * 0.7f*/)
			{
				if (LVLMAN::Instance()->getLevel()[Config::ROW_NUM - 1][0]->getTransform()->position.y > Config::SCREEN_HEIGHT - 32)
				{
					LVLMAN::Instance()->update(-playerSpeed, false);
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
	LVLMAN::Instance()->loadTiles("../Assets/sprites/TileTest.png", "tiles", "../Assets/sprites/TileData.txt");
	LVLMAN::Instance()->loadLevel("../Assets/data/Level1.txt");
	
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

	//BigSpider
	addChild(new MotherSpider());
	
	for (int row = 0; row < Config::ROW_NUM; row++)
	{
		for (int col = 0; col < Config::COL_NUM; col++)
		{

			if (LVLMAN::Instance()->getLevel()[row][col]->isObstacle() == true)
			{
				addChild(LVLMAN::Instance()->getLevel()[row][col]);
			}

		}
	}
}

void PlayScene::collisions()
{

	bool changeState = false;
	//Probably we have to change this "auto it", for int it = 0
	for (auto it = getDisplayList().begin(); it != getDisplayList().end();it++) {
		for (auto kt = getDisplayList().begin(); kt != getDisplayList().end();kt++) 
		{
			if ((*it) != nullptr && (*kt) != nullptr) {
				if ((*it)->getType() == SWORD && (*kt)->getType() == BOSS) 
				{
					if (CollisionManager::AABBCheck((*it), (*kt))) {
						m_pBossOne->dropAbility();
						(*kt)->clean();
						delete (*kt);
						(*kt) = nullptr;
					}
				
				}
				else if ((*it)->getType() == VICTOR && (*kt)->getType() == PICKABLE) 
				{
					if (CollisionManager::AABBCheck((*it), (*kt))) {
						dynamic_cast<VictorVanHelsing*>((*it))->addAbility(new Fireball());
						(*kt)->clean();
						delete (*kt);
						(*kt) = nullptr;
					}
				}
				else if ((*it)->getType() == PROJECTILE && (*kt)->getType() == VICTOR) 
				{
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


