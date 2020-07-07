#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	std::cout << "Clean called on StartScene" << std::endl;

	delete m_pTitleSprite;
	m_pTitleSprite = nullptr;
	
	delete m_pPlayButton;
	m_pPlayButton = nullptr;
	delete m_pLabelPlay;

	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}

	
}

void StartScene::start()
{

	m_pTitleSprite = new StaticSprite("../Assets/textures/MonsterSlayerTitle.png", "titleSprite", 400.0f, 300.0f);
	addChild(m_pTitleSprite);

	//Play Button
	m_pPlayButton = new Button("../Assets/textures/buttonRed.png", "PlayButton", PLAY_BUTTON);
	m_pPlayButton->getTransform()->position = glm::vec2(400.0f, 500.0f);
	m_pPlayButton->addEventListener(CLICK, [&](Button* button)-> void
	{
		button->setActive(false);
		SoundManager::Instance().stopMusic();
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pPlayButton->addEventListener(MOUSE_OVER, [&](Button* button)->void
	{
		button->setAlpha(128);
	});

	m_pPlayButton->addEventListener(MOUSE_OUT, [&](Button* button)->void
	{
		button->setAlpha(255);
	});
	addChild(m_pPlayButton);

	const SDL_Color white = { 255, 255, 255, 255 };
	m_pLabelPlay = new Label("Play", "Dock51", 40, white, glm::vec2(400.0f, 500.0f));
	m_pLabelPlay->setParent(this);
	addChild(m_pLabelPlay);

	//Music
	SoundManager::Instance().load("../Assets/audio/StartSceneMusic.mp3", "StartSceneMusic", SOUND_MUSIC);
	SoundManager::Instance().playMusic("StartSceneMusic");
	SoundManager::Instance().setAllVolume(20);
}

