#include "FlowFieldGraph.h"

void FlowFieldGraph::checkTileMouseClick(bool t_isLeftMouseClick, sf::Vector2i t_mousePosition)
{
	for (auto& row : m_tiles)
	{
		for (auto& tile : row)
		{
			if (tile->intersectsPoint(static_cast<sf::Vector2f>(t_mousePosition)) && tile->isTraversable())
			{
				handleMouseClick(tile, t_isLeftMouseClick);
			}
		}
	}
}

FlowFieldGraph::FlowFieldGraph(sf::Font& t_font, sf::RenderWindow& t_window) : m_renderWindow{ t_window }, m_font{t_font}
{
	int y = -10;
	int x = -10;
	int id = 0;
	sf::Color colour = sf::Color::Blue;
	for (int row = 0; row < m_tiles.size(); row++)
	{
		y += 20;
		x = -10;
		for (int col = 0; col < m_tiles.at(row).size(); col++)
		{
			auto& tile = m_tiles.at(row).at(col);
			x += 20;
			int isTraversable = rand() % 100 + 1;
			if (isTraversable < 5)
			{
				tile = new Tile(9000, new sf::Vector2f(0.0f, 0.0f), sf::Vector2f(x, y), 20.0f, 20.0f, m_font, colour, false, row, col);
			}
			else
			{
				tile = new Tile(9000, new sf::Vector2f(0.0f, 0.0f), sf::Vector2f(x, y), 20.0f, 20.0f, m_font, colour, true, row, col);
			}
			id++;
			tile->setId(id);
		}
	}
}

void FlowFieldGraph::generateCostsForTiles()
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

	tiles.push(m_goalNode);
	while (!tiles.empty())
	{
		Tile* tile = tiles.front();
		tiles.pop();
		generateTileCostWithNeighbour(tile->getRowAndCol().x, tile->getRowAndCol().y);
	}
	m_goalNode->setCost(0);


	for (auto& row : m_tiles)
	{
		for (auto& tile : row)
		{
			if (!tile->isTraversable()) tile->setCost(9000);
		}
	}
}

void FlowFieldGraph::generateTileCostWithNeighbour(int t_row, int t_col)
{
	for (int direction = 0; direction < 9; direction++)
	{
		if (direction == 4) continue;
		int row = t_row + ((direction % 3) - 1);
		int col = t_col + ((direction / 3) - 1);
		if (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS)
		{
			if (!m_tiles.at(row).at(col)->getMarked())
			{
				m_tiles.at(row).at(col)->setCost(m_tiles.at(t_row).at(t_col)->getCost() + 1);
				m_tiles.at(row).at(col)->setMarked(true);
				tiles.push(m_tiles.at(row).at(col));
			}
		}
	}
}

void FlowFieldGraph::generateTileIntegrationCostWithNeighbour(int t_row, int t_col)
{
	for (int direction = 0; direction < 9; direction++)
	{
		if (direction == 4) continue;
		int row = t_row + ((direction % 3) - 1);
		int col = t_col + ((direction / 3) - 1);
		if (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS)
		{
			Tile* tile = m_tiles.at(row).at(col);
			if (!tile->getMarked())
			{
				tile->setIntegrationCost(tile->getCost() +
					Utils::DistanceBetweenPositions(m_goalNode->getPosition(), tile->getPosition()));
				tile->setMarked(true);
				tiles.push(tile);
			}
		}
	}
}

void FlowFieldGraph::generateIntegrationField()
{
	for (auto& row : m_tiles)
	{
		for (auto& tile : row)
		{
			tile->setMarked(false);
		}
	}
	m_goalNode->setIntegrationCost(0);
	m_goalNode->setMarked(true);
	sf::Vector2i goalPos = m_goalNode->getRowAndCol();

	tiles.push(m_goalNode);
	while (!tiles.empty())
	{
		Tile* tile = tiles.front();
		tiles.pop();
		generateTileIntegrationCostWithNeighbour(tile->getRowAndCol().x, tile->getRowAndCol().y);
	}
	m_goalNode->setIntegrationCost(0);

	for (auto& row : m_tiles)
	{
		for (auto& tile : row)
		{
			if (!tile->isTraversable()) tile->setIntegrationCost(9000);
		}
	}
}

