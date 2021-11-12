#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "Tile.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <stack>
#include <queue>

#include "FlowFieldGraph.h"
class Game
{
public:
	Game();
	~Game();

	void run();

private:
	static constexpr int NUM_ROWS = 50;
	static constexpr int NUM_COLS = 50;
	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	sf::RenderWindow m_window;
	sf::Font m_font;

	bool m_exitGame;
	FlowFieldGraph* m_flowFieldGraph;
};

#endif 