#include "Player.h"
#include "Food.h"
#include "math.h"
#include "Game.h"

void Player::initVariables()
{
	m_TotalLength = 1;
	m_Speed = 1.f;
	m_DirectionX = 1;
	m_DirectionY = 0;
}

void Player::initShape()
{
	for (int i = 0; i < 100; i++)
	{
		m_Shape[i].setFillColor(sf::Color(255, 255, 255, 255));
		m_Shape[i].setSize(sf::Vector2f(30, 30));
	}
}

void Player::updateBufferDirection()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_LastDirectionKeyPressed = sf::Keyboard::W;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_LastDirectionKeyPressed = sf::Keyboard::S;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_LastDirectionKeyPressed = sf::Keyboard::A;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_LastDirectionKeyPressed = sf::Keyboard::D;
	}

}

Player::Player(Game& game, float locationX, float locationY)
	: m_Game(game)
{
	m_Shape[0].setPosition(locationX, locationY);

	initVariables();
	initShape();
}

Player::~Player()
{
}

void Player::updateDirection()
{
	if (m_LastDirectionKeyPressed == sf::Keyboard::W && m_DirectionY != 1)
	{
		m_DirectionX = 0;
		m_DirectionY = -1;
	}
	else if (m_LastDirectionKeyPressed == sf::Keyboard::S && m_DirectionY != -1)
	{
		m_DirectionX = 0;
		m_DirectionY = 1;
	}
	else if (m_LastDirectionKeyPressed == sf::Keyboard::A && m_DirectionX != 1)
	{
		m_DirectionX = -1;
		m_DirectionY = 0;
	}
	else if (m_LastDirectionKeyPressed == sf::Keyboard::D && m_DirectionX != -1)
	{
		m_DirectionX = 1;
		m_DirectionY = 0;
	}
}

void Player::updateMovement()
{
	moveTail();
	moveHead();
}

void Player::moveTail()
{
	const float scale = m_Shape[0].getSize().x;

	for (int i = m_TotalLength - 1; i > 0; i--)
	{
		m_Shape[i].setPosition(m_Shape[i - 1].getPosition().x, m_Shape[i - 1].getPosition().y);
	}
}

void Player::moveHead()
{
	const float scale = m_Shape[0].getSize().x;

	m_Shape[0].move(m_DirectionX * m_Speed * scale, m_DirectionY * m_Speed * scale);
}

void Player::checkWindowCollision(const sf::RenderTarget* target)
{
	for (int i = 0; i < m_TotalLength; i++)
	{
		const sf::FloatRect& shapeGlobalBounds = m_Shape[i].getGlobalBounds();
		const float shapeWidth = m_Shape[i].getSize().x;
		const float shapeHeight = m_Shape[i].getSize().y;

		if (shapeGlobalBounds.top < 0)
			m_Shape[i].setPosition(shapeGlobalBounds.left, target->getSize().y - shapeHeight);

		if (shapeGlobalBounds.top > target->getSize().y - shapeHeight)
			m_Shape[i].setPosition(shapeGlobalBounds.left, 0);

		if (shapeGlobalBounds.left < 0)
			m_Shape[i].setPosition(target->getSize().x - shapeWidth, shapeGlobalBounds.top);

		if (shapeGlobalBounds.left > target->getSize().x - shapeWidth)
			m_Shape[i].setPosition(0, shapeGlobalBounds.top);
	}
}

void Player::checkSelfCollision(const sf::RenderTarget* target)
{
	const float headLocationX = m_Shape[0].getPosition().x;
	const float headLocationY = m_Shape[0].getPosition().y;

	for (uint32_t i = 1; i < m_TotalLength; i++)
	{
		const float currentTailLocationX = m_Shape[i].getPosition().x;
		const float currentTailLocationY = m_Shape[i].getPosition().y;

		const float distance = sqrt(
			(currentTailLocationX - headLocationX) * (currentTailLocationX - headLocationX)
			+ (currentTailLocationY - headLocationY) * (currentTailLocationY - headLocationY));


		if (distance < 1)
		{
			onDeath();
			return;
		}
	}

}

void Player::checkFoodCollision(const sf::RenderTarget* target, Food& food)
{
	if (!hasEatenFood(food))
		return;

	m_Game.addScore(m_TotalLength * 5);
	food.pickLocation(target, *this);
	m_TotalLength++;
	moveTail();

}

void Player::updateCollisions(const sf::RenderTarget* target, Food& food)
{
	checkWindowCollision(target);
	checkSelfCollision(target);
	checkFoodCollision(target, food);
}

bool Player::hasEatenFood(const Food& food)
{
	const float foodLocationX = food.m_Shape.getGlobalBounds().left;
	const float foodLocationY = food.m_Shape.getGlobalBounds().top;

	const float locationX = m_Shape[0].getPosition().x;
	const float locationY = m_Shape[0].getPosition().y;

	const float distance = sqrt(
		(foodLocationX - locationX) * (foodLocationX - locationX)
		+ (foodLocationY - locationY) * (foodLocationY - locationY));

	if (distance < 1)
		return true;

	return false;
}

void Player::onDeath()
{
	m_Shape[0].setPosition(0, 0);
	m_DirectionX = 1;
	m_DirectionY = 0;
	m_TotalLength = 1;

	m_Game.resetScore();
}

uint32_t Player::getTotalLength() const
{
	return m_TotalLength;
}

sf::RectangleShape* Player::getShapes()
{
	return m_Shape;
}

void Player::update(const sf::RenderTarget* target, Food& food, const uint32_t& frameNumber)
{
	updateBufferDirection();

	// Framenumber is utilized to get the keypresses more often (10x).
	// This act like a buffer in this case to help with better control over snake.

	if (frameNumber % 10 == 0)
	{
		updateDirection();
		updateMovement();
		updateCollisions(target, food);
	}

}

void Player::render(sf::RenderTarget* target)
{
	if (!target)
		return;

	for (int i = 0; i < m_TotalLength; i++)
	{
		target->draw(m_Shape[i]);
	}
}
