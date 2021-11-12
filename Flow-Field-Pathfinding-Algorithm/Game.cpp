#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 1000U, 1000U, 32U }, "SFML Game" },
	m_exitGame{ false }
{
	srand(time(NULL));
	int y = -15;
	int x = -15;
	int id = 0;
	if (!m_font.loadFromFile("ASSETS//FONTS//ariblk.ttf")) std::cout << "Error loading font" << std::endl;
	sf::Color colour = sf::Color::Blue;
	for (int row = 0; row < m_tiles.size(); row++)
	{
		y += 20;
		x = -15;
		for (int col = 0; col <m_tiles.at(row).size(); col++)
		{
			auto& tile = m_tiles.at(row).at(col);
			x += 20;
			int isTraversable = rand() % 100 + 1;
			if (isTraversable < 5)
			{
				tile = new Tile(9000, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(x, y), 20.0f, 20.0f, m_font, colour, false, row, col);
			}
			else
			{
				tile = new Tile(9000, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(x, y), 20.0f, 20.0f, m_font, colour, true, row, col);
			}			
			id++;
			tile->setId(id);
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		std::cout << "user pressed left mouse button.\n";
		checkTileMouseClick(true);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		std::cout << "user pressed right mouse button.\n";
		checkTileMouseClick(false);
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

void Game::checkTileMouseClick(bool t_isLeftMouseClick)
{
	sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));
	for (auto& row : m_tiles)
	{
		for (auto& tile : row)
		{
			if (tile->intersectsPoint(mousePosition))
			{
				std::cout << "Intersecting with tile: " << tile->getID() << std::endl;
				if (t_isLeftMouseClick)
				{
					if (!tile->isGoalNode() && !tile->isStartNode())
					{
						tile->setIsGoalNode(true);
						tile->setIsStartNode(false);
						if (m_goalNode) m_goalNode->setIsGoalNode(false);
						m_goalNode = tile;
						generateCostsForTiles();
					}
					
				}
				else
				{
					if (!tile->isGoalNode() && !tile->isStartNode())
					{
						tile->setIsStartNode(true);
						tile->setIsGoalNode(false);
						if (m_startNode) m_startNode->setIsStartNode(false);
						m_startNode = tile;
					}
				}
			}
		}
	}
}

void Game::generateCostsForTiles()
{
	for (auto& row : m_tiles)
	{
		for (auto& tile : row)
		{
			tile->setMarked(false);
			tile->setCost(9000);
		}
	}
	m_goalNode->setCost(0);
	m_goalNode->setMarked(true);
	sf::Vector2i goalPos = m_goalNode->getRowAndCol();
	loopThroughAllTiles(generateTileCostWithNeighbour(goalPos.x, goalPos.y));
}

void Game::loopThroughAllTiles(std::stack<sf::Vector2i> t_tiles)
{
	while (!t_tiles.empty())
	{
		sf::Vector2i tile = t_tiles.top();
		t_tiles.pop();
		loopThroughAllTiles(generateTileCostWithNeighbour(tile.x, tile.y));
		std::cout << "X: " << tile.x << " Y: " << tile.y << "\n";
	}
}

std::stack<sf::Vector2i> Game::generateTileCostWithNeighbour(int t_row, int t_col)
{
	m_tiles.at(t_row).at(t_col)->setMarked(true);
	if (!m_tiles.at(t_row).at(t_col)->isTraversable()) return std::stack<sf::Vector2i>();
	//if (!m_tiles.at(t_row).at(t_col)->isTraversable()) return;
	std::stack<sf::Vector2i> validTiles;
	for (int direction = 0; direction < 9; direction++)
	{
		if (direction == 4) continue;

		int row = t_row + ((direction % 3) - 1);
		int col = t_col + ((direction / 3) - 1);

		if (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS)
		{
			
			if (!m_tiles.at(row).at(col)->getMarked())
			{
				validTiles.push(sf::Vector2i(row, col));
				if (m_tiles.at(row).at(col)->isTraversable())
				{
					m_tiles.at(row).at(col)->setCost(m_tiles.at(t_row).at(t_col)->getCost() + 1);					
				}
				else
				{
					m_tiles.at(row).at(col)->setCost(9000);
				}
				m_tiles.at(row).at(col)->setMarked(true);
			}
		}
	}
	return validTiles;
}



