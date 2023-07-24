#pragma once
#include "Bullet.h"

class AlienBullet : public Bullet 
{
public:
	AlienBullet(const float x, const float y);
	virtual ~AlienBullet();

	virtual void update() override;

private:

	void initVariables();
	float m_Speed;

};