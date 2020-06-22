#include "Sword.h"

Sword::Sword()
{
	m_running = false;
	m_damage = 0;

	//getTransform()->position = glm::vec2(0.0f,0.0f);
	TheTextureManager::Instance()->load("../Assets/textures/swordSilver.png", "sword");

	//auto size = TheTextureManager::Instance()->getTextureSize("sword");
	setWidth(30);
	setHeight(30);
	getRigidBody()->isColliding = false;
	//getTransform()->position = glm::vec2(100.0f, 100.0f);

	setType(SWORD);
	
}

Sword::Sword(glm::vec2 position, bool running, int angle, bool pickeable)
{
}

Sword::~Sword()
{
}

void Sword::update()
{
	static int c = 15; //timer
	if (m_initialiazed) {
		c = 0;
		m_initialiazed = false;
		m_running = true;
	}
	if (c < 15) { //do the animation

	}
	else {
		m_running = false;
	}
	c++;
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
	glm::vec2 direction = { cos(m_angle * M_PI / 180.0) , sin(m_angle * M_PI / 180.0) };
	getTransform()->position += (60.0f * direction);
}

void Sword::execute(glm::vec2 position, int angle)
{
	if (!m_addedToDisplay) {
		Game::Instance()->getCurrentScene()->addChild(this); //add the pointer to this instance.
		m_addedToDisplay = true;
	}
	getTransform()->position = position;
	m_angle = angle;
	m_initialiazed = true;
	start();
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
