#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "Game.h"

int main(int argc, char* argv[]) 
{
	Game game;

	while (game.isRunning()) 
	{

		game.update();
		game.render();
	}

	return 0;
}