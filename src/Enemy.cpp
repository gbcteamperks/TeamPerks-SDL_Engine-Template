#include "Enemy.h"
#include "Fireball.h"


Enemy::Enemy()
{
	
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
		m_pListAbilities.front()->execute(getTransform()->position, 90);
	}
}

void Enemy::dropAbility()
{
	if (m_pListAbilities.size() > 0) {
		m_pListAbilities.front()->pickable(getTransform()->position);//adding a pickeable item to DisplayList
	}
}
