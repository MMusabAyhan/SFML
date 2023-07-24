#include "Food.h"
#include "Player.h"

void Food::initVariables() 
{
}

void Food::initShape() 
{
	m_Shape.setFillColor(sf::Color(255, 0, 0, 100));
	m_Shape.setSize(sf::Vector2f(30.f,30.f));
}

Food::Food(Game& game)
	: m_Game(game)
{
	initVariables();
	initShape();
}

Food::~Food()
{

}

void Food::init(const sf::RenderTarget* target, Player& player)
{
	if (!target)
		return;
	pickLocation(target,player);
}

bool Food::isCollidingWithPlayer(const float& locationX, const float& locationY, Player& player) const
{
	for (uint32_t i = 0; i < player.getTotalLength(); i++)
	{
		const float playerShapeLocationX = player.getShapes()[i].getPosition().x;
		const float playerShapeLocationY = player.getShapes()[i].getPosition().y;

		if (playerShapeLocationX == locationX && playerShapeLocationY == locationY)
		{
			return true;
		}
	}
	return false;
}

void Food::pickLocation(const sf::RenderTarget* target, Player& player)
{
	const float scale = m_Shape.getSize().x;
	const uint32_t windowWidth = target->getSize().x;
	const uint32_t windowHeight = target->getSize().y;

	int32_t cols = (int32_t) floor(windowWidth / scale);
	int32_t rows = (int32_t) floor(windowHeight / scale);

	float locationX{};
	float locationY{};

	do 
	{
		locationX = (float) floor(rand() % cols) * scale;
		locationY = (float) floor(rand() % rows) * scale;
	}
	while (isCollidingWithPlayer(locationX, locationY, player));

	m_Shape.setPosition(locationX, locationY);
}

void Food::update() 
{
}

void Food::render(sf::RenderTarget* target) 
{
	target->draw(m_Shape);
}