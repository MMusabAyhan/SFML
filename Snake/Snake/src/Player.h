#pragma once
#include <cstdint>
#include "SFML/Graphics.hpp"

class Game;
class Food;

class Player
{
public:

	Player(Game& game, float locationX = 0.f, float locationY = 0.f);
	virtual ~Player();

	void update(const sf::RenderTarget* target, Food& food, const uint32_t& frameNumber);
	void render(sf::RenderTarget* target);
	uint32_t getTotalLength() const;
	sf::RectangleShape* getShapes();

private:

	void initVariables();
	void initShape();
	void updateBufferDirection();
	void updateDirection();
	void updateMovement();
	void moveTail();
	void moveHead();
	void updateCollisions(const sf::RenderTarget* target, Food& food);
	void checkWindowCollision(const sf::RenderTarget* target);
	void checkSelfCollision(const sf::RenderTarget* target);
	void checkFoodCollision(const sf::RenderTarget* target, Food& food);
	bool hasEatenFood(const Food& food);

	void onDeath();

	Game& m_Game;
	sf::RectangleShape m_Shape[100];
	uint32_t m_TotalLength;

	float m_Speed;
	int32_t m_DirectionX;
	int32_t m_DirectionY;

	sf::Keyboard::Key m_LastDirectionKeyPressed;

};