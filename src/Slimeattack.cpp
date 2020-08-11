#include "Slimeattack.h"

#include "LevelManager.h"

Slimeattack::Slimeattack()
{
	m_running = false;
	m_pDamage = 10;
	TheTextureManager::Instance()->load("../Assets/Sprites/slimeattack.png", "slimeattack");

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("slimeattack");
	setWidth(size.x);
	setHeight(size.y);
	getRigidBody()->isColliding = false;
	//getTransform()->position = glm::vec2(100.0f, 100.0f);
	m_specialAbility = true;
	setType(ENEMYABILITY);

}
Slimeattack::Slimeattack(glm::vec2 position, bool running, int angle, bool pickeable, bool enemyAbility)
{
	m_angle = angle;
	m_running = running;
	m_pickable = pickeable;
	m_pDamage = 10;
	m_specialAbility = true;
	
	getTransform()->position = position;
	getRigidBody()->velocity = { 3, 3 };
	glm::vec2 direction = { cos(m_angle * M_PI / 180.0) , sin(m_angle * M_PI / 180.0) };
	getRigidBody()->velocity *= direction;

	TheTextureManager::Instance()->load("../Assets/Sprites/slimeattack.png", "slimeattack");

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

Slimeattack::~Slimeattack()
{
}

void Slimeattack::update()
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

	if (checkCollisionWithLevel(LVLMAN::Instance()->getObstacles()))
	{
		m_running = false;
	}

}

void Slimeattack::draw()
{
	if (m_running && !m_pickable)
	{
		TheTextureManager::Instance()->draw("slimeattack", getTransform()->position.x, getTransform()->position.y, m_angle - 90, 255, true);
	}
	else if (m_running && m_pickable)
	{
		TheTextureManager::Instance()->playAnimation("BlueGem", m_pAnimations["BlueGem"],
			getTransform()->position.x, getTransform()->position.y, 0.50f, 0, 255, true);
	}
}

void Slimeattack::clean()
{

}

void Slimeattack::start()
{
	if (m_pickable)
	{
		sound();
		animation();
	}

}

void Slimeattack::execute(glm::vec2 position, int angle, bool enemyAbility)
{
	Game::Instance()->getCurrentScene()->addChild(new Slimeattack(position, true, angle, false, enemyAbility));
	//SoundManager::Instance().playSound("sound_forSlime!");

}

void Slimeattack::stop()
{
	m_running = false;
	m_abilityDone = true;
}

void Slimeattack::sound()
{
	if (m_running) {

	}
}

void Slimeattack::animation()
{
	if (m_running && !m_pickable) {

	}
}

void Slimeattack::pickable(glm::vec2 position)
{
	Game::Instance()->getCurrentScene()->addChild(new Slimeattack(position, true, 0, true, false));
}
