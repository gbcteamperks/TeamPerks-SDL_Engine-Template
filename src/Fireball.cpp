#include "Fireball.h"

Fireball::Fireball()
{
	//m_velocity = 6;
	m_running = false;
	m_damage = 0;

	//getTransform()->position = glm::vec2(0.0f,0.0f);
	TheTextureManager::Instance()->load("../Assets/Sprites/magicenemy-projectile.png", "circle");

	auto size = TheTextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);
	getRigidBody()->isColliding = false;
	//getTransform()->position = glm::vec2(100.0f, 100.0f);
	
	setType(PROJECTILE);
}
Fireball::Fireball(glm::vec2 position, bool running, int angle, bool pickeable)
{
	m_angle = angle;
	m_running = running;
	m_pickable = pickeable;
	m_damage = 0;

	getTransform()->position = position;
	getRigidBody()->velocity += 6.0;
	glm::vec2 direction = { cos(m_angle * M_PI / 180.0) , sin(m_angle * M_PI / 180.0) };
	getRigidBody()->velocity *= direction;

	TheTextureManager::Instance()->load("../Assets/Sprites/magicenemy-projectile.png", "circle");
	TheTextureManager::Instance()->load("../Assets/texture/buttonRed.png", "blackRect");

	setWidth(30);
	setHeight(30);
	getRigidBody()->isColliding = false;
	if (m_pickable) {
		setType(PICKABLE);
	}
	else {
		setType(PROJECTILE);
		getTransform()->position += (80.0f * direction);
	}
	start();
}

Fireball::~Fireball()
{
}

void Fireball::update()
{
	if (m_running && !m_pickable) 
	{
		getTransform()->position += getRigidBody()->velocity;
	}
}

void Fireball::draw()
{
	if (m_running && !m_pickable)
	{
		TheTextureManager::Instance()->draw("circle", getTransform()->position.x, getTransform()->position.y, m_angle -90 , 255, true);
	}
	else if (m_running && m_pickable) 
	{
		TheTextureManager::Instance()->draw("circle", getTransform()->position.x, getTransform()->position.y, 90, 255, true);
		TheTextureManager::Instance()->draw("blackRect", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
	}
}

void Fireball::clean()
{
	
}

void Fireball::start()
{
	if (m_pickable) 
	{
		sound();
		animation();
	}
	
}

void Fireball::execute(glm::vec2 position, int angle)
{
	//getTransform()->position = position;
	Game::Instance()->getCurrentScene()->addChild(new Fireball(position, true, angle, false));
	
}

void Fireball::stop()
{
	m_running = false;
}

void Fireball::sound()
{
	if (m_running) {

	}
}

void Fireball::animation()
{
	if (m_running && !m_pickable) {

	}
}

void Fireball::pickable(glm::vec2 position)
{	
	Game::Instance()->getCurrentScene()->addChild(new Fireball(position, true, 0, true));
}
