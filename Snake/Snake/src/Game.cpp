#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Food.h"
#include <filesystem>

void Game::initVariables()
{
	m_Window = nullptr;
	m_VideoMode.height = 600;
	m_VideoMode.width = 600;
	m_Score = 0;
	m_HighestScore = 0;

	m_FrameCount = 0;
}

void Game::initWindow()
{
	m_Window = new sf::RenderWindow(m_VideoMode, "Snake Game", sf::Style::Titlebar | sf::Style::Close);
	m_Window->setFramerateLimit(120);
}

void Game::initFood()
{
	if (!m_Window)
		return;

	m_Food.init(m_Window, m_Player);
}

void Game::initFonts()
{
	if (!m_ScoreFont.loadFromFile("./Fonts/Pixellettersfull.ttf"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD MontserratAlternates_Regular.otf" << "\n";
	}

	if (!m_HighestScoreFont.loadFromFile("./Fonts/Pixellettersfull.ttf"))
	{
		std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD MontserratAlternates_Regular.otf" << "\n";
	}

}

void Game::initTexts()
{
	m_ScoreText.setFont(m_ScoreFont);
	m_ScoreText.setFillColor(sf::Color::White);
	m_ScoreText.setCharacterSize(32);
	m_ScoreText.setPosition(20, 5);

	m_HighestScoreText.setFont(m_HighestScoreFont);
	m_HighestScoreText.setFillColor(sf::Color::White);
	m_HighestScoreText.setCharacterSize(32);
	m_HighestScoreText.setPosition(m_Window->getSize().x - 210, 5);
}

Game::Game()
{
	initVariables();
	initWindow();
	initFood();
	initFonts();
	initTexts();
}

Game::~Game()
{
	delete m_Window;
}

const bool Game::isRunning() const
{
	return m_Window->isOpen();
}

void Game::pollEvents()
{
	while (m_Window->pollEvent(m_Ev))
	{
		if (m_Ev.type == sf::Event::Closed)
			m_Window->close();

		if (m_Ev.type == sf::Event::KeyPressed && m_Ev.key.code == sf::Keyboard::Escape)
			m_Window->close();
	}
}

void Game::updatePlayer()
{
	m_Player.update(m_Window, m_Food, m_FrameCount);
}

void Game::updateTexts()
{
	m_ScoreText.setString("Score: " + std::to_string(m_Score));
	m_HighestScoreText.setString("High Score: " + std::to_string(m_HighestScore));
}

void Game::update()
{
	m_FrameCount++;

	pollEvents();

	if (!isRunning())
		return;

	updatePlayer();
	updateTexts();
}

void Game::renderPlayer()
{
	m_Player.render(m_Window);
}

void Game::renderFood()
{
	m_Food.render(m_Window);
}

void Game::renderTexts()
{
	m_Window->draw(m_ScoreText);
	m_Window->draw(m_HighestScoreText);
}

void Game::render()
{
	if (!isRunning())
		return;

	m_Window->clear(sf::Color(0, 0, 0, 255));

	renderPlayer();
	renderFood();
	renderTexts();

	m_Window->display();


}

void Game::addScore(const uint32_t scoreToAdd)
{
	m_Score += scoreToAdd;
	if (m_Score > m_HighestScore)
		m_HighestScore = m_Score;
}

void Game::resetScore()
{
	m_Score = 0;
}