#include "PlayScene.h"
#include "MotherSpider.h"
#include "EnemyWizard.h"
#include "VictorVanHelsing.h"
#include "Config.h"
#include "LevelManager.h"
#include <fstream>
#include <string>
#include "RatKing.h"
#include "SpawnEnemiesManager.h"
#include "SkeletonEnemy.h"
#include "Util.h"
#include "CrazyBat.h"
#include "King.h"
std::vector<VictorVanHelsing*> PlayScene::listPlayers;
int PlayScene::levelNumber = 1;
PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	LVLMAN::Instance()->render(m_debugView);
	drawDisplayList();
	if (m_debugView)
	{
		for (auto o : getDisplayList())
		{
			
			if (o->getType() != DESTRUCTIBLE) {
				Util::DrawRect({ o->getPosX(), o->getPosY() }, o->getWidth(), o->getHeight(), { 1.0f,1.0f,1.0f,1.0f });
			}
			Util::DrawRect({ listPlayers[0]->getPosX()+8,listPlayers[0]->getPosY()+32 }, 16, 16, { 0.0f,1.0f,1.0f,1.0f });
			
		}
		LevelManager::Instance()->drawObstaclesCollisionBox();

	}
}
void PlayScene::update()
{
	if (!gamePaused) 
	{
		collisions();
		if (enemyKillCount > 4)
		{
			//successful = true;
			summonBoss = true;
		}

		if (!summonBoss)
		{
			updateDisplayList();
			switch (levelNumber)
			{
			case 1:
				SpawnEnemiesManager::level1();
				break;
			case 2:
				SpawnEnemiesManager::level2();
				break;
			case 3:
				summonBoss = true;
				break;
			default:
				SpawnEnemiesManager::level1();
				break;
			}
			//delete projectiles
			if (getDisplayList().size() > 0) {
				for (auto it = getDisplayList().begin(); it != getDisplayList().end(); it++) {
					if (((*it)->getType() == ENEMYABILITY || (*it)->getType() == PLAYERABILITY) && (*it)->m_CheckBounds())
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
		else
		{
			//update to the transition scene
			/*std::cout << "Update transiton" << std::endl;
			invokeTransition();*/
			updateDisplayList();
			//SpawnEnemiesManager::level1();
			//delete projectiles
			if (getDisplayList().size() > 0) {
				for (auto it = getDisplayList().begin(); it != getDisplayList().end(); it++) {
					if (((*it)->getType() == ENEMYABILITY || (*it)->getType() == PLAYERABILITY) && (*it)->m_CheckBounds())
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

			switch (getLevelNumber())
			{
			case 1:
				SpawnEnemiesManager::level1Boss();
				break;
			case 2:
				SpawnEnemiesManager::level2Boss();
				break;
			default:
				SpawnEnemiesManager::level3Boss();
				break;
			}
			
		}

		if (presuccessful && levelNumber!=1)
		{
			if(m_currentTime == 0)
			{
				m_currentTime = (int)SDL_GetTicks() / 1000;
			}
			if(((int)SDL_GetTicks()/1000) - m_currentTime > 4)
			{
				successful = true;
				invokeTransition();
			}
			
		}
		else if (presuccessful && levelNumber == 1)
		{
			successful = true;
			invokeTransition();
		}
		LevelManager::Instance()->update(5, true);
	}
	
}

void PlayScene::clean()
{
	VictorVanHelsing::numberOfPlayers = 0;
	LVLMAN::Instance()->clean();
	SoundManager::Instance().stopMusic();

	removeAllChildren();
}

void PlayScene::handleEvents()
{
	if(!successful)
	{
		EventManager::Instance().update();

		if (!gamePaused)
		{
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
					listPlayers[1]->handleEventsController();
				}
			}

			//KeyBoard
			listPlayers[0]->handleEventsKeyboard();
			


			
		}
		


		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			TheGame::Instance()->quit();
		}
		if (EventManager::Instance().KeyReleased(SDL_SCANCODE_H)) // debug view
		{
			m_debugView = !m_debugView;
		}
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_T))
		{
			LVLMAN::Instance()->printNodes();

			/*std::cout << "x: " << LevelManager::Instance()->getLevel()[5][10]->m_node->x << " y:" << LevelManager::Instance()->getLevel()[5][10]->m_node->y << "\n";
			listPlayers[0]->getTransform()->position.x = LVLMAN::Instance()->getLevel()[5][10]->m_node->x;
			listPlayers[0]->getTransform()->position.y = LVLMAN::Instance()->getLevel()[5][10]->m_node->y;*/
		}
		if (EventManager::Instance().KeyReleased(SDL_SCANCODE_P))
		{
			gamePaused = !gamePaused;
		}	
		if (EventManager::Instance().KeyReleased(SDL_SCANCODE_0))
		{
			invokeTransition();
		}
		if (EventManager::Instance().KeyReleased(SDL_SCANCODE_8))
		{
			listPlayers[0]->getLife() = 1;
		}
	

	}
	else
	{
		//invoking transition.
	}
	
}



