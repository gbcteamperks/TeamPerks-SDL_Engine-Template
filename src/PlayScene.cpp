#include "PlayScene.h"


PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
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
			m_pVictorVanHelsing->getTransform()->position -= glm::vec2(2.0f, 0.0f);
			m_pVictorVanHelsing->setAnimationState(VICTOR_WALK_LEFT);
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_pVictorVanHelsing->getTransform()->position += glm::vec2(2.0f, 0.0f);
			m_pVictorVanHelsing->setAnimationState(VICTOR_WALK_RIGHT);
		}
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
		{
			m_pVictorVanHelsing->getTransform()->position -= glm::vec2(0.0f, 2.0f);
			m_pVictorVanHelsing->setAnimationState(VICTOR_WALK_UP);
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
		{
			m_pVictorVanHelsing->getTransform()->position += glm::vec2(0.0f, 2.0f);
			m_pVictorVanHelsing->setAnimationState(VICTOR_WALK_DOWN);
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

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_Q))
	{
		if (m_pVictorVanHelsing->isAbilityReady()) {
			m_pVictorVanHelsing->useCurrentAbility();
			m_pVictorVanHelsing->abilityNotReady();
		}
	}
	if (EventManager::Instance().isKeyUp(SDL_SCANCODE_Q))
	{
		m_pVictorVanHelsing->abilityReady();
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_E))
	{
		if (m_changeAbilityReady) {
			m_pVictorVanHelsing->changeAbility();
			m_changeAbilityReady = false;
		}
	}
	if (EventManager::Instance().isKeyUp(SDL_SCANCODE_E))
	{
		m_changeAbilityReady = true;
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

	m_pBkg = new StaticSprite("../Assets/textures/map_testing.png", "titleSprite", 400.0f, 300.0f);
	addChild(m_pBkg);


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
	
/*

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(300.0f, 400.0f);
	m_pBackButton->addEventListener(CLICK, [&](Button* button)-> void
	{
		button->setActive(false);
		TheGame::Instance()->changeSceneState(START_SCENE);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&](Button* button)->void
	{
		button->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&](Button* button)->void
	{
		button->setAlpha(255);
	});
	addChild(m_pBackButton);

	// Next Button
	m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	m_pNextButton->getTransform()->position = glm::vec2(500.0f, 400.0f);
	m_pNextButton->addEventListener(CLICK, [&](Button* button)-> void
	{
		button->setActive(false);
		TheGame::Instance()->changeSceneState(END_SCENE);
	});

	m_pNextButton->addEventListener(MOUSE_OVER, [&](Button* button)->void
	{
		button->setAlpha(128);
	});

	m_pNextButton->addEventListener(MOUSE_OUT, [&](Button* button)->void
	{
		button->setAlpha(255);
	});

	addChild(m_pNextButton);*/
}

void PlayScene::collisions()
{
	bool removeChild = false;
	const auto list = getDisplayList();
	//-- CHECK FOR COLLISION OF ALL OBJECTS!
	//for (int i = 0; i < numberOfChildren(); i++)
	//{
	//	for (int j = 0; j < numberOfChildren(); j++)
	//	{
	//		if (getDisplayList()[i]->getType() == SWORD && getDisplayList()[j]->getType() == BOSS) 
	//		{
	//			if (CollisionManager::AABBCheck(getDisplayList()[i], getDisplayList()[j]))
	//			{
	//				std::cout << "collision detected" << std::endl;
	//				m_pBossOne->dropAbility();
	//				//TheGame::Instance()->changeSceneState(END_SCENE);

	//				//std::cout << "\nCollision!! of " << getDisplayList()[i]->getType() << " and " << getDisplayList()[j]->getType();
	//			}
	//		}
	//		if (getDisplayList()[i]->getType() == PICKABLE && getDisplayList()[j]->getType() == VICTOR)
	//		{
	//			if (CollisionManager::AABBCheck(getDisplayList()[i], getDisplayList()[j]))
	//			{
	//				dynamic_cast<VictorVanHelsing*>(getDisplayList()[j])->addAbility(new Fireball());
	//				removeChild = true;
	//			}
	//		}
	//		
	//	}
	//}
	/*if (removeChild) {
		removeChildByType(PICKABLE);
	}*/
	bool changeState = false;
	for (auto it = getDisplayList().begin(); it != getDisplayList().end();it++) {
		for (auto kt = getDisplayList().begin(); kt != getDisplayList().end();) {
			if ((*it)->getType() == SWORD && (*kt)->getType() == BOSS) {
				if (CollisionManager::AABBCheck((*it), (*kt))) {
					std::cout << "collision detected" << std::endl;
					
					m_pBossOne->dropAbility();
					(*kt)->clean();
					delete (*kt);
					kt = getDisplayList().erase(kt);
					it = getDisplayList().begin();
					//loop = false;
				}
				else {
					kt++;
				}
			}
			else if ((*it)->getType() == VICTOR && (*kt)->getType() == PICKABLE) {
				if (CollisionManager::AABBCheck((*it), (*kt))) {
					std::cout << "collision detected" << std::endl;
					dynamic_cast<VictorVanHelsing*>((*it))->addAbility(new Fireball());
					(*kt)->clean();
					delete (*kt);
					kt = getDisplayList().erase(kt);
					it = getDisplayList().begin();
				}
				else {
					kt++;
				}
			}
			else if ((*it)->getType() == PROJECTILE && (*kt)->getType() == VICTOR) {
				if (CollisionManager::AABBCheck((*it), (*kt))) {
					changeState = true;
				}
				kt++;
			}
			else {
				kt++;
			}
		}
	}
	if (changeState) {
		TheGame::Instance()->changeSceneState(END_SCENE);
	}

}
