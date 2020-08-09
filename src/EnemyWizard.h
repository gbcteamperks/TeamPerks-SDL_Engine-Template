#pragma once
#include "Enemy.h"
#include "UIElement.h"
struct Node {
	Node(int x, int y)
	{
		data = new int[2];
		data[0] = x;
		data[1] = y;
		prev = nullptr;
		next = nullptr;
	}
	int* data;
	Node* next;
	Node* prev;
};

struct CircleList {
	CircleList()
	{
		head = nullptr;
		curr = nullptr;
	}
	
	bool isEmpty()
	{
		if (head == nullptr)
			return true;
		return false;
	}
	void add(Node* nn)
	{
		if (isEmpty())
		{
			head = nn;
			curr = head;
			head->prev = curr;
			head->next = curr;
			return;
		}
		Node* temp = head;
		while (temp->next != head)
			temp = temp->next;

		temp->next = nn; //new Node is the last one of the list
		temp->next->prev = temp; //setting new node
		temp->next->next = head;
		head->prev = temp->next; //connecting head with last node
	}
	void Next()
	{
		if (isEmpty())
			return;
		curr = curr->next;
	}
	void Prev()
	{
		if (isEmpty())
			return;
		curr = curr->prev;
	}
	Node* Current()
	{
		return curr;
	}
	Node* head;
	Node* curr;
};
class EnemyWizard : public Enemy {
public:
	EnemyWizard(glm::vec2 position);
	~EnemyWizard();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void bossAttack();

	//animation
	void setNodes();
	void PatrolWtNodes();
	bool SeekingNode(int x, int y);
	void m_buildAnimations() override;

private:

	SpriteSheet* m_pSpriteSheet;

	std::unordered_map<std::string, Animation> m_pAnimations;

	//patrol variables
	bool RightCicle;
	int initialPosPatrol;
	CircleList* m_patrolNodes;


	//UI
	int m_lifeRedCounter;
	std::vector<UIElement*> UI;
};
