#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 1500U, 1050U, 32U }, "SFML Game", sf::Style::Close},
	m_exitGame{ false }
{
	srand(time(NULL));
	if (!m_font.loadFromFile("ASSETS//FONTS//ariblk.ttf")) std::cout << "Error loading font" << std::endl;
	m_flowFieldGraph = new FlowFieldGraph(m_font, m_window);
	m_buttons.push_back(new Button(sf::Vector2f(1250, 200), "Display Costs (z)", 200, 50, "DISPLAY_COSTS"));
	m_buttons.push_back(new Button(sf::Vector2f(1250, 400), "Display IntCosts (x)", 200, 50, "DISPLAY_INT_COSTS"));
	m_buttons.push_back(new Button(sf::Vector2f(1250, 600), "Display Vectors (v)", 200, 50, "DISPLAY_VECTORS"));
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

void Game::displayCosts()
{
	m_flowFieldGraph->updateVectorFieldDisplay();
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

	if (sf::Keyboard::V == t_event.key.code)
	{
		m_flowFieldGraph->updateVectorFieldDisplay();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		std::cout << "user pressed left mouse button.\n";
		m_flowFieldGraph->checkTileMouseClick(true, sf::Mouse::getPosition(m_window));
		for (auto& button : m_buttons)
		{
			if (button->onButtonPress(sf::Mouse::getPosition(m_window)))
			{
				if (button->buttonType() == "DISPLAY_COSTS")
				{
					m_flowFieldGraph->updateTilesCostDisplay();
				}
				else if (button->buttonType() == "DISPLAY_VECTORS")
				{
					m_flowFieldGraph->updateVectorFieldDisplay();
				}
				else if (button->buttonType() == "DISPLAY_INT_COSTS")
				{
					m_flowFieldGraph->updateTilesIntegrationCostDisplay();
				}
			}
		}
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
	for (auto& button : m_buttons)
	{
		m_window.draw(*button);
	}
	m_window.display();
}




