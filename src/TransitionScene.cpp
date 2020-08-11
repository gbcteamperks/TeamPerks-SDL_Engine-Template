#include "TransitionScene.h"
#include "TextureManager.h"
#include "Renderer.h"
#include <iostream>
#include "Config.h"

TransitionScene::TransitionScene()
{
	m_pTransitionSprite = new StaticSprite("../Assets/textures/whitebackground.png", "whitebackground", 0.0f, 0.0f);
	const SDL_Color red = { 185, 0, 28, 255 };
	m_pText = new Label("Level Completed! Proceeding to next..", "sot", 60, red, glm::vec2(520.0f, 400.0f));
	m_pText->setParent(this);
	addChild(m_pText);
}

TransitionScene::~TransitionScene()
{
}

bool TransitionScene::goToClean()
{
	return goClean;
}

void TransitionScene::draw()
{
	if(alpha<255)
	{
		m_pTransitionSprite->draw(alpha++);
	}
	else
	{
		m_pTransitionSprite->draw(alpha);
		std::cout << alpha << std::endl;
	}
	
	drawDisplayList();
	
}
void TransitionScene::update()
{
	if(alpha == 255)
	{
		SDL_Delay(3500);
		//TheGame::Instance()->changeSceneState(PLAY_SCENE);
		goClean = true;
		clean();
	}
}

void TransitionScene::clean()
{
	TheGame::Instance()->getCurrentScene()->clean();
	PlayScene::listPlayers[0]->getLife() += 30;
	if(PlayScene::listPlayers[0]->getLife() > 100)
	{
		PlayScene::listPlayers[0]->getLife() = 100;
	}
	TheGame::Instance()->changeSceneState(PLAY_SCENE);
	delete m_pTransitionSprite;
	m_pTransitionSprite = nullptr;
}

void TransitionScene::handleEvents()
{
}

void TransitionScene::start()
{

}