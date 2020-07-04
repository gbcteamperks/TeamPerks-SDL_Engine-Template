#include "Orb.h"

Orb::Orb()
{
	//m_velocity = 6;
	m_running = false;
	m_damage = 0;

	//getTransform()->position = glm::vec2(0.0f,0.0f);
	TheTextureManager::Instance()->load("../Assets/Sprites/spiderExplode.png", "spiderExplode");

	getRigidBody()->isColliding = false;
	//getTransform()->position = glm::vec2(100.0f, 100.0f);

	setType(PROJECTILE);
}
Orb::Orb(glm::vec2 position, bool running, int angle, bool pickeable)
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/orbProjectile.txt",
		"../Assets/sprites/orbprojectile.png",
		"orbing");
	//gem for pickeable
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/gem.txt",
		"../Assets/sprites/Items_BlueGem.png",
		"BlueGem");


	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("orbing");
	m_pSpriteSheetGem = TheTextureManager::Instance()->getSpriteSheet("BlueGem");

	m_pSpriteSheetGem->setWidthAndHeight(64, 64);
	m_pSpriteSheet->setWidthAndHeight(64, 64);

	m_angle = angle;
	m_running = running;
	m_pickable = pickeable;
	m_damage = 0;


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
		setType(PROJECTILE);
		getTransform()->position += (70.0f * direction);
	}
	start();
}

Orb::~Orb()
{
}

void Orb::update()
{
	if (m_running && !m_pickable)
	{
		getTransform()->position += getRigidBody()->velocity;
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

void Orb::execute(glm::vec2 position, int angle)
{
	//getTransform()->position = position;
	Game::Instance()->getCurrentScene()->addChild(new Orb(position, true, angle, false));

}

void Orb::stop()
{
	m_running = false;
}

void Orb::sound()
{
	if (m_running) {

	}
}

void Orb::animation()
{

	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	float animationVelocity = 0.50f;
	// draw the player according to animation state
	if (m_running && !m_pickable)
	{
		TheTextureManager::Instance()->playAnimation("orbing", m_pAnimations["orbing"],
			x, y, animationVelocity, 0, 255, true);
	}
	else if (m_running && m_pickable)
	{
		TheTextureManager::Instance()->playAnimation("BlueGem", m_pAnimations["BlueGem"],
			x, y, animationVelocity, 0, 255, true);
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

	Animation bluegem = Animation();

	bluegem.name = "BlueGem";

	bluegem.frames.push_back(m_pSpriteSheetGem->getFrame("gem1"));
	bluegem.frames.push_back(m_pSpriteSheetGem->getFrame("gem2"));
	bluegem.frames.push_back(m_pSpriteSheetGem->getFrame("gem3"));
	bluegem.frames.push_back(m_pSpriteSheetGem->getFrame("gem4"));
	bluegem.frames.push_back(m_pSpriteSheetGem->getFrame("gem5"));
	bluegem.frames.push_back(m_pSpriteSheetGem->getFrame("gem6"));
	bluegem.frames.push_back(m_pSpriteSheetGem->getFrame("gem7"));
	bluegem.frames.push_back(m_pSpriteSheetGem->getFrame("gem8"));

	m_pAnimations["BlueGem"] = bluegem;

}

void Orb::AnimateDeath()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	float animationVelocity = 0.50f;
	if (TheTextureManager::Instance()->playAnimation("explosionSpider", m_pAnimations["Explosion"],
		x, y, animationVelocity, 0, 255, true))
	{
		m_abilityDone = true;
	}

}
void Orb::pickable(glm::vec2 position)
{
	Game::Instance()->getCurrentScene()->addChild(new Orb(position, true, 0, true));
}