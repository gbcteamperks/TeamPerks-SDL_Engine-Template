#include "Ability.h"

Ability::Ability()
{
	setParentType(ABILITY);

	//gem for pickeable
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/gem.txt",
		"../Assets/sprites/Items_BlueGem.png",
		"BlueGem");

	m_pSpriteSheetGem = TheTextureManager::Instance()->getSpriteSheet("BlueGem");
	m_pSpriteSheetGem->setWidthAndHeight(32, 32);

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

Ability::~Ability()
{
}


void Ability::stop()
{
}

void Ability::sound()
{
}

void Ability::animation()
{
}

