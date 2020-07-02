//#pragma once
//#ifndef _PATHMANAGER_H_
//#define _PATHMANAGER_H_
//#include "Pathing.h"
//#include <vector>
//class PathManager 
//{
//
//private:
//	static std::vector<NodeRecord*> s_open;
//	static std::vector<NodeRecord*> s_closed;
//	static std::vector<PathConnection*> s_path;
//
//	PathManager();
//
//public:
//	static void getShortestPath(PathNode* start, PathNode* goal);
//	static NodeRecord* getSmallestNode();
//	static std::vector<NodeRecord*>& openList();
//	static std::vector<NodeRecord*>& closedList();
//	static bool containsNode(std::vector<NodeRecord*>& list, PathNode* n);
//	static NodeRecord* getNodeRecord(std::vector<NodeRecord*>& list, PathNode* n);
//	static double HEuclid(const PathNode* start, const PathNode* goal);
//	static double HManhat(const PathNode* start, const PathNode* goal);
//	static void drawPath();
//};
//
//typedef PathManager PAMA;
//
//#endif // !_PATHMANAGER_H_
