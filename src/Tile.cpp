#include "Tile.h"
#include "TextureManager.h"

Tile::Tile(std::string name, int x, int y, const bool o,const bool h)
{
    //m_sPath = spritePath;
    m_sName = name;
    m_iX = x;
    m_iY = y;
    m_bObstacle = o;
    m_bHazard = h;
 
    
    setWidth(32);
    setHeight(32);
    setType(TILE);
    
}

Tile::~Tile()
{
}

void Tile::draw()
{

    TheTextureManager::Instance()->drawTile("tiles", getTransform()->position.x, getTransform()->position.y,m_iX,m_iY, 0, 255, false);
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

void Tile::setXY(int x, int y)
{
    m_iX = x;
    m_iY = y;
}

Tile* Tile::Clone()
{
    return new Tile(m_sName, m_iX, m_iY, m_bObstacle, m_bHazard);
}

void Tile::Print() 
{
    std::cout << "TX: " << m_iX << "TY: " << m_iY << "\n";
}
