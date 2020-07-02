//#include "PathManager.h"
//#include "MathManager.h"
//
//#include <iostream>
//void PathManager::getShortestPath(PathNode* start, PathNode* goal)
//{
//    s_path.clear(); //Clear old path to save new one
//    s_path.shrink_to_fit();
//    NodeRecord* currentRecord = new NodeRecord(start);
//    currentRecord->m_totalCost = start->getH();
//    s_open.push_back(currentRecord);
//    while (s_open.size() > 0) 
//    {
//        currentRecord = getSmallestNode();
//
//        if (currentRecord->m_node == goal) 
//        {
//            s_open.erase(std::remove(s_open.begin(), s_open.end(), currentRecord), s_open.end());
//            s_closed.push_back(currentRecord);
//            break;
//        }
//        std::vector<PathConnection*> connections = currentRecord->m_node->GetConnections();
//        for (unsigned i = 0; i < connections.size(); i++) 
//        {
//
//            PathNode* endNode = connections[i]->getToNode();
//            NodeRecord* endNodeRecord;
//            double endNodeCost = currentRecord->m_costSoFar + connections[i]->getCost();
//
//            if (containsNode(s_closed, endNode)) 
//            {
//                endNodeRecord = getNodeRecord(s_closed, endNode);
//                if (endNodeRecord->m_costSoFar <= endNodeCost) 
//                    continue;
//                s_closed.erase(std::remove(s_closed.begin(), s_closed.end(), endNodeRecord), s_closed.end());
//                
//            }
//            else if (containsNode(s_open, endNode)) 
//            {
//                endNodeRecord = getNodeRecord(s_open, endNode);
//                if (endNodeRecord->m_costSoFar <= endNodeCost)
//                    continue;
//            }
//            else
//            {
//                endNodeRecord = new NodeRecord();
//                endNodeRecord->m_node = endNode;
//            }
//            endNodeRecord->m_costSoFar = endNodeCost;
//            endNodeRecord->m_connection = connections[i];
//            endNodeRecord->m_fromRecord = currentRecord;
//            endNodeRecord->m_totalCost = endNodeCost + endNode->getH();
//            if (!containsNode(s_open, endNode))
//                s_open.push_back(endNodeRecord);
//
//        }
//        s_open.erase(std::remove(s_open.begin(), s_open.end(), currentRecord), s_open.end());
//        s_closed.push_back(currentRecord);
//    }
//
//    if (currentRecord->m_node != goal) 
//    {
//        std::cout << "No path found" << std::endl;
//    }
//    else 
//    {
//
//        while (currentRecord->m_node != start) 
//        {
//            s_path.push_back(currentRecord->m_connection);
//            currentRecord = currentRecord->m_fromRecord;
//        }
//        std::reverse(s_path.begin(), s_path.end());
//    }
//
//    //Clean up list
//    for (unsigned i = 0; i < s_open.size(); i++) 
//    {
//        delete s_open[i];
//        s_open[i] = nullptr;
//    }
//    s_open.clear();
//    s_open.shrink_to_fit();
//    for (unsigned i = 0; i < s_closed.size(); i++) 
//    {
//        delete s_closed[i];
//        s_closed[i] = nullptr;
//    }
//    s_closed.clear();
//    s_closed.shrink_to_fit();
//}
//
//NodeRecord* PathManager::getSmallestNode()
//{
//    std::vector<NodeRecord*>::iterator smallest = s_open.begin();
//    std::vector<NodeRecord*>::iterator current = s_open.begin();
//
//    while (++current != s_open.end()) 
//    {
//        if ((*current)->m_totalCost < (*smallest)->m_totalCost) 
//        {
//            smallest = current;
//        }
//        else if ((*current)->m_totalCost == (*smallest)->m_totalCost) 
//        {
//            smallest = (rand() % 2 ? current : smallest);
//        }
//    }
//    return(*smallest);
//}
//
//std::vector<NodeRecord*>& PathManager::openList()
//{
//    return s_open;
//}
//
//std::vector<NodeRecord*>& PathManager::closedList()
//{
//    return s_closed;
//}
//
//bool PathManager::containsNode(std::vector<NodeRecord*>& list, PathNode* n)
//{
//    for(unsigned i = 0; i < list.size();i++)
//    {
//        if (list[i]->m_node == n) 
//        {
//            return true;
//        }
//    }
//    return false;
//}
//
//NodeRecord* PathManager::getNodeRecord(std::vector<NodeRecord*>& list, PathNode* n)
//{
//    for (unsigned i = 0; i < list.size(); i++)
//    {
//        if (list[i]->m_node == n)
//        {
//            return list[i];
//        }
//    }
//    return nullptr;
//}
//
//double PathManager::HEuclid(const PathNode* start, const PathNode* goal)
//{
//    return MAMA::Distance(start->x, goal->x, start->y, goal->y);
//}
//
//double PathManager::HManhat(const PathNode* start, const PathNode* goal)
//{
//    return (std::abs(start->x - goal->x) + std::abs(start->y - goal->y));
//}
//
//void PathManager::drawPath()
//{
//
//    for (unsigned i = 0; i < s_path.size(); i++) 
//    {
//        
//    }
//
//}