void PlayScene::collisions()
{

	for (int i = 0; i < getDisplayList().size(); i++) {
		for (int k = 0; k < getDisplayList().size();k++) 
		{
			if (getDisplayList()[i] != nullptr && getDisplayList()[k] != nullptr) {
				//PLAYER ABILITIES AND ENEMIES
				if (getDisplayList()[i]->getType() == PLAYERABILITY && getDisplayList()[k]->getType() == ENEMY)
				{
					if (dynamic_cast<Ability*>(getDisplayList()[i])->IsRunning())
					{
						// **** Its the same code as the ability and boss check ****
						if (CollisionManager::AABBCheckBoss(getDisplayList()[i], getDisplayList()[k])) {
							dynamic_cast<Ability*>(getDisplayList()[i])->stop();
							if ((getDisplayList()[k])->getLife() > 0) {

								getDisplayList()[k]->getLife() -= getDisplayList()[i]->getDamage();
							}
							if ((getDisplayList()[k])->getLife() <= 0) {
								dynamic_cast<Enemy*>(getDisplayList()[k])->dropAbility();
								getDisplayList()[k]->clean();
								delete getDisplayList()[k];
								getDisplayList()[k] = nullptr;
								enemyKillCount++;
							}
						}
					}
				}	
				
				else if (getDisplayList()[i]->getType() == PLAYERABILITY && getDisplayList()[k]->getType() == DESTRUCTIBLE)
				{
					if (dynamic_cast<Ability*>(getDisplayList()[i])->IsRunning())
					{
						// **** Its the same code as the ability and boss check ****
						if (CollisionManager::AbilityAABBCheck(getDisplayList()[i], getDisplayList()[k])) {
							dynamic_cast<Ability*>(getDisplayList()[i])->stop();
							if ((getDisplayList()[k])->getLife() > 0) {

								getDisplayList()[k]->getLife() -= 1;
							}
							if ((getDisplayList()[k])->getLife() <= 0) {
								getDisplayList()[k]->clean();
								delete getDisplayList()[k];
								getDisplayList()[k] = nullptr;
							}
						}
					}
				}
				//PlAYER ABILITY AND BOSS
				else if (getDisplayList()[i]->getType() == PLAYERABILITY && getDisplayList()[k]->getType() == BOSS)
				{
					if (dynamic_cast<Ability*>(getDisplayList()[i])->IsRunning())
					{
						if (CollisionManager::AABBCheckBoss(getDisplayList()[i], getDisplayList()[k])) {
							dynamic_cast<Ability*>(getDisplayList()[i])->stop();
							if ((getDisplayList()[k])->getLife() > 0) {

								getDisplayList()[k]->getLife() -= getDisplayList()[i]->getDamage();
							}
							if ((getDisplayList()[k])->getLife() <= 0) {
								dynamic_cast<Enemy*>(getDisplayList()[k])->dropAbility();
								getDisplayList()[k]->clean();
								delete getDisplayList()[k];
								getDisplayList()[k] = nullptr;
								presuccessful = true;
							}
						}
					}
				}

				//VICTOR AND PICKEABLE OBJECTS
				else if (getDisplayList()[i]->getType() == VICTOR && getDisplayList()[k]->getType() == PICKABLE)
				{
					if (dynamic_cast<Ability*>(getDisplayList()[k])->IsRunning())
					{
						if (CollisionManager::AABBCheck(getDisplayList()[i], getDisplayList()[k])) {
							dynamic_cast<VictorVanHelsing*>(getDisplayList()[i])->addAbility(dynamic_cast<Ability*>(getDisplayList()[k])->getAbility());
							dynamic_cast<Ability*>(getDisplayList()[k])->stop();
						}
					}
				}
				//VICTOR AND ENEMYABILITIES
				else if (getDisplayList()[i]->getType() == VICTOR && getDisplayList()[k]->getType() == ENEMYABILITY)
				{
					if (dynamic_cast<Ability*>(getDisplayList()[k])->IsRunning())
					{
						if (CollisionManager::AABBCheck(getDisplayList()[k], getDisplayList()[i])) {
							dynamic_cast<Ability*>(getDisplayList()[k])->stop();
							getDisplayList()[i]->getLife() -= getDisplayList()[k]->getDamage();
							if(dynamic_cast<Ability*>(getDisplayList()[k])->isSpecialAbility())
							{
								if(!listPlayers[0]->isVictorSlow())
								{
									listPlayers[0]->slowEffect();
									m_slowTimer = (int)SDL_GetTicks() / 1000.0f;
									
								}
							}
							SoundManager::Instance().playSound("Grunt");
					
						}
					}
				}
				//VICTOR WITH DOOR
				else if (getDisplayList()[i]->getType() == VICTOR && getDisplayList()[k]->getType() == DOOR)
				{
					if (CollisionManager::AABBCheck(getDisplayList()[i], getDisplayList()[k])) {
						
						std::cout << " x: " << getDisplayList()[k]->getTransform()->position.x << " y: " << getDisplayList()[k]->getTransform()->position.y << "\n";
						std::cout << "Hit Door\n";
					}
				}
				//VICTOR WITH ENEMIES
				else if (getDisplayList()[i]->getType() == VICTOR && getDisplayList()[k]->getType() == ENEMY)
				{
					if (CollisionManager::AABBCheck(getDisplayList()[k], getDisplayList()[i])) {

						getDisplayList()[i]->getLife() -= 5;
						SoundManager::Instance().playSound("Grunt");
						
					}
				}

				//VICTOR WITH ENEMIES
				else if (getDisplayList()[i]->getType() == VICTOR && getDisplayList()[k]->getType() == BOSS)
				{
					if (CollisionManager::AABBCheck(getDisplayList()[k], getDisplayList()[i])) {

						getDisplayList()[i]->getLife() -= 5;
						SoundManager::Instance().playSound("Grunt");
						
					}
				}
				
			}
		}
	}

	if(listPlayers[0]->isVictorSlow())
	{
		if ((SDL_GetTicks() / 1000.0f) - m_slowTimer > 5)
		{
			listPlayers[0]->slowEffect();
			m_slowTimer = 0;
		}
	}
	

	if (listPlayers[0]->getLife() <= 0) 
	{
		listPlayers[0]->getLife() = 100;
		levelNumber = 1;
		TheGame::Instance()->changeSceneState(END_SCENE);
	}

	getDisplayList().erase(std::remove(getDisplayList().begin(), getDisplayList().end(), nullptr),getDisplayList().end());
	LVLMAN::Instance()->cleanObstacles();


}

