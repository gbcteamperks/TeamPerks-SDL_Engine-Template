#pragma once
#ifndef __TRANSITION_SCENE__
#define __TRANSITION_SCENE__

#include "Scene.h"
#include "StaticSprite.h"
#include "Label.h"
#include "Game.h"

class TransitionScene : public Scene
{
private:
	StaticSprite* m_pTransitionSprite{};
	Label* m_pText{};
	int alpha = 128;
	bool goClean = false;
	
public:
	TransitionScene();
	~TransitionScene();

	bool goToClean();
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;


};

#endif