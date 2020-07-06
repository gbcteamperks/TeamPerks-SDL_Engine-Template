#include "PlayScene.h"
#include "MotherSpider.h"
#include "EnemyWizard.h"
#include "VictorVanHelsing.h"
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
		for (auto it = getDisplayList().begin(); it != getDisplayList().end();it++) {
			if ((*it)->getType() == PROJECTILE && (*it)->m_CheckBounds()) 
			{
				(*it)->clean();
				delete (*it);
				(*it) = nullptr;
			}
			else if ((*it)->getParentType() == ABILITY) 
			{
				if (dynamic_cast<Ability*>(*it)->getAbilityDone())
				{
					(*it)->clean();
					delete (*it);
					(*it) = nullptr;
				}
			}

		}
	}
	getDisplayList().erase(std::remove(getDisplayList().begin(), getDisplayList().end(), nullptr), getDisplayList().end());

}

void PlayScene::clean()
{
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
			if (EventManager::Instance().getGameController(0)->START_BUTTON)
			{
				if (listPlayers.size() < 2)
				{
					listPlayers.push_back(new VictorVanHelsing(glm::vec2(500.0f, 400.0f)));
					addChild(listPlayers[1]);
				}
			}
			if (listPlayers.size() > 1)
			{
				const auto deadZone = 10000;
				if (EventManager::Instance().getGameController(0)->LEFT_STICK_X[1] > deadZone)
				{
					listPlayers[1]->getTransform()->position += glm::vec2(playerSpeed, 0.0f);
					listPlayers[1]->setAnimationState(VICTOR_WALK_RIGHT);
					if (listPlayers[1]->getTransform()->position.x /*> Config::SCREEN_WIDTH * 0.7f*/)
					{
						if (LVLMAN::Instance()->getLevel()[0][Config::COL_NUM - 1]->getTransform()->position.x > Config::SCREEN_WIDTH - 32)
						{
							LVLMAN::Instance()->update(-playerSpeed, true);
						}
					}
				}
				if (EventManager::Instance().getGameController(0)->LEFT_STICK_X[1] < -deadZone)
				{
					listPlayers[1]->getTransform()->position -= glm::vec2(playerSpeed, 0.0f);
					listPlayers[1]->setAnimationState(VICTOR_WALK_LEFT);

					if (listPlayers[1]->getTransform()->position.x /*> Config::SCREEN_WIDTH * 0.3f*/)
					{
						if (LVLMAN::Instance()->getLevel()[0][0]->getTransform()->position.x < 0)
						{
							LVLMAN::Instance()->update(playerSpeed, true);
						}
					}
				}
				if (EventManager::Instance().getGameController(0)->LEFT_STICK_Y[1] < -deadZone)
				{
					listPlayers[1]->getTransform()->position -= glm::vec2(0.0f, playerSpeed);
					listPlayers[1]->setAnimationState(VICTOR_WALK_UP);
					if (listPlayers[1]->getTransform()->position.y /*< Config::SCREEN_HEIGHT * 0.3f*/)
					{
						if (LVLMAN::Instance()->getLevel()[0][0]->getTransform()->position.y < 0)
						{
							LVLMAN::Instance()->update(playerSpeed, false);
						}
					}
				}
				if (EventManager::Instance().getGameController(0)->LEFT_STICK_Y[1] > deadZone)
				{
					listPlayers[1]->getTransform()->position += glm::vec2(0.0f, playerSpeed);
					listPlayers[1]->setAnimationState(VICTOR_WALK_DOWN);
					if (listPlayers[1]->getTransform()->position.y /*> Config::SCREEN_HEIGHT * 0.7f*/)
					{
						if (LVLMAN::Instance()->getLevel()[Config::ROW_NUM - 1][0]->getTransform()->position.y > Config::SCREEN_HEIGHT - 32)
						{
							LVLMAN::Instance()->update(-playerSpeed, false);
						}
					}
				}
				//Change Ability
				if (EventManager::Instance().getGameController(0)->Arealeased())
				{
					listPlayers[1]->changeAbility();
				}
				//Use Current Ability
				if (EventManager::Instance().getGameController(0)->Brealeased())
				{
					listPlayers[1]->useCurrentAbility(2);
				}
			}
		}
	}

	//KeyBoard
		//----
	playerSpeed = 2.0f;
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_LSHIFT)) 
	{
		playerSpeed = 5.0f;
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		listPlayers[0]->getTransform()->position -= glm::vec2(playerSpeed, 0.0f);
		listPlayers[0]->setAnimationState(VICTOR_WALK_LEFT);
			
		if (listPlayers[0]->getTransform()->position.x /*> Config::SCREEN_WIDTH * 0.3f*/)
		{
			if (LVLMAN::Instance()->getLevel()[0][0]->getTransform()->position.x < 0)
			{
				LVLMAN::Instance()->update(playerSpeed, true);
			}
		}
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		listPlayers[0]->getTransform()->position += glm::vec2(playerSpeed, 0.0f);
		listPlayers[0]->setAnimationState(VICTOR_WALK_RIGHT);
		if (listPlayers[0]->getTransform()->position.x /*> Config::SCREEN_WIDTH * 0.7f*/)
		{
			if (LVLMAN::Instance()->getLevel()[0][Config::COL_NUM - 1]->getTransform()->position.x > Config::SCREEN_WIDTH - 32)
			{
				LVLMAN::Instance()->update(-playerSpeed, true);
			}
		}
		
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		listPlayers[0]->getTransform()->position -= glm::vec2(0.0f, playerSpeed);
		listPlayers[0]->setAnimationState(VICTOR_WALK_UP);
		if (listPlayers[0]->getTransform()->position.y /*< Config::SCREEN_HEIGHT * 0.3f*/)
		{
			if (LVLMAN::Instance()->getLevel()[0][0]->getTransform()->position.y < 0)
			{
				LVLMAN::Instance()->update(playerSpeed, false);
			}
		}
			
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		listPlayers[0]->getTransform()->position += glm::vec2(0.0f, playerSpeed);
		listPlayers[0]->setAnimationState(VICTOR_WALK_DOWN);
		if (listPlayers[0]->getTransform()->position.y /*> Config::SCREEN_HEIGHT * 0.7f*/)
		{
			if (LVLMAN::Instance()->getLevel()[Config::ROW_NUM - 1][0]->getTransform()->position.y > Config::SCREEN_HEIGHT - 32)
			{
				LVLMAN::Instance()->update(-playerSpeed, false);
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
		listPlayers[0]->changeAbility();
	}
	//Use Current Ability
	if (EventManager::Instance().KeyReleased(SDL_SCANCODE_Q)) 
	{
		listPlayers[0]->useCurrentAbility(1);
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

	//Boss
	addChild(new EnemyWizard());

	//Victor
	listPlayers.push_back(new VictorVanHelsing(glm::vec2(390.0f, 400.0f)));
	addChild(listPlayers[0]);

	//BigSpider
	addChild(new MotherSpider());
	
}

void PlayScene::collisions()
{

	bool changeState = false;
	
	for (int i = 0; i < getDisplayList().size(); i++) {
		for (int k = 0; k < getDisplayList().size();k++) 
		{
			if (getDisplayList()[i] != nullptr && getDisplayList()[k] != nullptr) {
				if (getDisplayList()[i]->getType() == SWORD && getDisplayList()[k]->getType() == BOSS)
				{
					if (CollisionManager::AABBCheck(getDisplayList()[i], getDisplayList()[k])) {
						dynamic_cast<Enemy*>(getDisplayList()[k])->dropAbility();
						getDisplayList()[k]->clean();
						delete getDisplayList()[k];
						getDisplayList()[k] = nullptr;
					}
				
				}
				else if (getDisplayList()[i]->getType() == VICTOR && getDisplayList()[k]->getType() == PICKABLE)
				{
					if (CollisionManager::AABBCheck(getDisplayList()[i], getDisplayList()[k])) {
						dynamic_cast<VictorVanHelsing*>(getDisplayList()[i])->addAbility(dynamic_cast<Ability*>(getDisplayList()[k])->getAbility());
						getDisplayList()[k]->clean();
						delete getDisplayList()[k];
						getDisplayList()[k] = nullptr;
					}
				}
				else if (getDisplayList()[i]->getType() == PROJECTILE && getDisplayList()[k]->getType() == VICTOR)
				{
					if (CollisionManager::AABBCheck(getDisplayList()[i], getDisplayList()[k])) {
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


