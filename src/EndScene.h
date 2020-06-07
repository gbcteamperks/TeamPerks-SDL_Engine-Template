#pragma once
#ifndef __END_SCENE__
#define __END_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Button.h"
#include "BackgroundEndS.h"

class EndScene final : public Scene
{
public:
	EndScene();
	~EndScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	
	BackgroundEndS* m_pBackgroundEndS{};
	
	Button* m_pMenuButton;
	Label* m_pLabelMenu{};

	Button* m_pRestartButton;
	Label* m_pLabelRestart{};
	Label* m_label{};
};

#endif /* defined (__END_SCENE__) */