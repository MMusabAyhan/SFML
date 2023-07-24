#pragma once
#include "SFML/Graphics.hpp"

class Bullet
{
public:

	Bullet(const float x, const float y);
	virtual ~Bullet();

	virtual void update();
	void render(sf::RenderTarget* target);
	void setPosition(const float x, const float y);
	const bool isOffScreen(sf::RenderTarget* target);
	float getPositionX() const;
	float getPositionY() const;

protected:
	sf::RectangleShape m_Shape;

private:
	
	void initVariables();

};