#pragma once
#include <SFML/Graphics.hpp>

class Utils
{
public:
	static float DistanceBetweenPositions(sf::Vector2f first, sf::Vector2f other)
	{
		return sqrt(pow(other.x - first.x, 2) + pow(other.y - first.y, 2));
	}
};

