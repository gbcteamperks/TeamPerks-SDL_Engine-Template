#pragma once
#ifndef __TARGET__
#define __TARGET__

#include "DisplayObject.h"

class Target final : public DisplayObject {
public:
	Target();
	~Target();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void m_move();
	void setXY(int, int);


private:
	
	void m_checkBounds();
	void m_reset();
	int m_x = -100, m_y = -1;

};


#endif /* defined (__TARGET__) */