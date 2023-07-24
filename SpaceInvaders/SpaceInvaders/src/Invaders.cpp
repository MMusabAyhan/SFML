#include <iostream>
#include "Invaders.h"
#include <cstdlib>
#include "Alien.h"
#include "Player.h"
#include "ScoreComponent.h"

Invaders::Invaders()
{
	initVariables();
	initLevel();
	initTexture();
	initSprite();
}

void Invaders::initVariables()
{
	m_Speed = 0.1f;
	m_RowsCount = 1;
	m_TotalAlienNumber = 0;
	m_Direction = 1;

	m_Bullets.clear();
	m_Bullets.reserve(30);
	m_BulletCount = 0;
	m_TimeSinceLastBullet = 0;
	m_MaxTimeToShoot = 288;
}

void Invaders::initTexture()
{
	if (!m_AliensTexture.loadFromFile("./Images/Alien.png"))
	{
		std::cout << "Could not load alien texture !" << std::endl;
	}
}

void Invaders::initSprite()
{
	m_AliensSprite.setTexture(m_AliensTexture);
}

void Invaders::initLevel()
{
	level = 1;
}

void Invaders::initializeAliens(sf::RenderTarget* target)
{
	const float width = (float)target->getSize().x;
	const float alienSpriteWidth = m_AliensSprite.getLocalBounds().width;
	float y = 40.f;

	for (uint32_t i = 0; i < m_RowsCount; i++)
	{
		for (float x = 30.f; x < width - alienSpriteWidth; x += alienSpriteWidth)
		{
			m_Aliens[m_TotalAlienNumber].init(x, y, &m_AliensSprite);
			m_TotalAlienNumber++;
		}

		y += 40;
	}
}

const bool Invaders::anyAlienChangedDirection(sf::RenderTarget* target)
{
	for (uint32_t i = 0; i < m_TotalAlienNumber; i++)
	{
		if (m_Aliens[i].hasChangedDirection(target))
		{
			return true;
		}
	}

	return false;
}

void Invaders::moveAliensDown()
{
	for (uint32_t i = 0; i < m_TotalAlienNumber; i++)
	{
		m_Aliens[i].moveDown();
	}
}

void Invaders::getBottomAliens(std::vector<Alien*>& outBottomAliens)
{
	std::vector<uint32_t> aliensXPositions;
	getAliensXPositions(aliensXPositions);

	for (uint32_t i = 0; i < aliensXPositions.size(); i++)
	{
		float anAliensX = aliensXPositions[i];
		// Highest corresponds to the lowest on screen
		float highestYposition = 0;
		Alien* lowestAlien = nullptr;

		for (uint32_t j = 0; j < m_TotalAlienNumber; j++)
		{
			Alien& currentAlien = m_Aliens[j];
			const uint32_t currentAlienX = (uint32_t)currentAlien.getPositionX();

			if (currentAlienX == anAliensX && currentAlien.isAlive())
			{
				if (currentAlien.getPositionY() > highestYposition)
				{
					highestYposition = currentAlien.getPositionY();
					lowestAlien = &currentAlien;
				}
			}
		}

		outBottomAliens.push_back(lowestAlien);
	}
}

void Invaders::getAliensXPositions(std::vector<uint32_t>& outAliensXPositions)
{
	for (uint32_t i = 0; i < m_TotalAlienNumber; i++)
	{
		outAliensXPositions.emplace_back((uint32_t)m_Aliens[i].getPositionX());
	}
}

void Invaders::randomBottomInvaderShoot(std::vector<Alien*> bottomAliens)
{
	const uint32_t numberOfBottomAliens = bottomAliens.size();

	uint32_t randomNumber = rand() % numberOfBottomAliens;
	Alien* shootingAlien = bottomAliens[randomNumber];

	while (!shootingAlien)
	{
		randomNumber = rand() % numberOfBottomAliens;
		shootingAlien = bottomAliens[randomNumber];
	}

	const float shootingAlienWidth = shootingAlien->getSpriteWidth();
	const float shootingAlienHeight = shootingAlien->getSpriteHeight();

	m_Bullets.emplace_back(shootingAlien->getPositionX() + shootingAlienWidth / 2, shootingAlien->getPositionY() + shootingAlienHeight);
	m_BulletCount++;
	m_TimeSinceLastBullet = 0;
}

