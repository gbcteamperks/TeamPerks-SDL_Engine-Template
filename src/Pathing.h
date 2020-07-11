#pragma once
#ifndef _PATHING_H_
#define _PATHING_H_
#include <SDL.h>
#include <vector>
class PathConnection;

class PathNode :public SDL_Point 
{
private:
	double m_h;
	/*std::vector<PathConnection*>m_connections;*/

public:
	PathNode(int x, int y);
	~PathNode();
	void update();
	/*void addConnection(PathConnection* c);
	std::vector<PathConnection*>& GetConnections();*/
	SDL_Point getPt() { return { x,y }; }
	double getH() { return m_h; }
	void setH(double h) { m_h = h; }
};


//class PathConnection 
//{
//private:
//	double m_cost;
//	PathNode* m_pFromNode, * m_pToNode;
//public:
//	PathConnection(PathNode* f, PathNode* t, double cost = 1.0);
//	~PathConnection();
//	double getCost() { return m_cost; }
//	void setCost(double cost) { m_cost = cost; }
//	PathNode* getFromNode() { return m_pFromNode; }
//	PathNode* getToNode() { return m_pToNode; }
//};
//
//struct NodeRecord 
//{
//	NodeRecord(PathNode* n = nullptr) :m_node(n), m_connection(nullptr), m_fromRecord(nullptr), m_costSoFar(0.0), m_totalCost(0.0) {}
//	PathNode* m_node;
//	PathConnection* m_connection;
//	NodeRecord* m_fromRecord;
//	double m_costSoFar;
//	double m_totalCost;
//};

#endif // !_PATHING_H_
