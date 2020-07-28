#include "EndScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

EndScene::EndScene()
{
	EndScene::start();
}

EndScene::~EndScene()
= default;

void EndScene::draw()
{
	drawDisplayList();
}

void EndScene::update()
{
	updateDisplayList();
}

void EndScene::clean()
{
	delete m_pBackgroundEndS;
	m_pBackgroundEndS = nullptr;

	delete m_pMenuButton;
	m_pMenuButton = nullptr;
	delete m_pLabelMenu;

	delete m_pRestartButton;
	m_pRestartButton = nullptr;
	delete m_pLabelRestart;

	delete m_label;
	
	removeAllChildren();
}

void EndScene::handleEvents()
{
	EventManager::Instance().update();

	// Button Events
	m_pRestartButton->update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void EndScene::start()
{

	m_pBackgroundEndS = new BackgroundEndS();
	addChild(m_pBackgroundEndS);

	for (int i = 0; i < getDisplayList().size();i++) 
	{
		if (getDisplayList()[i]->getType() == VICTOR) 
		{
			getDisplayList()[i]->getLife() = 100;
		}
	}

	//Menu Button

	m_pMenuButton = new Button("../Assets/textures/buttonRed.png", "MenuButton", START_BUTTON);
	m_pMenuButton->getTransform()->position = glm::vec2(240.0f, 350.0f);
	m_pMenuButton->addEventListener(CLICK, [&](Button* button)-> void
		{
			button->setActive(false);
			TheGame::Instance()->changeSceneState(START_SCENE);
		});

	m_pMenuButton->addEventListener(MOUSE_OVER, [&](Button* button)->void
		{
			button->setAlpha(128);
		});

	m_pMenuButton->addEventListener(MOUSE_OUT, [&](Button* button)->void
		{
			button->setAlpha(255);
		});

	addChild(m_pMenuButton);
	//label Menu Button
	const SDL_Color white = { 255, 255, 255, 255 };
	m_pLabelMenu = new Label("Menu", "Dock51", 40, white, glm::vec2(240.0f, 350.0f));
	m_pLabelMenu->setParent(this);
	addChild(m_pLabelMenu);


	// Restart Button
	m_pRestartButton = new Button("../Assets/textures/buttonRed.png", "restartButton", RESTART_BUTTON);
	m_pRestartButton->getTransform()->position = glm::vec2(560.0f, 350.0f);
	m_pRestartButton->addEventListener(CLICK, [&](Button* button)-> void
	{
		button->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});

	m_pRestartButton->addEventListener(MOUSE_OVER, [&](Button* button)->void
	{
		button->setAlpha(128);
	});

	m_pRestartButton->addEventListener(MOUSE_OUT, [&](Button* button)->void
	{
		button->setAlpha(255);
	});

	addChild(m_pRestartButton);

	m_pLabelRestart = new Label("Restart", "Dock51", 40, white, glm::vec2(560.0f, 350.0f));
	m_pLabelRestart->setParent(this);
	addChild(m_pLabelRestart);

	//GameOver Label
	const SDL_Color red = { 255, 0, 0, 255 };
	m_label = new Label("GAME OVER", "Dock51", 80, red, glm::vec2(400.0f, 200.0f));
	m_label->setParent(this);
	addChild(m_label);
}
