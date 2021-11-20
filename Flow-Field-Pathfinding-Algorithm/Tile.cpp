#include "Tile.h"

Tile::Tile(int t_cost, sf::Vector2f t_goalVector, sf::Vector2f t_position,
	int t_width, int t_height, sf::Font& t_font, sf::Color t_colour, int t_row, int t_col)
	: m_cost{ t_cost }, m_goalVector{t_goalVector},
	m_position{ t_position }, m_font{t_font},
	m_isTraversable{true}, m_isMarked{true}, m_isStartNode{ false }, m_isGoalNode{ false },
	m_row{t_row}, m_col{t_col}, m_shouldDisplayIntegrationCost{false}
{
	initSprite(sf::Vector2f(t_width, t_height), t_colour);
	initText();
}

bool Tile::intersectsPoint(sf::Vector2f t_point)
{
	return m_shape.getGlobalBounds().contains(t_point);;
}

void Tile::draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const
{
	t_target.draw(m_shape, t_states);
	if(m_shouldDisplayCost) t_target.draw(m_displayCost, t_states);
	if (m_shouldDisplayIntegrationCost) t_target.draw(m_displayIntegrationCost, t_states);
	if (m_vectorToGoal.getVertexCount() > 0 && m_shouldDisplayVectorField) t_target.draw(m_vectorToGoal, t_states);
}

void Tile::initSprite(sf::Vector2f t_dimensions, sf::Color t_colour)
{
	m_defaultColour = t_colour;
	m_shape.setPosition(m_position);
	m_shape.setSize(t_dimensions);
	m_shape.setOrigin(m_shape.getGlobalBounds().width / 2.0f, m_shape.getGlobalBounds().height / 2.0f);
	m_shape.setFillColor(m_defaultColour);
	m_shape.setOutlineColor(sf::Color::Green);
	m_shape.setOutlineThickness(1.0f);
}

void Tile::initText()
{
	m_displayCost.setFont(m_font);
	m_displayCost.setFillColor(sf::Color::Black);
	m_displayCost.setCharacterSize(8);
	m_displayCost.setPosition(m_shape.getPosition() - sf::Vector2f(7.5f, 7.5f));
	if (m_cost < 9000) m_displayCost.setString(std::to_string(m_cost));
	else m_displayCost.setString("Max");

	m_displayIntegrationCost.setFont(m_font);
	m_displayIntegrationCost.setFillColor(sf::Color::Black);
	m_displayIntegrationCost.setCharacterSize(8);
	m_displayIntegrationCost.setPosition(m_shape.getPosition() - sf::Vector2f(7.5f, 7.5f));
	//m_displayIntegrationCost.setString(std::to_string(m_integrationFieldCost));
}
