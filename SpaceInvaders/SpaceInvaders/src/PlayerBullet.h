#pragma once
#include "Bullet.h"
#include "SFML/Graphics.hpp"

class PlayerBullet : public Bullet 
{
public:
	PlayerBullet(const float x, const float y);
	virtual ~PlayerBullet();

	virtual void update() override;

private:

	void initVariables();
	float m_Speed;



};