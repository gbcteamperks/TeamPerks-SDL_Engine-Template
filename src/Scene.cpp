#include "Scene.h"
#include "DisplayObject.h"

Scene::Scene()
= default;

Scene::~Scene()
{
	removeAllChildren();
}


void Scene::addChild(DisplayObject * child)
{
	m_displayList.push_back(child);
}

void Scene::removeAllChildren()
{
	for (int count = 0; count < m_displayList.size(); ++count)
	{
		m_displayList[count] = nullptr;
	}

	m_displayList.clear();
	m_displayList.resize(0);
	m_displayList.shrink_to_fit();
}


int Scene::numberOfChildren() const
{
	return m_displayList.size();
}

void Scene::removeChildByType(GameObjectType type)
{
	for (auto it = m_displayList.begin(); it != m_displayList.end();) {
		if ((*it)->getType() == type) {

			(*it)->clean();
			delete (*it);
			it = m_displayList.erase(it);

		}
		else {
			it++;

		}
	}
}

void Scene::updateDisplayList()
{
	for (auto count = 0; count < m_displayList.size(); ++count)
	{
		if (m_displayList[count] != nullptr)
		{
			m_displayList[count]->update();
		}
	}	
}

void Scene::drawDisplayList()
{
	for (auto count = 0; count < m_displayList.size(); ++count)
	{
		if (m_displayList[count] != nullptr)
		{
			if (m_displayList[count]->getType() != TILE) {
				m_displayList[count]->draw();
			}
		}
	}

}

std::vector<DisplayObject*> & Scene::getDisplayList()
{
	return m_displayList;
}

std::vector<DisplayObject*> Scene::getEnemies()
{
	std::vector<DisplayObject*> listEnemies;
	for (auto o : m_displayList)
	{
		if (o->getType() == ENEMY) 
		{
			listEnemies.push_back(o);
		}
	}
	return listEnemies;
}
