#include "TransitionScene.h"
#include "TextureManager.h"
#include "Renderer.h"
#include <iostream>
#include "Config.h"

TransitionScene::TransitionScene()
{
	//whiteBackground = new TransitionSceneBackground();
	m_pTransitionSprite = new StaticSprite("../Assets/textures/whitebackground.png", "whitebackground", 0.0f, 0.0f);
	addChild(m_pTransitionSprite);
}

TransitionScene::~TransitionScene()
{
}

void TransitionScene::draw()
{
	//whiteBackground->draw();
	m_pTransitionSprite->draw(128);
}
void TransitionScene::update()
{

}

void TransitionScene::clean()
{
}

void TransitionScene::handleEvents()
{
}

void TransitionScene::start()
{
	
}
