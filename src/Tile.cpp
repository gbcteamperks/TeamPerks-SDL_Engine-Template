#include "Tile.h"
#include "TextureManager.h"

Tile::Tile(std::string name, float posX, float posY, const bool o,const bool h)
{
    //m_sPath = spritePath;
    m_sName = name;
    m_bObstacle = o;
    m_bHazard = h;
    m_fX = posX;
    m_fY = posY;
    
    setWidth(64);
    setHeight(64);
    setType(TILE);
    
}

Tile::~Tile()
{
}

void Tile::draw()
{
    const auto x = getTransform()->position.x;
    const auto y = getTransform()->position.y;

    TheTextureManager::Instance()->drawTile(m_sName, x, y,m_fX,m_fY, 0, 255, true);
}

void Tile::update()
{
}

void Tile::clean()
{
}

bool& Tile::isObstacle()
{
    return m_bObstacle;
}

bool Tile::isHazard()
{
    return m_bHazard;
}

Tile* Tile::Clone()
{
    return new Tile(m_sName, m_fX, m_fY, m_bObstacle, m_bHazard);
}


