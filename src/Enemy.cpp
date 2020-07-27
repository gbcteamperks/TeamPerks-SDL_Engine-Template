#include "Enemy.h"
#include "Fireball.h"


Enemy::Enemy()
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/bloodsplat2.txt",
		"../Assets/sprites/bloodsplat2.png",
		"bloodsplat2");

	m_pSpriteSheetBlood = TheTextureManager::Instance()->getSpriteSheet("bloodsplat2");
	m_pSpriteSheetBlood->setWidthAndHeight(64, 64);

	buildBloodAnimation();
	
}

Enemy::~Enemy()
= default;


void Enemy::m_buildAnimations()
{
	
}

void Enemy::addAbility(Ability* ability)
{
	m_pListAbilities.push_back(ability);
}

void Enemy::deleteAbility()
{
	m_pListAbilities.erase(m_pListAbilities.begin()); //delete the first ability added.
}

void Enemy::useCurrentAbility()
{
	if (m_pListAbilities.size() > 0 && m_abilityReady) {
		m_pListAbilities.front()->execute(getTransform()->position, 90, true);
	}
}

void Enemy::dropAbility()
{
	if (m_pListAbilities.size() > 0) {
		m_pListAbilities.front()->pickable(getTransform()->position);//adding a pickeable item to DisplayList
	}
}

void Enemy::changeAbility()
{
	static int AbilityCounter = 0;
	AbilityCounter++;
	if (m_pListAbilities.size() > 1) {
		if (AbilityCounter > m_pListAbilities.size() - 1) {
			AbilityCounter = 1;
		}
		std::iter_swap(m_pListAbilities.begin(), m_pListAbilities.begin() + AbilityCounter);
	}
}

void Enemy::buildBloodAnimation()
{
	Animation bloodsplat = Animation();

	bloodsplat.name = "bloodsplat";
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat1"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat2"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat3"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat4"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat5"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat6"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat7"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat8"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat9"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat10"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat11"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat12"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat13"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat14"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat15"));
	//bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat16"));


	m_pAnimations["bloodsplat"] = bloodsplat;
}

void Enemy::animateBloodSplat()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	const float velocityAnimation = 4.0f;
	if (getRigidBody()->isColliding)
	{
		if (TheTextureManager::Instance()->playAnimation("bloodsplat2", m_pAnimations["bloodsplat"],
			x, y, velocityAnimation, 0, 255, true))
		{
			getRigidBody()->isColliding = false;
			m_pAnimations["bloodsplat"].current_frame = 0;
		}
	}
}
