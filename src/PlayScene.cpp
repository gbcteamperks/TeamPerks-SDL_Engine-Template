#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

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
			m_pPlaneSprite->getTransform()->position -= glm::vec2(2.0f, 0.0f);
			m_pTarget->m_move();
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_pPlaneSprite->getTransform()->position += glm::vec2(2.0f, 0.0f);
		}
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
		{
			m_pPlaneSprite->getTransform()->position -= glm::vec2(0.0f, 2.0f);
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
		{
			m_pPlaneSprite->getTransform()->position += glm::vec2(0.0f, 2.0f);
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

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}

	//-- CHECK FOR COLLISION OF ALL OBJECTS!
	for (int i = 0; i < numberOfChildren(); i++)
	{
		for (int j = i + 1; j < numberOfChildren(); j++)
		{
			if (CollisionManager::AABBCheck(getDisplayList()[i], getDisplayList()[j]))
			{
				std::cout << "\nCollision!! of " << getDisplayList()[i]->getType() << " and " << getDisplayList()[j]->getType();
			}
		}
	}
}

void PlayScene::start()
{
	// Plane Sprite
	m_pPlaneSprite = new PlaneSprite();
	addChild(m_pPlaneSprite);

	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);
	m_pPlayer->getTransform()->position = glm::vec2(30.0f, 30.0f);

	// Player Sprite
	//m_pShip = new Ship();
	//addChild(m_pShip);

	// Player Sprite
	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(200.0f, 200.0f);
	addChild(m_pTarget);


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

	addChild(m_pNextButton);
}