void FlowFieldGraph::generateVectorFieldWithNeighbour(int t_row, int t_col)
{
	Tile& tile = *m_tiles.at(t_row).at(t_col);
	if (tile.getMarked()) return;
	float lowestIntegrationCost = std::numeric_limits<float>::max();
	sf::Vector2f positionOfTile = tile.getPosition();
	for (int direction = 0; direction < 9; direction++)
	{
		if (direction == 4) continue;
		int row = t_row + ((direction % 3) - 1);
		int col = t_col + ((direction / 3) - 1);

		if (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS)
		{
			float integrationCost = m_tiles.at(row).at(col)->getIntegrationCost();
			if (integrationCost < lowestIntegrationCost)
			{
				lowestIntegrationCost = integrationCost;
				positionOfTile = m_tiles.at(row).at(col)->getPosition();
			}
		}
	}
	
	tile.setMarked(true);
	tile.setVectorField(new sf::Vector2f(positionOfTile + tile.getPosition()));
}

void FlowFieldGraph::generateVectorField()
{
	for (auto& row : m_tiles)
	{
		for (auto& tile : row)
		{
			tile->setMarked(false);
		}
	}
	m_goalNode->setVectorField(new sf::Vector2f(0.0f, 0.0f));
	m_goalNode->setMarked(true);
	sf::Vector2i goalPos = m_goalNode->getRowAndCol();

	for (auto& row : m_tiles)
	{
		for (auto& tile : row)
		{
			generateVectorFieldWithNeighbour(tile->getRowAndCol().x, tile->getRowAndCol().y);
		}
	}

	m_goalNode->setVectorField(new sf::Vector2f(0.0f, 0.0f));

	for (auto& row : m_tiles)
	{
		for (auto& tile : row)
		{
			if (!tile->isTraversable()) tile->setVectorField(nullptr);
		}
	}
}

void FlowFieldGraph::generatePathTowardsGoal()
{
	for (auto& row : m_tiles)
	{
		for (auto& tile : row)
		{
			tile->setColour(tile->getDefaultColour());
		}
	}

	tiles.push(m_startNode);
	while (!tiles.empty())
	{
		Tile* tile = tiles.front();
		tiles.pop();
		if (tile->isGoalNode())
		{
			std::queue<Tile*> empty;
			tiles.swap(empty);
			return;
		}
		generatePathTowardsGoalWithNeighbour(tile->getRowAndCol().x, tile->getRowAndCol().y);
	}
}

void FlowFieldGraph::generatePathTowardsGoalWithNeighbour(int t_row, int t_col)
{
	Tile& tile = *m_tiles.at(t_row).at(t_col);
	float lowestIntegrationCost = std::numeric_limits<float>::max();
	sf::Vector2i rowAndCol = tile.getRowAndCol();
	for (int direction = 0; direction < 9; direction++)
	{
		if (direction == 4) continue;
		int row = t_row + ((direction % 3) - 1);
		int col = t_col + ((direction / 3) - 1);

		if (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS)
		{
			float integrationCost = m_tiles.at(row).at(col)->getIntegrationCost();
			if (integrationCost < lowestIntegrationCost)
			{
				lowestIntegrationCost = integrationCost;
				rowAndCol = m_tiles.at(row).at(col)->getRowAndCol();
			}
		}
	}
	tiles.push(m_tiles.at(rowAndCol.x).at(rowAndCol.y));
	m_tiles.at(rowAndCol.x).at(rowAndCol.y)->setColour(sf::Color::Yellow);
}


void FlowFieldGraph::render()
{
	for (auto& row : m_tiles)
	{
		for (auto& tile : row)
		{
			m_renderWindow.draw(*tile);
		}
	}
}

void FlowFieldGraph::updateTilesCostDisplay()
{
	for (auto& row : m_tiles)
	{
		for (auto& tile : row)
		{
			tile->setShouldDisplayCost(!tile->shouldDisplayCost());
		}
	}
}


void FlowFieldGraph::handleMouseClick(Tile*& tile, bool t_isLeftClick)
{
	std::cout << "Intersecting with tile: " << tile->getID() << std::endl;
	if (t_isLeftClick)
	{
		if (!tile->isGoalNode() && !tile->isStartNode())
		{
			tile->setIsGoalNode(true);
			tile->setIsStartNode(false);
			if (m_goalNode) m_goalNode->setIsGoalNode(false);
			m_goalNode = tile;
			generateCostsForTiles();
			generateIntegrationField();
			generateVectorField();
			
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
	if (m_goalNode && m_startNode) generatePathTowardsGoal();
}
