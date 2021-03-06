#include "Fireball.h"

Fireball::Fireball()
{
	//m_velocity = 6;
	m_running = false;
	m_pDamage = 5;
	//getTransform()->position = glm::vec2(0.0f,0.0f);
	TheTextureManager::Instance()->load("../Assets/Sprites/magicenemy-projectile.png", "circle");

	auto size = TheTextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);
	getRigidBody()->isColliding = false;
	//getTransform()->position = glm::vec2(100.0f, 100.0f);
	
	setType(ENEMYABILITY);

}
Fireball::Fireball(glm::vec2 position, bool running, int angle, bool pickeable, bool enemyAbility)
{
	m_angle = angle;
	m_running = running;
	m_pickable = pickeable;
	m_pDamage = 15;

	getTransform()->position = position;
	getRigidBody()->velocity = { 6.0f, 6.0f };
	glm::vec2 direction = { cos(m_angle * M_PI / 180.0) , sin(m_angle * M_PI / 180.0) };
	getRigidBody()->velocity *= direction;

	TheTextureManager::Instance()->load("../Assets/Sprites/magicenemy-projectile.png", "circle");

	setWidth(30);
	setHeight(30);
	getRigidBody()->isColliding = false;
	if (m_pickable) {
		setType(PICKABLE);
	}
	else {
		getTransform()->position += (70.0f * direction);
		if (enemyAbility) {
			setType(ENEMYABILITY);
		}
		else {
			setType(PLAYERABILITY);
		}
	}
	start();
}

Fireball::~Fireball()
{
}

void Fireball::update()
{
	setPosX(getTransform()->position.x - getWidth() * 0.5);
	setPosY(getTransform()->position.y - getHeight() * 0.5);

	if (m_running && !m_pickable) 
	{
		Move(getRigidBody()->velocity.x, getRigidBody()->velocity.y);
	}
	else if (m_running && m_pickable)
	{
		m_pickeableTimer++;
		if (m_pickeableTimer > 300)
			m_abilityDone = true;
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
		TheTextureManager::Instance()->playAnimation("BlueGem", m_pAnimations["BlueGem"],
			getTransform()->position.x, getTransform()->position.y, 0.50f, 0, 255, true);
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

void Fireball::execute(glm::vec2 position, int angle, bool enemyAbility)
{
	//getTransform()->position = position;
	Game::Instance()->getCurrentScene()->addChild(new Fireball(position, true, angle, false, enemyAbility));
	SoundManager::Instance().playSound("FireBall");
	
}

void Fireball::stop()
{
	m_running = false;
	m_abilityDone = true;
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
	Game::Instance()->getCurrentScene()->addChild(new Fireball(position, true, 0, true, false));
}
