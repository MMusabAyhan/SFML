#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(const float x, const float y) : Bullet(x, y)
{
	initVariables();
}

void PlayerBullet::initVariables()
{
	m_Speed = 6.f;
	m_Shape.setFillColor(sf::Color::Green);
}

PlayerBullet::~PlayerBullet()
{

}

void PlayerBullet::update()
{
	const float x = m_Shape.getPosition().x;
	const float y = m_Shape.getPosition().y;

	m_Shape.setPosition(x, y - m_Speed);
}


