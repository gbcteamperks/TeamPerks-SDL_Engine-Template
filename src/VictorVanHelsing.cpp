#include "VictorVanHelsing.h"
#include "TextureManager.h"
#include "CollisionManager.h"

VictorVanHelsing::VictorVanHelsing()
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png",
		"spritesheet");

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("spritesheet");

	// set frame width
	setWidth(65);

	// set frame height
	setHeight(65);

	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLANE);

	m_buildAnimations();
	m_pObject = this;
}

VictorVanHelsing::~VictorVanHelsing()
= default;

void VictorVanHelsing::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the plane sprite with simple propeller animation
	TheTextureManager::Instance()->playAnimation(
		"spritesheet", m_pAnimations["plane"],
		x, y, 0.5f, 0, 255, true);
}

void VictorVanHelsing::update()
{
	GameObject::m_BoundsRestrict();
}

void VictorVanHelsing::clean()
{
}


void VictorVanHelsing::setAnimation(const Animation & animation)
{
	m_pAnimations[animation.name] = animation;
}

void VictorVanHelsing::m_buildAnimations()
{
	Animation planeAnimation = Animation();

	planeAnimation.name = "plane";
	planeAnimation.frames.push_back(m_pSpriteSheet->getFrame("plane1"));
	planeAnimation.frames.push_back(m_pSpriteSheet->getFrame("plane2"));
	planeAnimation.frames.push_back(m_pSpriteSheet->getFrame("plane3"));

	m_pAnimations["plane"] = planeAnimation;
}




