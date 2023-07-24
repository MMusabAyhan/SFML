#include "Alien.h"
Alien::Alien()
{
	initVariables();
}

void Alien::initVariables()
{
	m_Alive = false;
}

Alien::~Alien()
{
}

void Alien::update(const uint32_t direction, const float speed)
{
	const float y = m_Sprite.getPosition().y;

	if (direction == 1)
	{
		const float newX = m_Sprite.getPosition().x + speed;
		m_Sprite.setPosition(newX, y);
	}
	
	else if (direction == -1) 
	{
		const float newX = m_Sprite.getPosition().x - speed;
		m_Sprite.setPosition(newX, y);
	}
}

void Alien::render(sf::RenderTarget* target)
{
	if (!m_Alive)
		return;

	target->draw(m_Sprite);
}

void Alien::init(const float x, const float y, sf::Sprite* sprite)
{
	m_Sprite = *sprite;
	m_Sprite.setPosition(x, y);
	m_Alive = true;
}

const bool Alien::hasChangedDirection(sf::RenderTarget* target)
{
	const float x = m_Sprite.getPosition().x;
	const float alienWidth = m_Sprite.getLocalBounds().width;
	const float windowWidth = (float) target->getSize().x;

	if (x >= windowWidth - alienWidth)
	{
		return true;
	}
	else if (x <= 0) 
	{
		return true;
	}

	return false;
}

void Alien::moveDown()
{
	const float x = m_Sprite.getPosition().x;
	const float y = m_Sprite.getPosition().y;
	m_Sprite.setPosition(x, y + 10);
}

void Alien::onHit()
{
	m_Alive = false;
}

float Alien::getPositionX() const
{
	return m_Sprite.getPosition().x;
}

float Alien::getPositionY() const
{
	return m_Sprite.getPosition().y;
}

float Alien::getSpriteWidth() const
{
	return m_Sprite.getLocalBounds().width;
}

float Alien::getSpriteHeight() const
{
	return m_Sprite.getLocalBounds().height;
}

bool Alien::isAlive() const
{
	return m_Alive;
}