#pragma once
#ifndef __TRANSITION_SCENE__
#define __TRANSITION_SCENE__

#include "Scene.h"
#include "StaticSprite.h"

class TransitionScene : public Scene
{
private:
	StaticSprite* m_pTransitionSprite{};
public:
	TransitionScene();
	~TransitionScene();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;


};

#endif
