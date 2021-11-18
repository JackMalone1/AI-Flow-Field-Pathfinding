#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 1000U, 1000U, 32U }, "SFML Game", sf::Style::Titlebar | sf::Style::Close},
	m_exitGame{ false }
{
	srand(time(NULL));
	int y = -10;
	int x = -10;
	int id = 0;
	if (!m_font.loadFromFile("ASSETS//FONTS//ariblk.ttf")) std::cout << "Error loading font" << std::endl;
	m_flowFieldGraph = new FlowFieldGraph(m_font, m_window);
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
		if (sf::Event::KeyPressed == newEvent.type || sf::Event::MouseButtonPressed == newEvent.type) 
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

	if (sf::Keyboard::Z == t_event.key.code)
	{
		m_flowFieldGraph->updateTilesCostDisplay();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		std::cout << "user pressed left mouse button.\n";
		m_flowFieldGraph->checkTileMouseClick(true, sf::Mouse::getPosition(m_window));
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		std::cout << "user pressed right mouse button.\n";
		m_flowFieldGraph->checkTileMouseClick(false, sf::Mouse::getPosition(m_window));
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	{
		m_flowFieldGraph->placeObstructedTIle(static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window)));
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
	m_flowFieldGraph->render();
	m_window.display();
}




