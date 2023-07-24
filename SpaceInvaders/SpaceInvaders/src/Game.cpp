#include "Game.h"
#include "Player.h"
#include <iostream>

void Game::initVariables()
{
	m_Window = nullptr;
	m_VideoMode.height = 600;
	m_VideoMode.width = 600;
}

void Game::initWindow()
{
	m_Window = new sf::RenderWindow(m_VideoMode, "Space Invaders", sf::Style::Default);
	m_Window->setFramerateLimit(144);

}

void Game::initGameEntities()
{
	m_Invaders.initializeAliens(m_Window);
	m_Player.init(m_Window);
}

void Game::pollEvents()
{
	while(m_Window->pollEvent(m_Ev))
	{
		if(m_Ev.type == sf::Event::Closed)
		{
			m_Window->close();
		}
		if (m_Ev.type == sf::Event::KeyPressed && m_Ev.key.code == sf::Keyboard::Escape)
		{
			m_Window->close();
		}
	}
}

Game::Game()
{
	initVariables();
	initWindow();
	initGameEntities();
}

Game::~Game()
{
	delete m_Window;
}

const bool Game::isRunning() const
{
	return m_Window->isOpen();
}

void Game::update()
{
	pollEvents();

	if (!m_Window->isOpen())
		return;

	m_Invaders.update(m_Window, m_Player);
	m_Player.update(m_Window, m_Invaders);
	m_ScoreComponent.update();

}

void Game::render()
{
	if (!m_Window->isOpen())
		return;

	m_Window->clear(sf::Color::Black);

	m_Invaders.render(m_Window);
	m_Player.render(m_Window);
	m_ScoreComponent.render(m_Window);

	m_Window->display();
}

