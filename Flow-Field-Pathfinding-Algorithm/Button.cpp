#include "Button.h"

bool Button::onButtonPress(sf::Vector2i t_mousePosition)
{
	return m_body.getGlobalBounds().contains(static_cast<sf::Vector2f>(t_mousePosition));
}

Button::Button(sf::Vector2f t_position, std::string t_text, float t_width, float t_height, std::string t_button) : m_button{t_button}
{
	m_body.setSize(sf::Vector2f(t_width, t_height));
	m_body.setPosition(t_position);
	m_body.setFillColor(sf::Color::Magenta);	
	if (!font.loadFromFile("ASSETS//FONTS//ariblk.ttf")) std::cout << "Error loading font" << std::endl;
	m_text.setFont(font);
	m_text.setPosition(t_position + sf::Vector2f(10.0f, 15.0f));
	m_text.setCharacterSize(18);
	m_text.setFillColor(sf::Color::Black);
	m_text.setString(t_text);
}

void Button::draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const
{
	t_target.draw(m_body, t_states);
	t_target.draw(m_text, t_states);
}
