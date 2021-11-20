#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
class Button : public sf::Drawable
{
public:
	bool onButtonPress(sf::Vector2i t_mousePosition);
	std::string buttonType() { return m_button; }
	Button(sf::Vector2f t_position, std::string t_text, float t_width, float t_height, std::string t_button);
private:
	sf::RectangleShape m_body;
	sf::Text m_text;
	std::string m_string;
	std::string m_button;
	sf::Font font;
private:
	virtual void draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const;
};


