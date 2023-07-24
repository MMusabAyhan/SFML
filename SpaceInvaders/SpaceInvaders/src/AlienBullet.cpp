#include "AlienBullet.h"

AlienBullet::AlienBullet(const float x, const float y) : Bullet(x,y)
{
	initVariables();
}

void AlienBullet::initVariables()
{
	m_Speed = 1.f;
}
AlienBullet::~AlienBullet()
{
}

void AlienBullet::update()
{
	const float x = m_Shape.getPosition().x;
	const float y = m_Shape.getPosition().y;

	m_Shape.setPosition(x, y + m_Speed);
}


