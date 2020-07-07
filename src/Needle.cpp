#include "Needle.h"
#include "TextureManager.h"

Needle::Needle()
{
	TextureManager::Instance()->load("../Assets/textures/LifeBarNeedle.png", "Needle");
}

Needle::~Needle()
= default;

void Needle::draw()
{
	TextureManager::Instance()->draw("Needle", x, y, angle, 255, false, SDL_FLIP_NONE, 15, 33);
}

void Needle::update(GameObject* player)
{
	if (player->getLife() > 75) {
		x = (((100 - player->getLife()) * 0.3) + 85);
		y = (((player->getLife() - 100) * 0.01) + 512);
		angle = (((100 - player->getLife())*2.8) - 60);
	}
	else if(player->getLife() > 50) {
		x = (((100 - player->getLife())*0.3 ) + 85);
		y = (((player->getLife() - 100) * 0.01) + 512);
		angle = (((100 - player->getLife()) * 2.7) - 60);
	}
	else if (player->getLife() > 0) {
		x = (((player->getLife()-50) * 0.2) + 100);
		y = (((50-player->getLife()) * 0.25) + 511);
		angle = (((100 - player->getLife()) * 2.5) - 60);
	}
}

void Needle::clean()
{
}