void Invaders::updateBullets(sf::RenderTarget* target, Player& player)
{
	for (uint32_t i = 0; i < m_BulletCount;)
	{
		m_Bullets[i].update();

		const float x = m_Bullets[i].getPositionX();
		const float y = m_Bullets[i].getPositionY();

		if (hasHitPlayer(x,y,player))
		{
			restartLevel(target);
			return;
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

bool Invaders::hasHitPlayer(const float x, const float y, Player& player)
{
	const float playerX = player.getPositionX();
	const float playerY = player.getPositionY();

	const float playerCenterX = playerX + player.getSpriteWidth() / 2;
	const float playerCenterY = playerY + player.getSpriteHeight() / 2;

	if (checkCollisionWithPlayer(x, y, playerCenterX, playerCenterY))
	{
		return true;
	}

	return false;
}

bool Invaders::checkCollisionWithPlayer(const float x, const float y, const float playerX, const float playerY)
{
	const float checkRadius = 15.f;
	const float distance = sqrt((playerX - x) * (playerX - x) + (playerY - y) * (playerY - y));
	
	if (distance < checkRadius)
	{
		return true;
	}
	return false;
}

Invaders::~Invaders()
{

}

void Invaders::update(sf::RenderTarget* target, Player& player)
{
	if (hasAllAliensFallen())
	{
		nextLevel(target);
	}

	if (hasAnyAlienPassedBottomLimit())
	{
		restartLevel(target);
	}

	for (uint32_t i = 0; i < m_TotalAlienNumber; i++)
	{
		m_Aliens[i].update(m_Direction, m_Speed);
	}

	if (anyAlienChangedDirection(target))
	{
		if (m_Direction == 1)
		{
			m_Direction = -1;
		}
		else
		{
			m_Direction = 1;
		}

		moveAliensDown();
	}

	if (m_TimeSinceLastBullet >= m_MaxTimeToShoot)
	{
		std::vector<Alien*> bottomAliens;
		getBottomAliens(bottomAliens);

		if (bottomAliens.size() <= 0)
			return;

		randomBottomInvaderShoot(bottomAliens);
	}

	m_TimeSinceLastBullet++;

	updateBullets(target, player);
}

void Invaders::render(sf::RenderTarget* target)
{
	for (uint32_t i = 0; i < m_TotalAlienNumber; i++)
	{
		m_Aliens[i].render(target);
	}

	for (uint32_t i = 0; i < m_BulletCount; i++)
	{
		m_Bullets[i].render(target);
	}
}

Alien* Invaders::getAliens()
{
	return m_Aliens;
}

uint32_t& Invaders::getAlienNumber()
{
	return m_TotalAlienNumber;
}

void Invaders::nextLevel(sf::RenderTarget* target)
{
	initVariables();
	m_Speed += 0.1f * level;
	m_MaxTimeToShoot -= 40 * level;
	level++;
	m_RowsCount = level;
	m_RowsCount = std::min((int)m_RowsCount, 3);
	initializeAliens(target);

}

void Invaders::restartLevel(sf::RenderTarget* target)
{
	initVariables();
	initializeAliens(target);

	ScoreComponent::resetScore();
	
}

bool Invaders::hasAllAliensFallen()
{
	for (uint32_t i = 0; i < m_TotalAlienNumber; i++)
	{
		if (m_Aliens[i].isAlive())
		{
			return false;
		}
	}
	return true;
}


bool Invaders::hasAnyAlienPassedBottomLimit()
{
	for (uint32_t i = 0; i < m_TotalAlienNumber; i++)
	{
		const float currentAlienY = m_Aliens[i].getPositionY();

		if (m_Aliens[i].isAlive() && currentAlienY > 400.f)
		{
			return true;
		}
	}
	return false;
}