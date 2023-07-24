#include "Bullet.h"

Bullet::Bullet(const float x, const float y)
{
	initVariables();
	m_Shape.setPosition(x, y);
}

void Bullet::initVariables()
{
	m_Shape.setSize(sf::Vector2f(3.f,10.f));
	m_Shape.setFillColor(sf::Color::Red);
}

Bullet::~Bullet()
{
}

void Bullet::update()
{

}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(m_Shape);
}

void Bullet::setPosition(const float x, const float y)
{
	m_Shape.setPosition(x, y);
}

const bool Bullet::isOffScreen(sf::RenderTarget* target)
{
	const float windowHeight = target->getSize().y;
	const float y = m_Shape.getPosition().y;

	if (y > windowHeight)
	{
		return true;
	}

	return false;
}

float Bullet::getPositionX() const
{
	return m_Shape.getPosition().x;
}
float Bullet::getPositionY() const
{
	return m_Shape.getPosition().y;
}