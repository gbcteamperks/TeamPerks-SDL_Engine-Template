#include "Orb.h"

Orb::Orb()
{
	//m_velocity = 6;
	m_running = false;
	m_pDamage = 15;

	//getTransform()->position = glm::vec2(0.0f,0.0f);
	TheTextureManager::Instance()->load("../Assets/Sprites/spiderExplode.png", "spiderExplode");

	getRigidBody()->isColliding = false;
	//getTransform()->position = glm::vec2(100.0f, 100.0f);

	setType(ENEMYABILITY);
}
Orb::Orb(glm::vec2 position, bool running, int angle, bool pickeable, bool enemyAbility)
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/orbProjectile.txt",
		"../Assets/sprites/orbprojectile.png",
		"orbing");

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("orbing");

	m_pSpriteSheet->setWidthAndHeight(64, 64);

	m_angle = angle;
	m_running = running;
	m_pickable = pickeable;
	m_pDamage = 15;


	//animation
	m_currentAnimationState = PLAYER_RUN_LEFT;
	m_buildAnimations();

	getTransform()->position = position;
	getRigidBody()->velocity += 2.0;
	glm::vec2 direction = { cos(m_angle * M_PI / 180.0) , sin(m_angle * M_PI / 180.0) };
	getRigidBody()->velocity *= direction;
	

	setWidth(30);//for collision
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

Orb::~Orb()
{
}

void Orb::update()
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

void Orb::draw()
{
	animation();
}

void Orb::clean()
{

}

void Orb::start()
{
	if (m_pickable)
	{
		sound();
		//animation();
	}

}

void Orb::execute(glm::vec2 position, int angle, bool enemyAbility)
{
	//getTransform()->position = position;
	Game::Instance()->getCurrentScene()->addChild(new Orb(position, true, angle, false,enemyAbility));
	SoundManager::Instance().playSound("Orb");

}

void Orb::stop()
{
	m_running = false;
	m_abilityDone = true;
}

void Orb::sound()
{
	if (m_running) {

	}
}

void Orb::animation()
{
	// draw the player according to animation state
	if (m_running && !m_pickable)
	{
		TheTextureManager::Instance()->playAnimation("orbing", m_pAnimations["orbing"],
			getTransform()->position.x, getTransform()->position.y, 0.50f, 0, 255, true);
	}
	else if (m_running && m_pickable)
	{
		TheTextureManager::Instance()->playAnimation("BlueGem", m_pAnimations["BlueGem"],
			getTransform()->position.x, getTransform()->position.y, 0.50f, 0, 255, true);
	}
	

}
void Orb::m_buildAnimations()
{
	Animation animation = Animation();

	animation.name = "orbing";

	animation.frames.push_back(m_pSpriteSheet->getFrame("orb1"));
	animation.frames.push_back(m_pSpriteSheet->getFrame("orb2"));
	animation.frames.push_back(m_pSpriteSheet->getFrame("orb3"));
	animation.frames.push_back(m_pSpriteSheet->getFrame("orb4"));
	animation.frames.push_back(m_pSpriteSheet->getFrame("orb5"));
	animation.frames.push_back(m_pSpriteSheet->getFrame("orb6"));
	animation.frames.push_back(m_pSpriteSheet->getFrame("orb7"));

	m_pAnimations["orbing"] = animation;

}

void Orb::AnimateDeath()
{
	// alias for x and y
	/*const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	float animationVelocity = 0.50f;
	if (TheTextureManager::Instance()->playAnimation("explosionSpider", m_pAnimations["Explosion"],
		x, y, animationVelocity, 0, 255, true))
	{
		m_abilityDone = true;
	}*/

}
void Orb::pickable(glm::vec2 position)
{
	Game::Instance()->getCurrentScene()->addChild(new Orb(position, true, 0, true, false));
}