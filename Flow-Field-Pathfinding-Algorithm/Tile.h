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
	int m_id;
	bool m_isTraversable;
	bool m_isGoalNode;
	bool m_isStartNode;
	sf::Color m_defaultColour;
	bool m_isMarked;
public:
	Tile(int t_cost, sf::Font& t_font, bool t_isTraversable);
	Tile(int t_cost, sf::Vector2f t_goalVector, sf::Vector2f t_position, int t_width, int t_height, sf::Font& t_font, sf::Color t_colour, bool t_isTraversable);
	void setId(int t_id)
	{
		m_id = t_id;
		initText();
	}

	int getID() { return m_id; }

	void setIsGoalNode(bool t_isGoalNode) 
	{
		m_isGoalNode = t_isGoalNode;
		if (m_isGoalNode) m_shape.setFillColor(sf::Color::Red);
		else if(!m_isStartNode) m_shape.setFillColor(m_defaultColour);
	}
	void setIsStartNode(bool t_isStartNode) 
	{
		m_isStartNode = t_isStartNode;
		if (m_isStartNode) m_shape.setFillColor(sf::Color::Green);
		else if(!m_isGoalNode) m_shape.setFillColor(m_defaultColour);
	}
	bool isGoalNode() { return m_isGoalNode; }
	bool isStartNode() { return m_isStartNode; }

	bool intersectsPoint(sf::Vector2f t_point);

	void setCost(int t_cost) { m_cost = t_cost; }
	int getCost() { return m_cost; }

	void setMarked(bool t_marked) { m_isMarked = t_marked; }
	bool getMarked() { return m_isMarked; }

	bool isTraversable() { return m_isTraversable; }
private:
	virtual void draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const;
	void initSprite(sf::Vector2f t_dimensions, sf::Color t_colour);
	void initText();
};

