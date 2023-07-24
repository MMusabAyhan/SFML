#pragma once
#include <cstdint>
#include "Alien.h"
#include "AlienBullet.h"
#include <vector>
#include "Player.h"

class Invaders 
{
public:
	Invaders();
	virtual ~Invaders();

	void update(sf::RenderTarget* target, class Player& player);
	void render(sf::RenderTarget* target);
	void initializeAliens(sf::RenderTarget* target);
	Alien* getAliens();
	uint32_t& getAlienNumber();
private:

	void initVariables();
	void initTexture();
	void initSprite();
	const bool anyAlienChangedDirection(sf::RenderTarget* target);
	void moveAliensDown();
	void getBottomAliens(std::vector<Alien*>& outBottomAliens);
	void getAliensXPositions(std::vector<uint32_t>& outAliensXPositions);
	void randomBottomInvaderShoot(std::vector<Alien*> bottomAliens);
	void updateBullets(sf::RenderTarget* target, class Player& player);
	void nextLevel(sf::RenderTarget* target);
	void restartLevel(sf::RenderTarget* target);
	bool hasAllAliensFallen();
	bool hasAnyAlienPassedBottomLimit();
	void initLevel();
	bool hasHitPlayer(const float x, const float y, class Player& player);
	bool checkCollisionWithPlayer(const float x, const float y, const float playerX, const float playerY);

	Alien m_Aliens[200];
	uint32_t m_RowsCount;
	uint32_t m_TotalAlienNumber;
	uint32_t m_Direction;
	float m_Speed;
	sf::Texture m_AliensTexture;
	sf::Sprite m_AliensSprite;

	std::vector<AlienBullet> m_Bullets;
	uint32_t m_BulletCount;
	uint32_t m_TimeSinceLastBullet;
	uint32_t m_MaxTimeToShoot;
	uint32_t level;

};