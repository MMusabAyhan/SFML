#pragma once
#include "SFML/Graphics.hpp"

class Player;
class Game;

class Food 
{
public:

	Food(Game& game);
	void init(const sf::RenderTarget* target, Player& player);
	virtual ~Food();

	void pickLocation(const sf::RenderTarget* target, Player& player);
	void update();
	void render(sf::RenderTarget* target);

	sf::RectangleShape m_Shape;
private:

	void initVariables();
	void initShape();
	bool isCollidingWithPlayer(const float& locationX, const float& locationY, Player& player) const;

	Game& m_Game;
};