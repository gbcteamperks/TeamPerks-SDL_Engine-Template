//#include "Pathing.h"
//#include "EventManager.h"
//PathNode::PathNode(int x, int y)
//{
//	this->x = x;
//	this->y = y;
//}
//
//PathNode::~PathNode()
//{
//	for (unsigned i = 0; i < m_connections.size(); i++) 
//	{
//		delete m_connections[i];
//		m_connections[i] = nullptr;
//	}
//	m_connections.clear();
//	m_connections.shrink_to_fit();
//}
//
//void PathNode::update() 
//{
//
//}
//
//void PathNode::addConnection(PathConnection* c) 
//{
//	m_connections.push_back(c);
//}
//
//std::vector<PathConnection*>& PathNode::GetConnections() 
//{
//	return m_connections;
//}
//
//PathConnection::PathConnection(PathNode* f, PathNode* t, double cost) :m_cost(cost), m_pFromNode(f), m_pToNode(t) {}
//
