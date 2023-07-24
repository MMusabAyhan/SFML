#include <iostream>
#include "ScoreComponent.h"

uint32_t ScoreComponent::m_Score;
uint32_t ScoreComponent::m_HighestScore;

ScoreComponent::ScoreComponent() 
{
	initVariables();
	initFonts();
	initTexts();
}

void ScoreComponent::initVariables()
{
	m_Score = 0;
	m_HighestScore = 0;
}
void ScoreComponent::initFonts() 
{
	if (!m_ScoreFont.loadFromFile("./Fonts/Pixellettersfull.ttf"))
	{
		std::cout << "Could not load Score's Font!" << "\n";
	}

	if (!m_HighestScoreFont.loadFromFile("./Fonts/Pixellettersfull.ttf"))
	{
		std::cout << "Could not load High Score's Font!" << "\n";
	}
}
void ScoreComponent::initTexts() 
{
	m_ScoreText.setFont(m_ScoreFont);
	m_ScoreText.setCharacterSize(24);
	m_ScoreText.setFillColor(sf::Color::White);
	m_ScoreText.setPosition(20,5);


	m_HighestScoreText.setFont(m_HighestScoreFont);
	m_HighestScoreText.setCharacterSize(24);
	m_HighestScoreText.setFillColor(sf::Color::White);
	m_HighestScoreText.setPosition(400, 5);
}

void ScoreComponent::update()
{
	m_ScoreText.setString("Score: " + std::to_string(m_Score));
	m_HighestScoreText.setString("High Score: " + std::to_string(m_HighestScore));
}

void ScoreComponent::render(sf::RenderTarget* target)
{
	target->draw(m_ScoreText);
	target->draw(m_HighestScoreText);
}

void ScoreComponent::addScore(const uint32_t scoreToAdd)
{
	m_Score += scoreToAdd;

	if (m_HighestScore < m_Score)
		m_HighestScore = m_Score;
	
}

void ScoreComponent::resetScore()
{
	m_Score = 0;
}

uint32_t ScoreComponent::getScore()
{
	return m_Score;
}

uint32_t ScoreComponent::getHighestScore()
{
	return m_HighestScore;
}