#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "Player.h"
#include "Food.h"

class Game 
{
public:

	Game();
	virtual ~Game();

	const bool isRunning() const;
	void pollEvents();
	void update();
	void render();
	void addScore(const uint32_t scoreToAdd);
	void resetScore();

private:

	void initVariables();
	void initWindow();
	void initFood();
	void initFonts();
	void initTexts();

	void updatePlayer();
	void updateTexts();
	void renderPlayer();
	void renderFood();
	void renderTexts();

	sf::RenderWindow* m_Window;
	sf::VideoMode m_VideoMode;
	sf::Event m_Ev;
	Player m_Player{ *this };
	Food m_Food{ *this };

	sf::Font m_ScoreFont;
	sf::Text m_ScoreText;
	uint32_t m_Score;

	sf::Font m_HighestScoreFont;
	sf::Text m_HighestScoreText;
	uint32_t m_HighestScore;

	uint32_t m_FrameCount;

};