#pragma once
#include <cstdint>
#include "SFML/Graphics.hpp"

class ScoreComponent 
{

public:

	ScoreComponent();

	void initVariables();
	void initFonts();
	void initTexts();
	void update();
	void render(sf::RenderTarget* target);
	static void addScore(const uint32_t scoreToAdd);
	static void resetScore();
	static uint32_t getScore();
	static uint32_t getHighestScore();

private:

	sf::Font m_ScoreFont;
	sf::Text m_ScoreText;
	static uint32_t m_Score;

	sf::Font m_HighestScoreFont;
	sf::Text m_HighestScoreText;
	static uint32_t m_HighestScore;


};