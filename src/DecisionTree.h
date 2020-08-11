#pragma once
#include <functional>
struct TreeNode {
	TreeNode()
	{
		Condition = nullptr;
		Action = nullptr;
		Left = nullptr;
		Right = nullptr;
	}
	std::function<bool()> Condition;
	std::function<void()> Action;
	TreeNode* Left;
	TreeNode* Right;
};
class DecisionTree {
public:
	DecisionTree()
	{
		m_root = nullptr;
	}
	void setRoot(TreeNode* nn)
	{
		m_root = nn;
	}
	void solveTree()
	{
		TreeNode* temp = nullptr;
		temp = m_root;
		while(temp->Condition != nullptr)
		{
			if (temp->Action != nullptr)
				temp->Action();
			if (temp->Condition())
				temp = temp->Right;
			else
				temp = temp->Left;
		}
		if (temp->Action != nullptr)
			temp->Action();
	}
private:
	TreeNode* m_root;
};