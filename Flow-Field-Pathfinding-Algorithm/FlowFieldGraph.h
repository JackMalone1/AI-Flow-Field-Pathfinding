#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "Tile.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <stack>
#include <queue>
#include "Utils.h"

class FlowFieldGraph
{
private:
	static constexpr int NUM_ROWS = 50;
	static constexpr int NUM_COLS = 50;
	std::array<std::array<Tile*, NUM_ROWS>, NUM_COLS> m_tiles;
	std::queue<Tile*> tiles;
	Tile* m_goalNode = nullptr;
	Tile* m_startNode = nullptr;
	sf::RenderWindow& m_renderWindow;
	sf::Font& m_font;
public:
	void checkTileMouseClick(bool t_isLeftMouseClick, sf::Vector2i t_mousePosition);
	FlowFieldGraph(sf::Font& t_font, sf::RenderWindow& t_window);
	void render();
	void updateTilesCostDisplay();
	void placeObstructedTIle(sf::Vector2f t_mousePosition);
private:
	void generateIntegrationField();
	void generateVectorField();
	void generateCostsForTiles();
	void generateTileCostWithNeighbour(int t_row, int t_col);
	void generateTileIntegrationCostWithNeighbour(int t_row, int t_col);
	void generateVectorFieldWithNeighbour(int t_row, int t_col);
	void generatePathTowardsGoal();
	void generatePathTowardsGoalWithNeighbour(int t_row, int t_col);
	void handleMouseClick(Tile*& tile, bool t_isLeftClick);
	
};

