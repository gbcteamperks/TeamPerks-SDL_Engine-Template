#include "TextureManager.h"
#include "BackgroundEndS.h"

BackgroundEndS::BackgroundEndS()
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/Endsheet.txt",
		"../Assets/sprites/Endsheet.png",
		"Endsheet");

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("Endsheet");

	// set frame width
	setWidth(800);

	// set frame height
	setHeight(600);

	getTransform()->position = glm::vec2(400.0f, 300.0f); //center of the screen

	setType(BACKGROUND);

	m_buildAnimations();
	
}

BackgroundEndS::~BackgroundEndS()
= default;

void BackgroundEndS::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the plane sprite with simple propeller animation
	TheTextureManager::Instance()->playAnimation(
		"Endsheet", m_pAnimations["background"],
		x, y, 1.0f, 0, 255, true);
}

void BackgroundEndS::update()
{

}

void BackgroundEndS::clean()
{
}




void BackgroundEndS::setAnimation(const Animation & animation)
{
	m_pAnimations[animation.name] = animation;
}

void BackgroundEndS::m_buildAnimations()
{
	Animation backgroundAnimation = Animation();

	backgroundAnimation.name = "background";
	backgroundAnimation.frames.push_back(m_pSpriteSheet->getFrame("background1"));
	backgroundAnimation.frames.push_back(m_pSpriteSheet->getFrame("background2"));
	backgroundAnimation.frames.push_back(m_pSpriteSheet->getFrame("background3"));
	backgroundAnimation.frames.push_back(m_pSpriteSheet->getFrame("background4"));
	backgroundAnimation.frames.push_back(m_pSpriteSheet->getFrame("background5"));
	backgroundAnimation.frames.push_back(m_pSpriteSheet->getFrame("background6"));
	backgroundAnimation.frames.push_back(m_pSpriteSheet->getFrame("background7"));
	backgroundAnimation.frames.push_back(m_pSpriteSheet->getFrame("background8"));
	backgroundAnimation.frames.push_back(m_pSpriteSheet->getFrame("background9"));
	backgroundAnimation.frames.push_back(m_pSpriteSheet->getFrame("background10"));
	backgroundAnimation.frames.push_back(m_pSpriteSheet->getFrame("background11"));
	backgroundAnimation.frames.push_back(m_pSpriteSheet->getFrame("background12"));
	backgroundAnimation.frames.push_back(m_pSpriteSheet->getFrame("background13"));
	backgroundAnimation.frames.push_back(m_pSpriteSheet->getFrame("background14"));
	backgroundAnimation.frames.push_back(m_pSpriteSheet->getFrame("background15"));
	backgroundAnimation.frames.push_back(m_pSpriteSheet->getFrame("background16"));

	m_pAnimations["background"] = backgroundAnimation;
}
