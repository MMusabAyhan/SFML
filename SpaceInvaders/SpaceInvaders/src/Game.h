#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Invaders.h"
#include "ScoreComponent.h"

class Game 
{
public:
	Game();
	virtual ~Game();

	const bool isRunning() const;
	void update();
	void render();

private:

	void initVariables();
	void initWindow();
	void initGameEntities();

	void pollEvents();

	sf::RenderWindow* m_Window;
	sf::VideoMode m_VideoMode;
	sf::Event m_Ev;

	Invaders m_Invaders;
	Player m_Player;
	ScoreComponent m_ScoreComponent;
};