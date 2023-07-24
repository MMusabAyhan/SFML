#pragma once
#include "SFML/Graphics.hpp"

class Alien
{
public:
	Alien();
	virtual ~Alien();

	void update(const uint32_t direction, const float speed);
	void render(sf::RenderTarget* target);
	void init(const float x, const float y, sf::Sprite* sprite);
	const bool hasChangedDirection(sf::RenderTarget* target);
	void moveDown();
	void onHit();
	float getPositionX() const;
	float getPositionY() const;
	float getSpriteWidth() const;
	float getSpriteHeight() const;
	bool isAlive() const;

private:

	void initVariables();

	sf::Sprite m_Sprite;
	bool m_Alive;

};