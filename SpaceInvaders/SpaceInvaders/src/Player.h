#pragma once
#include "SFML/Graphics.hpp"
#include "PlayerBullet.h"
#include "Invaders.h"

class Player 
{
public:
	Player();
	virtual ~Player();

	void update(sf::RenderTarget* target, class Invaders& invaders);
	void render(sf::RenderTarget* target);
	void init(sf::RenderTarget* target);
	float getPositionX() const;
	float getPositionY() const;
	float getSpriteWidth() const;
	float getSpriteHeight() const;

private:

	void initVariables();
	void initTexture();
	void initSprite();
	void updateInput();
	void updateDirection();
	bool shouldShoot();
	void updateCanShoot();
	void shoot();
	void updateMovement();
	void constrain(sf::RenderTarget* target);
	void updateBullets(sf::RenderTarget* target, class Invaders& invaders);
	const bool hasHitAnyAlien(const Bullet& bullet, Alien* aliens, uint32_t& alienNumber);
	bool checkAlienCollision(const float x, const float y, Alien* aliens, uint32_t& alienNumber);

	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	uint32_t m_Direction;
	float m_Speed;

	std::vector<PlayerBullet> m_Bullets;
	uint32_t m_BulletCount;
	uint32_t m_TimeSinceLastBullet;
	uint32_t m_MaxTimeToShoot;
	bool m_CanShoot;
};