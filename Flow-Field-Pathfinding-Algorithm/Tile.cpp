#include "Tile.h"

Tile::Tile(int t_cost, sf::Font& t_font) : m_cost{ t_cost }, m_position{ sf::Vector2f{0.0f,0.0f} }, m_goalVector{ sf::Vector2f{0.0f,0.0f} }, m_font{t_font}
{
	initSprite(sf::Vector2f(20.0f, 20.0f), sf::Color::Red);
	initText();
}

Tile::Tile(int t_cost, sf::Vector2f t_goalVector, sf::Vector2f t_position, int t_width, int t_height, sf::Font& t_font, sf::Color t_colour)
	: m_cost{ t_cost }, m_goalVector{t_goalVector},
	m_position{ t_position }, m_font{t_font}
{
	initSprite(sf::Vector2f(t_width, t_height), t_colour);
	initText();
}

void Tile::draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const
{
	t_target.draw(m_shape, t_states);
	//t_target.draw(m_displayCost, t_states);
}

void Tile::initSprite(sf::Vector2f t_dimensions, sf::Color t_colour)
{
	m_shape.setPosition(m_position);
	m_shape.setSize(t_dimensions);
	m_shape.setOrigin(m_shape.getGlobalBounds().width / 2.0f, m_shape.getGlobalBounds().height / 2.0f);
	m_shape.setFillColor(t_colour);
}

void Tile::initText()
{
	m_displayCost.setFont(m_font);
	m_displayCost.setFillColor(sf::Color::Red);
	m_displayCost.setCharacterSize(12);
	m_displayCost.setPosition(m_shape.getPosition());
	m_displayCost.setString(std::to_string(m_cost));
}
