#pragma once

#include <SFML/Graphics.hpp>


class Tile
{
private:
	sf::Vector2f m_goalVector;
	sf::Vector2f m_position;
	int m_cost;

	sf::RectangleShape m_shape;
public:
	Tile(int t_cost);
};