bool PlayScene::tileCollision(GameObject* obj)
{
	return false;
}

int PlayScene::getLevelNumber()
{
	return levelNumber;
}

void PlayScene::invokeTransition()
{
	
	levelNumber++;
	//std::cout << levelNumber <<"\n"<< std::endl;
	TheGame::Instance()->changeSceneState(TRANSITION_SCENE);

}
void PlayScene::start()
{
	//LVLMAN::Instance()->loadTiles("../Assets/sprites/Level1_Tiles.png", "tiles", "../Assets/sprites/TileData.txt");

	std::cout << "start" << levelNumber << "\n" << std::endl;
	gamePaused = false;
	switch (levelNumber)
	{
	case 1:
		levelNumberConcatenate = "../Assets/data/Level" + std::to_string((levelNumber)) + ".txt";
		tileNumberConcatenate = "../Assets/sprites/Level" + std::to_string((levelNumber)) + "_Tiles.png";
		break;

	case 2:
		levelNumberConcatenate = "../Assets/data/Level" + std::to_string((levelNumber)) + ".txt";
		tileNumberConcatenate = "../Assets/sprites/Level" + std::to_string((levelNumber)) + "_Tiles.png";
		break;

	case 3:
		levelNumberConcatenate = "../Assets/data/Level" + std::to_string((levelNumber)) + ".txt";
		tileNumberConcatenate = "../Assets/sprites/Level" + std::to_string((levelNumber)) + "_Tiles.png";
		break;

	default:
		break;
	}
	LVLMAN::Instance()->loadTiles(tileNumberConcatenate, "tiles", "../Assets/sprites/TileData.txt");
	LVLMAN::Instance()->loadLevel(levelNumberConcatenate,getDisplayList());
	std::cout << "start";

	
	//Victor
	listPlayers.push_back(new VictorVanHelsing(glm::vec2(525.0f, 150.0f)));
	addChild(listPlayers[0]);
	int x, y;
	switch (levelNumber)
	{
	case 1:
		break;
	case 2:
		x = Config::SCREEN_WIDTH * .5;
		y = Config::SCREEN_HEIGHT*0.2;
		for (auto p : PlayScene::listPlayers) {
			p->getTransform()->position = glm::vec2(x, y);
			x = x + 50;
		}
		break;
	case 3:
		x = Config::SCREEN_WIDTH*.5;
		y = Config::SCREEN_HEIGHT * .5;
		for (auto p : PlayScene::listPlayers) {
			p->getTransform()->position = glm::vec2(x, y);
			x = x + 50;
		}
		break;
	}


	//Music
	SoundManager::Instance().load("../Assets/audio/PlaySceneMusic.mp3", "PlaySceneMusic", SOUND_MUSIC);
	SoundManager::Instance().playMusic("PlaySceneMusic");
	//Sound fx
	SoundManager::Instance().load("../Assets/audio/sword-1b.wav", "Sword", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/Rat.mp3", "Rat", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/Fireball.wav", "FireBall", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/electricshock.wav", "Orb", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/Grunting-sound.mp3", "Grunt", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/tailwhip.wav", "whip", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/slimespit.wav", "slimy", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/ratbiter.wav", "ratbiter", SOUND_SFX);
}


