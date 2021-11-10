#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 1000U, 1000U, 32U }, "SFML Game" },
	m_exitGame{ false }
{
	int y = -10;
	int x = -10;
	if (!m_font.loadFromFile("ASSETS//FONTS//aribl.ttf")) std::cout << "Error loading font" << std::endl;
	sf::Color colour = sf::Color::Red;
	for (auto& row : m_tiles)
	{
		x += 20;
		y = -10;
		for (auto& tile : row)
		{
			y += 20;
			colour = colour == sf::Color::Red ? sf::Color::Blue : sf::Color::Red;
			tile = new Tile(0, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(x, y), 20.0f, 20.0f, m_font, colour);
		}
	}
}


Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps);
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); 
			update(timePerFrame); 
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) 
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) 
		{
			processKeys(newEvent);
		}
	}
}



void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}


void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}


void Game::render()
{
	m_window.clear(sf::Color::White);
	for (auto& row : m_tiles)
	{
		for (auto& tile : row)
		{
			m_window.draw(*tile);
		}
	}
	m_window.display();
}

