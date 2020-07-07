#include "Sword.h"

Sword::Sword()
{
	m_running = false;
	m_damage = 0;


	TheTextureManager::Instance()->load("../Assets/textures/swordSilver.png", "sword");


	setWidth(30);
	setHeight(30);
	getRigidBody()->isColliding = false;


	setType(SWORD);
	
}

Sword::Sword(glm::vec2 position, bool running, int angle, bool pickeable)
{
	m_angle = angle;
	m_running = running;
	m_pickable = pickeable;
	m_damage = 0;

	TheTextureManager::Instance()->load("../Assets/textures/swordSilver.png", "sword");

	getTransform()->position = position;
	getRigidBody()->velocity += 0;
	glm::vec2 direction = { cos(m_angle * M_PI / 180.0) , sin(m_angle * M_PI / 180.0) };
	getRigidBody()->velocity *= direction;


	setWidth(30);//for collision
	setHeight(30);
	getRigidBody()->isColliding = false;

	if (m_pickable) {
		setType(PICKABLE);
	}
	else {
		setType(SWORD);
		getTransform()->position += (70.0f * direction);
	}
	start();
}

Sword::~Sword()
{
}

void Sword::update()
{
	
	if (abilityTimer > 15) {
		m_abilityDone = true;
	}
	abilityTimer++;
}

void Sword::draw()
{
	
	if (m_running) {
		TheTextureManager::Instance()->draw("sword", getTransform()->position.x, getTransform()->position.y, m_angle + 90, 255, true);
	}
}

void Sword::clean()
{
}

void Sword::start()
{
	if (m_pickable)
	{
		sound();
		//animation();
	}
}

void Sword::execute(glm::vec2 position, int angle)
{
	Game::Instance()->getCurrentScene()->addChild(new Sword(position, true, angle, false)); 
	SoundManager::Instance().playSound("Sword");
}

void Sword::stop()
{
	m_running = false;
}

void Sword::sound()
{
}

void Sword::animation()
{
}

void Sword::pickable(glm::vec2 position)
{
}
