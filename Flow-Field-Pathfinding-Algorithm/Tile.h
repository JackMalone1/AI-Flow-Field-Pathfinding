#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Tile : public sf::Drawable
{
private:
	sf::Vector2f m_goalVector;
	sf::Vector2f m_position;
	int m_cost;
	sf::Text m_displayCost;
	sf::Font& m_font;
	sf::RectangleShape m_shape;
public:
	Tile(int t_cost, sf::Font& t_font);
	Tile(int t_cost, sf::Vector2f t_goalVector, sf::Vector2f t_position, int t_width, int t_height, sf::Font& t_font, sf::Color t_colour);
private:
	virtual void draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const;
	void initSprite(sf::Vector2f t_dimensions, sf::Color t_colour);
	void initText();
};

