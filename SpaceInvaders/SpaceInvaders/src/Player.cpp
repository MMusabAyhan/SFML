#pragma once
#include <iostream>
#include "Player.h"
#include "Invaders.h"
#include "ScoreComponent.h"

Player::Player()
{
	initVariables();
	initTexture();
	initSprite();
}

Player::~Player()
{
}

void Player::initVariables()
{
	m_Direction = 0;
	m_Speed = 1.5f;
	m_TimeSinceLastBullet = 0;
	m_MaxTimeToShoot = 48.f;
	m_CanShoot = true;
}

void Player::initTexture()
{
	if (!m_Texture.loadFromFile("./Images/Ship.png"))
	{
		std::cout << "Could not load Ship Sprite ! " << std::endl;
	}
}

void Player::initSprite()
{
	m_Sprite.setTexture(m_Texture);
}

void Player::init(sf::RenderTarget* target)
{
	const float shipWidth = m_Sprite.getLocalBounds().width;
	const float shipHeight = m_Sprite.getLocalBounds().height;
	const float windowWidth = target->getSize().x;
	const float windowHeight = target->getSize().y;

	m_Sprite.setPosition((windowWidth / 2 - shipWidth / 2), windowHeight - shipHeight);
}

void Player::update(sf::RenderTarget* target, Invaders& invaders)
{
	updateInput();
	updateMovement();
	constrain(target);
	updateBullets(target, invaders);
	m_TimeSinceLastBullet++;
}

void Player::updateInput()
{
	if (shouldShoot())
	{
		shoot();
	}

	updateCanShoot();

	updateDirection();
}

void Player::updateDirection()
{
	bool directionKeyPressed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_Direction = -1;
		directionKeyPressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_Direction = 1;
		directionKeyPressed = true;
	}

	if (!directionKeyPressed)
	{
		m_Direction = 0;
	}

}

bool Player::shouldShoot()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_CanShoot)
	{
		return true;
	}

	return false;
}

void Player::updateCanShoot()
{
	if (m_TimeSinceLastBullet < m_MaxTimeToShoot)
		return;
	
	m_CanShoot = true;
}

void Player::shoot()
{
	const float shipWidth = m_Sprite.getLocalBounds().width;
	const float shipHeight = m_Sprite.getLocalBounds().height;

	const float shipX = m_Sprite.getPosition().x;
	const float shipY = m_Sprite.getPosition().y;

	m_Bullets.emplace_back(shipX + shipWidth/2 , shipY);

	m_CanShoot = false;
	m_TimeSinceLastBullet = 0;
	m_BulletCount++;
}

void Player::updateMovement()
{
	if (m_Direction == 0)
		return;

	const float x = m_Sprite.getPosition().x;
	const float y = m_Sprite.getPosition().y;

	if (m_Direction == 1)
	{
		m_Sprite.setPosition(x + m_Speed, y);
	}
	else if (m_Direction == -1)
	{
		m_Sprite.setPosition(x - m_Speed, y);
	}
}

void Player::constrain(sf::RenderTarget* target)
{
	const float windowWidth = target->getSize().x;
	const float windowHeight = target->getSize().y;
	const float shipWidth = m_Sprite.getLocalBounds().width;

	const float x = m_Sprite.getPosition().x;
	const float y = m_Sprite.getPosition().y;

	if (x<=0)
	{
		m_Sprite.setPosition(0, y);
	}
	if (x >= windowWidth - shipWidth)
	{
		m_Sprite.setPosition(windowWidth - shipWidth, y);
	}

}

void Player::render(sf::RenderTarget* target)
{
	target->draw(m_Sprite);

	for (uint32_t i = 0; i < m_BulletCount; i++)
	{
		m_Bullets[i].render(target);
	}
}

void Player::updateBullets(sf::RenderTarget* target, Invaders& invaders)
{
	Alien* aliens = invaders.getAliens();
	uint32_t& alienNumber = invaders.getAlienNumber();

	for (uint32_t i = 0; i < m_BulletCount;)
	{
		m_Bullets[i].update();

		if (hasHitAnyAlien(m_Bullets[i],aliens,alienNumber))
		{
			m_Bullets.erase(m_Bullets.begin() + i);
			m_BulletCount--;

			ScoreComponent::addScore(50);

			continue;
		}
		
		if (m_Bullets[i].isOffScreen(target))
		{
			m_Bullets.erase(m_Bullets.begin() + i);
			m_BulletCount--;
			continue;
		}

		i++;
	}
}

const bool Player::hasHitAnyAlien(const Bullet& bullet, Alien* aliens, uint32_t& alienNumber)
{
	const float x = bullet.getPositionX();
	const float y = bullet.getPositionY();

	return checkAlienCollision(x, y,aliens,alienNumber);
}

bool Player::checkAlienCollision(const float x, const float y, Alien* aliens, uint32_t& alienNumber)
{
	for (uint32_t i = 0; i < alienNumber; i++)
	{
		if (!aliens[i].isAlive())
			continue;

		Alien& currentAlien = aliens[i];

		const float currentAlienX = currentAlien.getPositionX();
		const float currentAlienY = currentAlien.getPositionY();

		const float currentAlienWidth = currentAlien.getSpriteWidth();
		const float currentAlienHeight = currentAlien.getSpriteHeight();

		const float currentAlienCenterX = currentAlienX + currentAlienWidth / 2;
		const float currentAlienCenterY = currentAlienY + currentAlienHeight / 2;

		const float checkRadius = currentAlienWidth / 2;

		const float distance = sqrt((currentAlienCenterX - x) * (currentAlienCenterX - x) + (currentAlienCenterY - y) * (currentAlienCenterY - y));

		if (distance < checkRadius && currentAlien.isAlive())
		{
			currentAlien.onHit();
			return true;
		}
	}
	return false;
}

float Player::getPositionX() const
{
	return m_Sprite.getPosition().x;
}

float Player::getPositionY() const 
{
	return m_Sprite.getPosition().y;
}

float Player::getSpriteWidth() const
{
	return m_Sprite.getLocalBounds().width;
}
float Player::getSpriteHeight() const
{
	return m_Sprite.getLocalBounds().height;
}